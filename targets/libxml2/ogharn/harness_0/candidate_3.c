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
   char* xmlCtxtReadMemoryvar4[size+1];
	sprintf(xmlCtxtReadMemoryvar4, "/tmp/p43w2");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, XML_DETECT_IDS, NULL, xmlCtxtReadMemoryvar4, sizeof(xmlCtxtReadMemoryvar4));
   return 0;
}
