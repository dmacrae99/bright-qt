/* libbrightness.h: Accompanying header file for libbrightness.c
 *
 * Copyright (C) 2017  Damien MacRae
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses.
 *
 * Damien MacRae <dmacrae99@gmail.com>
 *
 */
#ifndef LIBBRIGHTNESS_H
#define LIBBRIGHTNESS_H

struct backlight {
	const char *devname;
	long int maxbrightness;
	long int currentbrightness;
	char *foldername;
};

int get_brightness(char *file);
int get_maxbrightness(struct backlight *backlight);
int get_currentbrightness(struct backlight *backlight);
const char *get_backlightname();
char *get_filename(const char *folderpath, const char *file);
char *get_folderpath(struct backlight *backlight);
void set_brightness(struct backlight *backlight,int amount);
struct backlight *init_backlight();

#endif
