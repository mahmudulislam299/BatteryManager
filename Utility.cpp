#include "Utility.h"

void positionCheckFunc(char *arr, int postion, int num_byte)
{
	for(int i =0 ; i < num_byte; i++)
	{
		Serial.print(arr[postion+i]);
	}
	Serial.println();
}


bool extractSubarray(const char* input, int startPos, int size, char* output) 
{
  // Check if the input array is empty or NULL
  if (input == NULL || input[0] == '\0')
  {
    return false; // Return false for invalid input
  }

  // Check if the starting position is valid
  if (startPos < 0 || startPos >= strlen(input))
  {
    return false; // Return false for invalid starting position
  }

  // Check if the size is valid
  if (size <= 0 || startPos + size > strlen(input))
  {
    return false; // Return false for invalid size
  }

  // Extract the subarray
  int j = 0;
  for (int i = startPos; i < startPos + size; i++) {
    output[j] = input[i];
    j++;
  }
  output[j] = '\0'; // Null-terminate the output array

	// Serial.print("output hex: ");
	// Serial.println(output);

  return true; // Return true for successful extraction
}

int32_t hexToDecimal(const char* hexString) 
{
  // Check if the input string is empty or NULL
  if (hexString == NULL || hexString[0] == '\0')
  {
    return -1; // Return -1 for invalid input
  }

  // Verify if the input string is a valid hexadecimal representation
  for (int i = 0; hexString[i] != '\0'; i++)
  {
    if (!isxdigit(hexString[i]))
    {
      return -1; // Return -1 for invalid input
    }
  }

  int32_t decimalValue = strtol(hexString, NULL, 16);
  return decimalValue;
}