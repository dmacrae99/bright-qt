#ifdef __cplusplus
extern "C" {
#endif

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
void set_brightness(struct backlight *backlight,const char *amountc);
struct backlight *init_backlight();

#ifdef __cplusplus
}
#endif
