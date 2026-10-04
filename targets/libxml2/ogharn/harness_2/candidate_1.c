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

int fuzz_1(char* fuzzData, long size) {
   int xmlCtxtReadMemoryvar2 = 1;
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/h0v42");
   char* xmlCtxtReadMemoryvar4[size+1];
	sprintf(xmlCtxtReadMemoryvar4, "/tmp/u1wez");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, xmlCtxtReadMemoryvar2, xmlCtxtReadMemoryvar3, xmlCtxtReadMemoryvar4, sizeof(xmlCtxtReadMemoryvar4));
   return 0;
}
