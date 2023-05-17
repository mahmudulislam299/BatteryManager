#include "Utility.h"

char postionCheckFunc(char *arr, int postion, int num_byte)
{
	for(int i =0 ; i < num_byte; i++)
	{
		Serial.print(arr[postion+i]);
	}
	Serial.println();
}


void extractSubarray(const char* input, int startPos, int size, char* output) 
{
  int endPos = startPos + size;

  // Extract the subarray
  int j = 0;
  for (int i = startPos; i < endPos; i++) {
    output[j] = input[i];
    j++;
  }
  output[j] = '\0'; // Null-terminate the output array
}



// void loop() {
//   char arr[] = "~250F46003076000";
//   char output_arr[10]; // Adjust the size as per your requirement

//   extractSubarray(arr, 1, 4, output_arr);

//   Serial.println(output_arr); // Print the extracted subarray
//   delay(1000);
// }
