#include "gc.h"

int main(int, char *argv[]){	
	ifstream fin;
	GCContentCalculator gcalc; 
	fin.open(argv[1]);
	gcalc.popTable(fin);
	gcalc.printLargestFrequency();
}
