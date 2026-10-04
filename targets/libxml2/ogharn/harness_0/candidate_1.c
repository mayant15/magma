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
   char* xmlCtxtReadMemoryvar3[size+1];
	sprintf(xmlCtxtReadMemoryvar3, "/tmp/ci7qs");
   xmlParserCtxtPtr xmlNewParserCtxtval1 = xmlNewParserCtxt();
   xmlDocPtr xmlCtxtReadMemoryval1 = xmlCtxtReadMemory(xmlNewParserCtxtval1, fuzzData, XML_DETECT_IDS, xmlCtxtReadMemoryvar3, fuzzData+size, size);
   xmlDocPtr xmlCopyDocval1 = xmlCopyDoc(xmlCtxtReadMemoryval1, 0);
   return 0;
}
