/* HTML parser: memory, chunked pull (IO) or push.
 *
 * Config comes from the input's last 4 bytes (see support/harness.h):
 *   mode 0    htmlCtxtReadMemory
 *   mode 1    htmlCtxtReadIO, `chunk` bytes per read   (buffer growth)
 *   mode 2/3  htmlParseChunk, `chunk` bytes per push
 * flags pick HTML parser options and serialization.
 *
 *   XML007  push parser keeps going after the parser was halted (encoding
 *           conversion failure, or the error handler calling xmlStopParser)
 *   XML013  DOCTYPE system/public literal spanning a buffer reallocation
 *   XML014  document ending in the middle of a tag/attribute name
 *   XML015  non-ASCII name while the input buffer moves (growth or the
 *           UTF-8 -> ISO-8859-1 fallback switch)
 *   XML005  reached through the debug allocator
 */

#include "harness.h"

#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>

static const int html_options[] = {
    HTML_PARSE_RECOVER,  HTML_PARSE_NODEFDTD, HTML_PARSE_PEDANTIC,
    HTML_PARSE_NOBLANKS, HTML_PARSE_NOIMPLIED, HTML_PARSE_COMPACT,
    HTML_PARSE_IGNORE_ENC,
};
#define NUM_HTML_OPTIONS (sizeof html_options / sizeof html_options[0])
#define FLAG_DUMP (1u << NUM_HTML_OPTIONS)

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_cfg cfg = harness_config(data, size);
  int opts = harness_options(cfg.flags, html_options, NUM_HTML_OPTIONS) |
             HTML_PARSE_NONET;
  htmlParserCtxtPtr ctxt = NULL;
  htmlDocPtr doc = NULL;

  harness_begin(&cfg);

  if (cfg.mode >= 2) {
    size_t off, n;
    ctxt = htmlCreatePushParserCtxt(NULL, NULL, NULL, 0, "fuzz.html",
                                    XML_CHAR_ENCODING_NONE);
    if (ctxt == NULL)
      return 0;
    htmlCtxtUseOptions(ctxt, opts);
    for (off = 0; off < size; off += n) {
      n = size - off < cfg.chunk ? size - off : cfg.chunk;
      htmlParseChunk(ctxt, (const char *)data + off, (int)n, 0);
    }
    htmlParseChunk(ctxt, NULL, 0, 1);
    doc = ctxt->myDoc;
    ctxt->myDoc = NULL;
  } else {
    ctxt = htmlNewParserCtxt();
    if (ctxt == NULL)
      return 0;
    if (cfg.mode == 0) {
      doc = htmlCtxtReadMemory(ctxt, (const char *)data, (int)size,
                               "fuzz.html", NULL, opts);
    } else {
      harness_src src = {data, size, cfg.chunk};
      doc = htmlCtxtReadIO(ctxt, harness_read, harness_close, &src,
                           "fuzz.html", NULL, opts);
    }
  }

  if (doc != NULL) {
    if (cfg.flags & FLAG_DUMP) {
      xmlChar *mem = NULL;
      int len = 0;
      htmlDocDumpMemory(doc, &mem, &len);
      xmlFree(mem);
    }
    xmlFreeDoc(doc);
  }
  htmlFreeParserCtxt(ctxt);
  return 0;
}
