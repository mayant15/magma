/* Shared plumbing for the hand-written libxml2 harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, like the traffic and
 * ogharn harnesses) plus:
 *
 *  - libxml2's debug allocator (xmlMemMalloc & co, as used by xmllint's
 *    memory debugging). XML005's canary lives in xmlMallocLoc and friends,
 *    which are only used when this allocator is installed.
 *  - a structured error handler that silences output and can stop the parser
 *    (xmlStopParser) on the Nth error, as applications do from callbacks.
 *    Halting mid-parse is what XML007 and XML008 need.
 *  - a chunked read callback so the parser sees input arrive incrementally
 *    (buffer growth/reallocation is what XML012, XML013 and XML015 need).
 *  - an external entity loader that never touches the filesystem/network.
 *
 * Per-input configuration is taken from the last 4 bytes of the input, which
 * are *not* stripped: trailing bytes after an XML/HTML document's root are
 * harmless, so seed documents parse unchanged and mutating the tail changes
 * the configuration.
 */

#ifndef LIBXML2_HANDWRITTEN_HARNESS_H
#define LIBXML2_HANDWRITTEN_HARNESS_H

#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/xmlerror.h>
#include <libxml/xmlmemory.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Path of the input file (for harnesses that read through libxml2's own
 * file I/O, e.g. to reach the gzip/xz decompressors). */
static const char *harness_path;

/* ---- configuration ------------------------------------------------------ */

typedef struct {
  unsigned mode;       /* bits 0-1:   input mode, harness specific */
  size_t chunk;        /* bits 2-7:   1..64 bytes per read/push */
  unsigned stop_after; /* bits 8-11:  xmlStopParser on Nth error, 0 = never */
  uint32_t flags;      /* bits 12-31: harness-specific option bits */
} harness_cfg;

static inline harness_cfg harness_config(const uint8_t *data, size_t size) {
  uint32_t raw = 0;
  size_t i, n = size < 4 ? size : 4;
  harness_cfg cfg;

  for (i = 0; i < n; i++)
    raw |= (uint32_t)data[size - n + i] << (8 * i);

  cfg.mode = raw & 3;
  cfg.chunk = 1 + ((raw >> 2) & 63);
  cfg.stop_after = (raw >> 8) & 15;
  cfg.flags = raw >> 12;
  return cfg;
}

/* Map option bits onto a table of parser options. */
static inline int harness_options(uint32_t flags, const int *table, size_t n) {
  int opts = 0;
  size_t i;
  for (i = 0; i < n; i++)
    if (flags & (1u << i))
      opts |= table[i];
  return opts;
}

/* ---- errors --------------------------------------------------------------- */

static unsigned harness_errors, harness_stop_after;

static void harness_structured_error(void *user, xmlErrorPtr err) {
  (void)user;
  if (err == NULL || err->ctxt == NULL || harness_stop_after == 0)
    return;
  switch (err->domain) {
  case XML_FROM_PARSER:
  case XML_FROM_HTML:
  case XML_FROM_NAMESPACE:
  case XML_FROM_VALID:
    /* For these domains err->ctxt is the parser context. */
    if (++harness_errors == harness_stop_after)
      xmlStopParser((xmlParserCtxtPtr)err->ctxt);
    break;
  default:
    break;
  }
}

static void harness_generic_error(void *ctx, const char *msg, ...) {
  (void)ctx;
  (void)msg;
}

static inline void harness_begin(const harness_cfg *cfg) {
  harness_errors = 0;
  harness_stop_after = cfg->stop_after;
}

/* ---- chunked input -------------------------------------------------------- */

typedef struct {
  const uint8_t *data;
  size_t left;
  size_t chunk;
} harness_src;

static inline int harness_read(void *ctx, char *out, int len) {
  harness_src *src = (harness_src *)ctx;
  size_t n = src->chunk;
  if (n > src->left)
    n = src->left;
  if (n > (size_t)len)
    n = (size_t)len;
  memcpy(out, src->data, n);
  src->data += n;
  src->left -= n;
  return (int)n;
}

static inline int harness_close(void *ctx) {
  (void)ctx;
  return 0;
}

/* ---- external entities ------------------------------------------------------ */

static xmlExternalEntityLoader harness_default_loader;

/* Every external entity / DTD resolves to a single space: valid as content,
 * DTD text and PE replacement text, and never touches the filesystem. The
 * one exception is the input file itself (xmlCtxtReadFile goes through the
 * entity loader too), which gets libxml2's own file / gzip / xz I/O. */
static xmlParserInputPtr harness_entity_loader(const char *url, const char *id,
                                               xmlParserCtxtPtr ctxt) {
  if (url != NULL && harness_path != NULL && strcmp(url, harness_path) == 0)
    return harness_default_loader(url, id, ctxt);
  return xmlNewStringInputStream(ctxt, BAD_CAST " ");
}

/* ---- main ------------------------------------------------------------------- */

static void harness_init(void) {
  xmlMemSetup(xmlMemFree, xmlMemMalloc, xmlMemRealloc, xmlMemoryStrdup);
  xmlInitParser();
  xmlSetGenericErrorFunc(NULL, harness_generic_error);
  xmlSetStructuredErrorFunc(NULL, harness_structured_error);
  harness_default_loader = xmlGetExternalEntityLoader();
  xmlSetExternalEntityLoader(harness_entity_loader);
}

static int fuzz_one(const uint8_t *data, size_t size);

int main(int argc, char *argv[]) {
  FILE *f;
  long size;
  uint8_t *buf;
  int ret;

  if (argc < 2)
    return 0;

  f = fopen(argv[1], "rb");
  if (f == NULL)
    return 0;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);
  if (size < 1) {
    fclose(f);
    return 0;
  }

  buf = (uint8_t *)malloc((size_t)size);
  if (buf == NULL || fread(buf, (size_t)size, 1, f) != 1) {
    fclose(f);
    free(buf);
    return 0;
  }
  fclose(f);

  harness_path = argv[1];
  harness_init();
  ret = fuzz_one(buf, (size_t)size);
  free(buf);
  return ret;
}

#endif /* LIBXML2_HANDWRITTEN_HARNESS_H */
