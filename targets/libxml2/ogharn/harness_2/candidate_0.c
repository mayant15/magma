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

int fuzz_0(char* fuzzData, long size) {
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/bfbeu");
   char* xmlCtxtReadMemoryvar4[size+1];
	sprintf(xmlCtxtReadMemoryvar4, "/tmp/p0x9m");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, size, xmlCtxtReadMemoryvar3, xmlCtxtReadMemoryvar4, -1);
   xmlDocPtr xmlCopyDocval1 = xmlCopyDoc(xmlCtxtReadMemoryval1, XML_COMPLETE_ATTRS);
   xmlFreeDoc(xmlCopyDocval1);
   return 0;
}
