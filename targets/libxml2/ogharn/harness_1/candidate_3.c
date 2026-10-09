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

int fuzz_3(char* fuzzData, long size) {
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/1xww2");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, size, xmlCtxtReadMemoryvar3, NULL, XML_SAX2_MAGIC);
   xmlFreeDoc(xmlCtxtReadMemoryval1);
   return 0;
}
