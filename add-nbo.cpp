// main.cpp
#include <fstream>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>		
#include <stdio.h>
#include <stdlib.h>

uint32_t readInt(const char *fileName)
{
	FILE *binFile = fopen(fileName, "rb");
	uint32_t result;
	size_t readLen = fread(&result, 1, sizeof(uint32_t), binFile);

	if (binFile == NULL)
	{
		fprintf(stderr, "Error: Input file %s is null. \n", fileName);
		exit(-1);
	} else if(readLen != sizeof(uint32_t))
	{
		fprintf(stderr, "Error: Fread return %lu. \n", readLen);
		exit(-1);
	}

	result = ntohl(result);

	fclose(binFile);

	return result;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Error: Correct syntax is ./add-nbo <first_file> <second_file>\n");
		exit(-1);
	
	}
	
	uint32_t f1 = readInt(argv[1]);
	uint32_t f2 = readInt(argv[2]);

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", int(f1), f1, int(f2), f2, int(f1+f2), f1+f2);
	return 0;
}
