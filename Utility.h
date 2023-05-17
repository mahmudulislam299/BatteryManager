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
 * extractSubarray - Extracts a subarray from the input array based on the specified start position and size.
 * 
 * @param input     The input character array.
 * @param startPos  The starting position of the subarray.
 * @param size      The size of the subarray to extract.
 * @param output    The output character array to store the extracted subarray.
 * @return None.
 */
void extractSubarray(const char* input, int startPos, int size, char* output);

/**
 * hexToDecimal - Converts a hexadecimal string to a decimal integer.
 * 
 * @param hexString  The input hexadecimal string.
 * @return The decimal value converted from the input string.
 */
int32_t hexToDecimal(const char* hexString);

#endif // !UTILITY_H
