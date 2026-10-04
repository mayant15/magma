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

int fuzz_4(char* fuzzData, long size) {
   char* xmlCtxtReadMemoryvar4[size+1];
	sprintf(xmlCtxtReadMemoryvar4, "/tmp/vtxba");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, size, fuzzData+size, xmlCtxtReadMemoryvar4, -1);
   xmlFreeDoc(xmlCtxtReadMemoryval1);
   return 0;
}
