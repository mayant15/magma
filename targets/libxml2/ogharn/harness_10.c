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

   xmlSAXHandlerPtr xmlSAXUserParseMemoryvar0;
	memset(&xmlSAXUserParseMemoryvar0, 0, sizeof(xmlSAXUserParseMemoryvar0));

   void* xmlSAXUserParseMemoryvar1[size+1];
	sprintf(xmlSAXUserParseMemoryvar1, "/tmp/5kjhc");
   int xmlSAXUserParseMemoryval1 = xmlSAXUserParseMemory(xmlSAXUserParseMemoryvar0, xmlSAXUserParseMemoryvar1, fuzzData, size);
	if((int)xmlSAXUserParseMemoryval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
