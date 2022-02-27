#include "StarWars.h"

void count_page_num(int *num_count, int page_number) {
	int each_page, remainder;

	//For each page, count the number that consists the page number.
	for (int i=1; i <= page_number; i++) {
                each_page = i;
                while (each_page > 0) {
                        remainder = each_page % 10;
                        num_count[remainder]++;
                        each_page /= 10;
                }
        }
}

