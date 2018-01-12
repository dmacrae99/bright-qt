#include <stdio.h>
#include <stdlib.h>

#include "libbacklight.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		help();
	}

	return EXIT_SUCCESS;
}

void help() {
	printf("sbacklight: Application to control the backlight of laptops\n");
	printf("USAGE: sbacklight <Option> <Value>\n");
	printf("<Option>: \n
			\t-i\t--inc\tIncrease the brightness\n
			\t-c\t--current\tDisplay the current brightness\n
			\t-h\t--help\tDisplay this help menu\n");
	printf("<Value>: This application works in percentage, So use percentage 
			amounts for functions\n");
}
