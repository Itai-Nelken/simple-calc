#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

//using argv[2][0] or *argv[2] is the same

int main(int argc, char **argv) {
	float num1, num2;
	if(argc>1 && !strcmp(argv[1], "--help")) {
		help();
		return 0;
	}
	while(argc==4) {
		num1=atoi(argv[1]);
		num2=atoi(argv[3]);
		if(argv[2][0]=='+') {
			printf("%.3f + %.3f = \e[1m%.3f\e[0m\n", num1, num2, num1+num2);
			break;
		} else if(*argv[2]=='-') {
			printf("%.3f - %.3f = \e[1m%.3f\e[0m\n", num1, num2, num1-num2);
			break;
		} else if(*argv[2]=='x'|| *argv[2]=='*') {
			printf("%.3f * %.3f = \e[1m%.3f\e[0m\n", num1, num2, num1*num2);
			break;
		} else if(*argv[2]=='/') {
			printf("%.3f / %.3f = \e[1m%.3f\e[0m\n", num1, num2, num1/num2);
			break;
		} else {
			fprintf(stderr, "\e[31m\e[1mInvalid operation!\e[0m\n");
			break;
		}
	}
	if(argc==1) {
		help();
	}
	return 0;
}
