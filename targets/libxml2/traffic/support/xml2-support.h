/*
 * Generated with AI.
 * ses_036844be9ffeqc6pOX8RvjU8TI
 */

#ifndef _TRAFFIC_LIBXML2_SUPPORT_H
#define _TRAFFIC_LIBXML2_SUPPORT_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <stdint.h>
#include <string.h>

// Status-style wrappers so Traffic can model failure without NULL: the
// generator cannot construct NULL, and a NULL-able (ptr T) return cannot
// carry the ghost facts later calls need. Each wrapper returns 0 on success
// and writes the handle through `out`.

// Parse an XML document from the input. The first two input bytes select
// parser options (mirroring xmlFuzzReadInt) and the remainder is parsed, like
// the upstream fuzz/xml.c target. Only a safe subset of options is honored.
static int xml2_read_memory(uint8_t* data, size_t size, xmlDocPtr* out) {
  const char* buffer;
  int options;
  int len;

  if (data == NULL && size != 0)
    return 1;
  if (size > 0x7fffffff)
    return 1;

  options = size >= 2 ? (data[0] | (data[1] << 8)) : 0;
  options &= XML_PARSE_RECOVER | XML_PARSE_NOENT | XML_PARSE_DTDLOAD |
             XML_PARSE_DTDATTR | XML_PARSE_DTDVALID | XML_PARSE_PEDANTIC |
             XML_PARSE_NOBLANKS | XML_PARSE_XINCLUDE | XML_PARSE_NONET |
             XML_PARSE_NODICT | XML_PARSE_NSCLEAN | XML_PARSE_NOCDATA |
             XML_PARSE_COMPACT;
  if ((options & XML_PARSE_NOENT) && size > 50000)
    return 1;

  buffer = size >= 2 ? (const char*)data + 2 : (const char*)data;
  len = size >= 2 ? (int)size - 2 : (int)size;

  xmlInitParser();
  *out = xmlReadMemory(buffer, len, "traffic.xml", NULL, options);
  return *out != NULL ? 0 : 1;
}

// Evaluate the input as an XPath expression against a document-less context,
// like the upstream fuzz/xpath.c target. The object is NULL on error.
static int xml2_xpath_eval(uint8_t* data, size_t size, xmlXPathObjectPtr* out) {
  xmlChar* expr;
  xmlXPathContextPtr ctxt;
  xmlXPathObjectPtr obj;

  if (data == NULL && size != 0)
    return 1;
  if (size > 0x7fffffff)
    return 1;

  expr = (xmlChar*)xmlMalloc((size_t)size + 1);
  if (expr == NULL)
    return 1;
  memcpy(expr, data, size);
  expr[size] = '\0';

  ctxt = xmlXPathNewContext(NULL);
  if (ctxt == NULL) {
    xmlFree(expr);
    return 1;
  }
  obj = xmlXPathEvalExpression(expr, ctxt);
  xmlXPathFreeContext(ctxt);
  xmlFree(expr);
  if (obj == NULL)
    return 1;
  *out = obj;
  return 0;
}

// Open a pull parser over the input.
static int xml2_reader_open(uint8_t* data, size_t size, xmlTextReaderPtr* out) {
  if (data == NULL && size != 0)
    return 1;
  if (size > 0x7fffffff)
    return 1;

  xmlInitParser();
  *out = xmlReaderForMemory((const char*)data, (int)size, "traffic.xml", NULL,
                            0);
  return *out != NULL ? 0 : 1;
}

// The result kind of an XPath object (node-set, boolean, number, string,
// points, xpath-locationset).
static int xml2_xpath_type(xmlXPathObjectPtr obj) {
  if (obj == NULL)
    return 0;
  return (int)obj->type;
}

// The number of nodes in a node-set result (0 for other result kinds).
static int xml2_xpath_node_count(xmlXPathObjectPtr obj) {
  if (obj == NULL)
    return 0;
  return (int)xmlXPathNodeSetGetLength(obj->nodesetval);
}

#endif // _TRAFFIC_LIBXML2_SUPPORT_H
