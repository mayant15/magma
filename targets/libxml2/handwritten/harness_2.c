/* Regular expressions plus the string / buffer APIs.
 *
 * The input is a sequence of operations; each starts with an opcode byte:
 *   op % 4 == 0, 1  regexp: NUL/newline-terminated pattern, then a subject
 *                   string; compile, check determinism, execute
 *   op % 4 == 2     xmlBufferCreateSize + xmlBufferAdd / xmlBufferCat
 *   op % 4 == 3     xmlStrncat / xmlStrncatNew with a fuzzed length
 *
 *   XML016  character range whose end precedes its start, e.g. "[z-a]"
 *   XML005  reached through the debug allocator
 *   XML011  reached in xmlStrncat / xmlStrncatNew. Triggering needs a string
 *           of >= 2 GiB (xmlStrlen() going negative), which these int-sized
 *           APIs cannot build, so it is reach-only here.
 */

#include "harness.h"

#include <libxml/tree.h>
#include <libxml/xmlregexp.h>
#include <libxml/xmlstring.h>

#define MAX_OPS 32
#define MAX_STR 1024

typedef struct {
  const uint8_t *p;
  size_t left;
} provider;

static int take_byte(provider *pv, uint8_t *out) {
  if (pv->left == 0)
    return 0;
  *out = *pv->p++;
  pv->left--;
  return 1;
}

static uint64_t take_u64(provider *pv, size_t nbytes) {
  uint64_t v = 0;
  size_t i;
  for (i = 0; i < nbytes && pv->left > 0; i++) {
    v |= (uint64_t)*pv->p++ << (8 * i);
    pv->left--;
  }
  return v;
}

/* String up to (and consuming) the next NUL or newline. Caller frees. */
static xmlChar *take_str(provider *pv) {
  size_t n = 0;
  xmlChar *s;
  while (n < pv->left && n < MAX_STR && pv->p[n] != 0 && pv->p[n] != '\n')
    n++;
  s = xmlStrndup(BAD_CAST pv->p, (int)n);
  if (n < pv->left)
    n++; /* terminator */
  pv->p += n;
  pv->left -= n;
  return s;
}

static void do_regexp(provider *pv) {
  xmlChar *pattern = take_str(pv);
  xmlChar *subject = take_str(pv);
  xmlRegexpPtr re;

  if (pattern != NULL) {
    re = xmlRegexpCompile(pattern);
    if (re != NULL) {
      xmlRegexpIsDeterminist(re);
      if (subject != NULL)
        xmlRegexpExec(re, subject);
      xmlRegFreeRegexp(re);
    }
  }
  xmlFree(pattern);
  xmlFree(subject);
}

static void do_buffer(provider *pv) {
  size_t size = (size_t)take_u64(pv, 2); /* up to 64 KiB */
  xmlChar *add = take_str(pv);
  xmlBufferPtr buf;

  buf = xmlBufferCreateSize(size);
  if (buf != NULL) {
    if (add != NULL) {
      xmlBufferAdd(buf, add, xmlStrlen(add));
      xmlBufferCat(buf, add);
      xmlBufferShrink(buf, (unsigned)xmlStrlen(add));
    }
    xmlBufferFree(buf);
  }
  xmlFree(add);
}

static void do_strcat(provider *pv) {
  uint8_t sel = 0;
  xmlChar *a, *b, *r;
  int blen, len;

  take_byte(pv, &sel);
  len = (int)take_u64(pv, 4);
  a = take_str(pv);
  b = take_str(pv);
  blen = xmlStrlen(b);
  /* len in [-1, blen]: never read past b, but keep the API's -1 path. */
  len = (int)((unsigned)len % (unsigned)(blen + 2)) - 1;

  if (sel & 1) {
    r = xmlStrncatNew(a, b, len);
    xmlFree(r);
    xmlFree(a);
  } else {
    r = xmlStrncat(a, b, len); /* takes ownership of a */
    if (r != NULL)
      xmlFree(r);
    else
      xmlFree(a);
  }
  xmlFree(b);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  provider pv = {data, size};
  uint8_t op;
  int i;

  for (i = 0; i < MAX_OPS && take_byte(&pv, &op); i++) {
    switch (op % 4) {
    case 0:
    case 1:
      do_regexp(&pv);
      break;
    case 2:
      do_buffer(&pv);
      break;
    case 3:
      do_strcat(&pv);
      break;
    }
  }
  return 0;
}
