#include "utils.h"

void float_to_str(char *str, float f)
{
	long int i;
	signed char j, k;
	unsigned char pos = 0;
	char tempstr[16];
	
	if (f >= 0)
		i = (long int)(f * 100.0f + 0.5f);
	else
		i = (long int)(f * 100.0f - 0.5f);
	if (i < 0) {
		str[0] = '-';
		pos = 1;
		i = -i;
	}
	
	for (j=0; j<15; j++) {
		k = i % 10;
		tempstr[j] = k + '0';
		i = i / 10;
		if (i == 0 && j >= 2)
			break;
	}
	tempstr[j+1] = '\0';

	for (k=j; k>=0; k--) {
		str[pos] = tempstr[k];
		if (k == 2) {
			pos++;
			str[pos] = '.';
		}
		pos++;
	}
	if (f >= 0) {
		str[j+2] = '\0';
		//return j+2;
	}
	else {
		str[j+3] = '\0';
		//return j+3;
	}
}


void int_to_str(char *str, long int i)
{
	signed char j, k;
	unsigned char pos = 0;
	char tempstr[16];
	
	if (i < 0) {
		str[0] = '-';
		pos = 1;
		i = -i;
	}
	
	for (j=0; j<15; j++) {
		k = i % 10;
		tempstr[j] = k + '0';
		i = i / 10;
		if (i == 0)
			break;
	}
	tempstr[j+1] = '\0';

	for (k=j; k>=0; k--) {
		str[pos] = tempstr[k];
		pos++;
	}
	if (str[0] != '-') {
		str[j+1] = '\0';
		//return j+1;
	}
	else {
		str[j+2] = '\0';
		//return j+2;
	}
}


void delay_ms(uint16_t ms)
{
	uint32_t i, j;
	j = ms * 19200; // j = ms / 1000.0 * 48000000 / 2.5;  
	for (i=0; i<j; i++) {
	}
}
