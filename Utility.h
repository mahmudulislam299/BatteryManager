#ifndef UTILITY_H
#define UTILITY_h

#include <Arduino.h>

/**
 * positionCheckFunc - Print the specified number of bytes from the given array starting at the specified position.
 * 
 * @param arr       The input character array.
 * @param position  The starting position to print from.
 * @param num_byte  The number of bytes to print.
 * @return None.
 */
void positionCheckFunc(char* arr, int position, int num_byte);

/**
 * extractSubarray - Extracts a subarray from the input array.
 * 
 * This function extracts a subarray from the input array based on the specified
 * starting position and size. The extracted subarray is stored in the output array.
 * 
 * @param input     The input array.
 * @param startPos  The starting position of the subarray.
 * @param size      The size of the subarray.
 * @param output    The output array to store the extracted subarray.
 * @return True if the extraction is successful, false otherwise.
 */
bool extractSubarray(const char* input, int startPos, int size, char* output);

/**
 * hexToDecimal - Converts a hexadecimal string to a decimal integer.
 * 
 * This function takes a hexadecimal string as input and converts it to a decimal
 * integer value. It performs the conversion using the strtol function from the
 * standard library.
 * 
 * @param hexString  The input hexadecimal string.
 * @return The decimal value converted from the input string. Returns -1 for invalid input.
 */
int32_t hexToDecimal(const char* hexString);

#endif // !UTILITY_H
