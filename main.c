#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
	int opcija = 1;

	while (opcija != 99) {
		opcija = izbornik();
	}
	return 0;
}