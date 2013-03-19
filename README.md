NoRSX is a 2D lib for PSL1GHT
=============================

NOW IT'S A REAL PSL1GHT LIB
This lib will be installed inside the PORTLIBS

Authors
-------
	deroad
	kakaroto (for his rsxutil.c)
	KDSBest (for some performance patches)

Changelog:
----------
	- 0.2.9 -
		Ingame XMB Bug Fully fixed! now it works very very well!
		Added ExitSignalStatus() that returns NO_SIGNAL ( = 0) and EXIT_SIGNAL ( = 1) to check if the use pressed exit game on the XMB menu.
	- 0.2.2 -
		Added Image Resize Algorithm ( Thanks to: http://www.compuphase.com/graphic/scale.htm )
	- 0.2.1 -
		Added new Message Dialog functions:
			Single Progress Bar.
			Double Progress Bar
			Dialog with timer.
			Error Dialog with timer.
		Performance Patches for:
			bitmap rendering.
			image rendering.
		Implemented print function. now is a class.
	- 0.2.0 -
		Text rendering improved with performance test
		Fixed XMB Flip. Now is much more better.
		Added Printf functions.
			just initialize it: init_print(path_to_directory);
			write something to file: print("Hello World!\n");
			close the file: end_print();
		Added XMB Status
		Performance Patches for Font functions
	- 0.1.9 -
		Added Spu.cpp to use spu stuff
		Added NoRSX error list (incomplete)
	- 0.1.8 -
		Added Animation.cpp and Animation.h to create animations
		New Bitmap Functions
	- 0.1.6 -
		Added gradient for background color.
	- 0.1.5 -
		Now it's a real lib. to use it you will need to add in the Makefile the -lNoRSX flag
		New Header. now to include NoRSX inside your code, you will need to add the new header <NoRSX.h>
		Added EventHandler. it is included with <NoRSX.h> you don't need to use it. it's already configured by the lib.
	- 0.1.2 -
		Fixed Font ChromaKey. now fonts are better displayed 
	- 0.1.1e -
		Font Size..
	- 0.1.1d -
		Added PS3 Font PATHS
	- 0.1.1c -
		Performance Patch by KDSBest (Just for Images).
		Added DrawIMGtoBitmap function for JPG (I forgot this one!)
	- 0.1.1b -
		Fixed Screen Size bugs.
	- 0.1.1 -
		Added Change Screen Size.
		Screen Size Supported:
			RESOLUTION_1920x1080
			RESOLUTION_1280x720
			RESOLUTION_720x576
			RESOLUTION_720x480
			They needs to be initialized as this Example: NoRSX GFX(RESOLUTION_1280x720);
	- 0.1.0d -
		Performance Patch by Deroad/Wargio ~40 FPS.
	- 0.1.0c -
		Performance Patch by KDSBest (thanks for them. most of the stuffs that go to 24 FPS, now go to 30 FPS).
	- 0.1.0b -
		Fixed Bitmap when exit.
	- 0.1.0 -
		Added Bitmap!.
	- 0.0.9b -
		Added a few options!.
	- 0.0.9 -
		Now TTF support is perfect!
		Removed old font support.
	- 0.0.8 -
		Added TTF support (be careful when using it! it's still sperimental).
	- 0.0.7 -
		Added AlphaBlending (30 fps).
	- 0.0.6 -
		Added line.
	- 0.0.5c -
		Added AlphaBlending (15 fps).
	- 0.0.5b -
		Added Circle.
		Added Pixel4.
	- 0.0.5 -
		Added Printf to the Sperimental Text function.
		Added Pixel.
	- 0.0.4 -
		Added Msg dialog.
		Added Sperimental Text (NO FONTS for now).
		Added Partial Image function.
	- 0.0.3 -
		Background support.
		Can generate an object like rectangles
	- 0.0.2 -
		Now it loads everything correctly.
	- 0.0.1 -
		PNG/JPG support

Homebrews built with this lib:
------------------------------
	NoRSX Example  (deroad)
	PS Seismograph (deroad)
	XMB Manager Plus (XMBM+ Team)


Fonts
-----

All the fonts included with the example aren't mine..
 
