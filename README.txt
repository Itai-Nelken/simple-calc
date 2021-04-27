SIMPLE CALC
===========
simple-calc by Itai-Nelken.

compiling, installing, & uninstalling:
---------------------------------------
DEPENDENCIES:
cmake<=1.16
make (oldest version known to work is 3.81)
a C compiler like gcc.

COMFIGURING:
from the root of the 'simple-calc' folder, run the following:
	mkdir build; cd build; cmake ..

COMPILING:
run the following:
	make
RUNNING:
you can now run the executable directly with:
	./simple-calc

INSTALLING:
run the following from the build folder:
	sudo make install
now you can start simple-calc from the shell (terminal) with this command: simple-calc

UNINSTALLING:
to uninstall, run the following from the build folder:
	sudo make uninstall
alternatively, delete /usr/local/bin/simple-calc

***

