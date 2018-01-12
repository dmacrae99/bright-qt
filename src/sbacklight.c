#include <stdio.h>
#include <stdlib.h>

#include "libbacklight/libbacklight.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		help();
	}

	return EXIT_SUCCESS;
}

void help() {
	printf("Application to control the backlight\n");
	printf("USAGE: sbacklight <Option>\n");
	printf("    <Option>: \n");
	printf("        -s, --set     PERCENT    Set brightness to percent");
	printf("        -m, --max                Set brightness to max");
	printf("        -i, --inc     PERCENT    Increase brightness");
	printf("        -d, --dec     PERCENT    Decrease brightness");
	printf("        -c, --cur                Prints the current brightness");
	printf("        -h, --help               Prints this help menu");
}
