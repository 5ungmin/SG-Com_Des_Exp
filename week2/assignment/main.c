#include "StarWars.h"

void main(int argc, char *argv[]) {
	FILE *fp;
	int num_count[10];
	int test_case_num, page_number;

	//If there's no input file, exit.
	if (argc != 2) {
		printf("Error! Uasage: CountPageNum [case filename]\n");
		return;
	}

	//Open test case file and read the number of test cases.
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Error! Cannot open file.\n");
		return;
	}
	fscanf(fp, "%d", &test_case_num);

	//Count the number that consists each page number.
	//Repeat the process test_case_num times.
	for (int i=0; i<test_case_num; i++) {
		//reset the page count
		for (int j=0; j<10; j++) {
			num_count[j] = 0;
		}
		read_page_num(fp, &page_number);
		count_page_num(num_count, page_number);
		print_result(num_count);
	}
	fclose(fp);
	return;
}
