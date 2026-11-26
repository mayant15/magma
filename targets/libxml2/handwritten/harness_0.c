/* XML parser: memory, chunked pull (IO), push, or libxml2 file I/O.
 *
 * Config comes from the input's last 4 bytes (see support/harness.h):
 *   mode 0  xmlCtxtReadMemory
 *   mode 1  xmlCtxtReadIO, `chunk` bytes per read     (buffer growth)
 *   mode 2  xmlParseChunk, `chunk` bytes per push
 *   mode 3  xmlCtxtReadFile on the input path         (gzip / xz decoders)
 * flags pick parser options plus post-parse validation and serialization.
 *
 *   XML001/006  xmlSnprintfElementContent on a DTD validity error, long
 *               prefixed names. XML006's condition can only become true via
 *               XML001's overflow, in the same call and after XML001's
 *               canary, so Magma (which counts only the first trigger per
 *               run) records XML001.
 *   XML002      ATTLIST declaring an xmlns:* attribute as ID/IDREF + DTDVALID
 *   XML003      external PE reference without NOENT/DTDVALID/DTDLOAD/DTDATTR
 *   XML004      mode 3, .lzma header whose dictionary exceeds the decoder
 *               memlimit (LZMA_MEMLIMIT_ERROR slips past xz_decomp)
 *   XML005      reached through the debug allocator
 *   XML008      "--" inside a comment while the error handler stops the parser
 *   XML009      encoding declaration whose conversion of buffered bytes fails
 *               (e.g. EUC-JP followed by an invalid byte)
 *   XML010      external PE referenced inside an entity value
 *   XML011      reached via xmlStrncat/xmlStrncatNew in tree building
 *   XML012      mode 1, ~4 KB non-ASCII NCName ending in a multibyte char
 *               whose lead byte ends a read: that grow reallocates the buffer
 *   XML017      junk between "]" and ">" of a DOCTYPE internal subset
 */

#include "harness.h"

#include <libxml/tree.h>
#include <libxml/valid.h>

static const int xml_options[] = {
    XML_PARSE_RECOVER,  XML_PARSE_NOENT,    XML_PARSE_DTDLOAD,
    XML_PARSE_DTDATTR,  XML_PARSE_DTDVALID, XML_PARSE_NOBLANKS,
    XML_PARSE_SAX1,     XML_PARSE_NSCLEAN,  XML_PARSE_NOCDATA,
    XML_PARSE_OLD10,    XML_PARSE_IGNORE_ENC, XML_PARSE_NODICT,
    XML_PARSE_PEDANTIC, XML_PARSE_OLDSAX,   XML_PARSE_BIG_LINES,
};
#define NUM_XML_OPTIONS (sizeof xml_options / sizeof xml_options[0])
#define FLAG_POST_VALIDATE (1u << NUM_XML_OPTIONS)
#define FLAG_DUMP (1u << (NUM_XML_OPTIONS + 1))

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_cfg cfg = harness_config(data, size);
  int opts = harness_options(cfg.flags, xml_options, NUM_XML_OPTIONS) |
             XML_PARSE_NONET;
  xmlParserCtxtPtr ctxt = NULL;
  xmlDocPtr doc = NULL;

  harness_begin(&cfg);

  if (cfg.mode == 2) {
    size_t off, n;
    ctxt = xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, "fuzz.xml");
    if (ctxt == NULL)
      return 0;
    xmlCtxtUseOptions(ctxt, opts);
    for (off = 0; off < size; off += n) {
      n = size - off < cfg.chunk ? size - off : cfg.chunk;
      xmlParseChunk(ctxt, (const char *)data + off, (int)n, 0);
    }
    xmlParseChunk(ctxt, NULL, 0, 1);
    doc = ctxt->myDoc;
    ctxt->myDoc = NULL;
  } else {
    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL)
      return 0;
    if (cfg.mode == 0) {
      doc = xmlCtxtReadMemory(ctxt, (const char *)data, (int)size, "fuzz.xml",
                              NULL, opts);
    } else if (cfg.mode == 1) {
      harness_src src = {data, size, cfg.chunk};
      doc = xmlCtxtReadIO(ctxt, harness_read, harness_close, &src, "fuzz.xml",
                          NULL, opts);
    } else {
      doc = xmlCtxtReadFile(ctxt, harness_path, NULL, opts);
    }
  }

  if (doc != NULL) {
    if (cfg.flags & FLAG_POST_VALIDATE) {
      xmlValidCtxtPtr vctxt = xmlNewValidCtxt();
      if (vctxt != NULL) {
        xmlValidateDocument(vctxt, doc);
        xmlFreeValidCtxt(vctxt);
      }
    }
    if (cfg.flags & FLAG_DUMP) {
      xmlChar *mem = NULL;
      int len = 0;
      xmlDocDumpMemory(doc, &mem, &len);
      xmlFree(mem);
    }
    xmlFreeDoc(doc);
  }
  xmlFreeParserCtxt(ctxt);
  return 0;
}
