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

int fuzz_5(char* fuzzData, long size) {
   char* xmlCtxtReadMemoryvar1[size+1];
	sprintf(xmlCtxtReadMemoryvar1, "/tmp/n0lih");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, xmlCtxtReadMemoryvar1, 0, fuzzData+size, fuzzData, size);
   return 0;
}
