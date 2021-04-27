#include <stdio.h>
#include "calc.h"

void help() {
	printf("\e[1mUSAGE:\e[0m %s [num1] [operation] [num2]\n", PROGEXECNAME);
	printf("\e[1mOPERATIONS:\e[0m +, -, x, /.  x=*\n");
}
