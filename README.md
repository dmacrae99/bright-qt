# sbacklight
Application that can set the screen brightness in linux. The application uses udev and will control the device based on the device found in "/sys/class/backlight"

To install: 
	git clone --depth=1 https://github.com/dmacrae99/sbacklight
	cd sbacklight
	make folders
	make
	sudo make install
	
If you want to be able to set the backlight without root access add yourself to the video group with
	sudo gpasswd -a <user> video
	
Make sure to reboot so the udev rule that was copied in make install can be configured by udev

For help:
	sbacklight -h


