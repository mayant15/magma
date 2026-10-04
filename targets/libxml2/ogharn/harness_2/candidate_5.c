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
   int xmlCtxtReadMemoryvar2 = 1;
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/2hlpq");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, xmlCtxtReadMemoryvar2, xmlCtxtReadMemoryvar3, fuzzData, size);
   xmlDocPtr xmlCopyDocval1 = xmlCopyDoc(xmlCtxtReadMemoryval1, 0);
   return 0;
}
