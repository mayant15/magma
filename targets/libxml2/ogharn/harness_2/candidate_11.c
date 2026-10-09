#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <libxml/tree.h>
#include <libxml/globals.h>
#include <libxml/xmlIO.h>

int fuzz_11(char* fuzzData, long size) {
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/1iauj");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, size, xmlCtxtReadMemoryvar3, NULL, XML_SAX2_MAGIC);
   xmlDocPtr xmlCopyDocval1 = xmlCopyDoc(xmlCtxtReadMemoryval1, BASE_BUFFER_SIZE);
   return 0;
}
