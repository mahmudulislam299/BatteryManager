#include "Utility.h"

char postionCheckFunc(char *arr, int postion, int num_byte)
{
	for(int i =0 ; i < num_byte; i++)
	{
		Serial.print(arr[postion+i]);
	}
	Serial.println();
}
