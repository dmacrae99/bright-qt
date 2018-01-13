#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libbacklight/libbacklight.h"
#include "sbacklight.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		help();
		return EXIT_SUCCESS;
	}
	struct backlight *backlight = init_backlight();
	int value;
	int set = 0;

	if ((strcmp("-m", argv[1]) == 0) || (strcmp("--max", argv[1]) == 0)) {
		set = 1;
		value = backlight->maxbrightness;
	}

	else if ((strcmp("-c", argv[1]) == 0) || (strcmp("--cur", argv[1]) == 0)) {
		int percent = get_currentbrightness(backlight)/backlight->maxbrightness*100;
		printf("Current brightness: %d%%", percent);
	}

	else if ((strcmp("-h", argv[1]) == 0) || (strcmp("--help", argv[1]) == 0)) {
		help();
	}

	else if ((strcmp("-s", argv[1]) == 0) || (strcmp("--set", argv[1]) == 0)) {
		set = 1;

		if (argc < 3) {
			set = 0;
			printf("Not Enough Arguments\n sbacklight -s PERCENT\n");
		}

		else if (isNumber(argv[2]) != 0) {
			set = 0;
			printf("Invalid argument: %s\n", argv[2]);
		}

		else {	
			value = backlight->maxbrightness*atoi(argv[2])/100;
		}
	}

	else if ((strcmp("-i", argv[1]) == 0) || (strcmp("--inc", argv[1]) == 0)) {
		set = 1;
		if (argc < 3) {
			set = 0;
			printf("Not Enough Arguments\n sbacklight -i PERCENT\n");
		}

		else if (isNumber(argv[2])) {
			set = 0;
			printf("Invalid argument: %s\n", argv[2]);
		}

		else {
			int increaseamount = backlight->maxbrightness*atoi(argv[2])/100;
			value = backlight->currentbrightness+increaseamount;
		}
	}

	else if ((strcmp("-d", argv[1]) == 0) || (strcmp("--dec", argv[1]) == 0)) {
		set = 1;
		if (argc < 3) {
			set = 0;
			printf("Not Enough Arguments\n sbacklight -d PERCENT\n");
		}

		else if (isNumber(argv[2])) {
			set = 0;
			printf("Invalid argument: %s\n", argv[2]);
		}

		else {
			int decreaseamount = backlight->maxbrightness*atoi(argv[2])/100;
			value = backlight->currentbrightness-decreaseamount;
		}
	}

	else {
		printf("Unknown Argument: %s %s\n\n", argv[0], argv[1]);
		help();
	}

	if (set == 1) {
		set_brightness(backlight, value);
	}

	backlight_unref(backlight);
	return EXIT_SUCCESS;
}

int isNumber(char number[]) {
	int i = 0;

	if (number[0] == '-')
		i = 1;

	for (; number[i] != 0; i++) {
		if (!isdigit(number[i]))
			return 1;
	}

	return 0;
}

void help() {
	printf("Application to control the backlight\n");
	printf("USAGE: sbacklight <Option>\n");
	printf("    <Option>: \n");
	printf("        -s, --set     PERCENT    Set brightness to percent\n");
	printf("        -m, --max                Set brightness to max\n");
	printf("        -i, --inc     PERCENT    Increase brightness\n");
	printf("        -d, --dec     PERCENT    Decrease brightness\n");
	printf("        -c, --cur                Prints the current brightness\n");
	printf("        -h, --help               Prints this help menu\n");
}
