#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>

int main(int argc, char *argv[])
{
	FILE *f;
    char *fuzzData = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1) 
        exit(0);

    fuzzData = (char*)malloc((size_t)size+1);
    if(fuzzData == NULL)
        exit(0);

    if(fread(fuzzData, (size_t)size, 1, f) != 1)
        exit(0);
    fuzzData[size] = '\0';

   xmlSAXHandlerPtr xmlSAXParseMemoryWithDatavar0;
	memset(&xmlSAXParseMemoryWithDatavar0, 0, sizeof(xmlSAXParseMemoryWithDatavar0));

   int xmlSAXParseMemoryWithDatavar3 = 1;
   void* xmlSAXParseMemoryWithDatavar4[size+1];
	sprintf(xmlSAXParseMemoryWithDatavar4, "/tmp/eko83");
   xmlDocPtr xmlSAXParseMemoryWithDataval1 = xmlSAXParseMemoryWithData(xmlSAXParseMemoryWithDatavar0, fuzzData, size, xmlSAXParseMemoryWithDatavar3, xmlSAXParseMemoryWithDatavar4);
   return 0;
}
