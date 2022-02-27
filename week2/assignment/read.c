#include "StarWars.h"

void read_page_num(FILE* fp, int *page_number) {
	fscanf(fp, "%d", page_number);
	if (*page_number < 0 || *page_number > 1000000001) {
		printf("Error! Total page number is out of range.\n");
		exit(0);
	}
}

