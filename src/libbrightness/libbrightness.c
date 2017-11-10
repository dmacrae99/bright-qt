#include "libbrightness.h"

#include <stdio.h>
#include <stdlib.h>
#include <libudev.h>
#include <string.h>

struct backlight *init_backlight() {
	struct backlight *backlight = malloc(sizeof(struct backlight));
	
	backlight->devname = get_backlightname();
	backlight->foldername = get_folderpath(backlight);	
	backlight->currentbrightness = get_currentbrightness(backlight);
	backlight->maxbrightness = get_maxbrightness(backlight);
	
	return backlight;
}

const char *get_backlightname() {
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *dev_list_entrys;
	const char *path, *sysname;
	struct udev_device *dev;
	
	udev = udev_new();
	if (!udev)
		fprintf(stderr, "ERROR: Failed to Create Udev Device\n");
	else {
		enumerate = udev_enumerate_new(udev);
		if(!enumerate)
			fprintf(stderr, "ERROR: Failed to create enumerate system\n");
		else {
			udev_enumerate_add_match_subsystem(enumerate, "backlight");
			udev_enumerate_scan_devices(enumerate);

			dev_list_entrys = udev_enumerate_get_list_entry(enumerate);

			if(!dev_list_entrys)
				fprintf(stderr, "ERROR: No udev Devices were found\n");
			else {
				path = udev_list_entry_get_name(dev_list_entrys);
				dev = udev_device_new_from_syspath(udev, path);

				sysname = udev_device_get_sysname(dev);
			}
		}
	}
	free(udev);
	free(enumerate);
	free(dev_list_entrys);
	free(dev);
	return sysname;
}


char *get_folderpath(struct backlight *backlight) {
	char *folderpath;
	folderpath = malloc(500*sizeof(char));
	strcpy(folderpath, "/sys/class/backlight/");
	strcat(folderpath, backlight->devname);
	strcat(folderpath, "/");
	return folderpath;
}

char *get_filename(const char *folderpath, const char *file) {
	char *filename = malloc(500*sizeof(char));
	filename = strcpy(filename, folderpath);
	filename = strcat(filename, file);
	return filename;
}

int get_maxbrightness(struct backlight *backlight) {
	return get_brightness(get_filename(backlight->foldername,"max_brightness"));
}

int get_currentbrightness(struct backlight *backlight) {
	return get_brightness(get_filename(backlight->foldername,"brightness"));
}

int get_brightness(char *file) {
	char *readbuffer = malloc(sizeof(char)*10);
	int brightness;

	FILE *brightnessf = fopen(file, "r");
	if(brightnessf != NULL)
		fgets(readbuffer, 10, brightnessf);
	else
		fprintf(stderr, "ERROR: Failed to open file for reading!\nTry with sudo\n");
	brightness = atoi(readbuffer);

	free(readbuffer);
	free(file);
	fclose(brightnessf);
	return brightness;	
}

void set_brightness(struct backlight *backlight, const char *amountc) {
	char *file = get_filename(backlight->foldername,"brightness");
	char *writebuffer = malloc(sizeof(char)*10);
	FILE *brightnessf;
	int amount;

	amount = atoi(amountc);

	printf("Opening file %s for writing...\n", file);
	brightnessf = fopen(file, "w");

	if(!brightnessf)
		fprintf(stderr, "ERROR: Failed to open file for reading!\n");
	else {
		sprintf(writebuffer, "%d", amount);
		fputs(writebuffer, brightnessf);
	}

	free(writebuffer);
	fclose(brightnessf);
}
