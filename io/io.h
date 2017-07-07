#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>
#include <limits.h>
#include <ctype.h>

#include "random.h"

#define MAX_string 30		//lunghezza massima delle stringhe

void io_getString(char *string, int length);

int io_getInteger();

char io_getChar();

int io_fgetInteger(FILE *file);


void io_clearScreen();

void io_pressKey();

void check_cursor(char cursor);

#endif
