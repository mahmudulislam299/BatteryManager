#include "BatteryManager.h"
#include "BatteryCommand.h"
#include "Utility.h"


// Constructor(s)
BatteryManager::BatteryManager(Stream *port) 
{
  // Constructor implementation
	dataStream = port;
  arrayPtr = qryRestult;
}

// Destructor
BatteryManager::~BatteryManager() {
    // Destructor implementation
}

// Member functions implementation
void BatteryManager::chargeBattery() 
{
	Serial.println("sending data of value");
	for (int i = 0; i< sizeof(query1); i++)
  {
    dataStream->flush();
    dataStream->write(query1[i]);
    // Serial.print(query1[i], HEX);
    Serial.print(query1[i]);
    Serial.print(" ");
  }

}

void BatteryManager::dischargeBattery() {
    // Implementation of dischargeBattery()
}

void BatteryManager::getBatteryStatus() {
    // Implementation of getBatteryStatus()

		Serial.println("battery ok");
}

// Implement the remaining member functions here

void BatteryManager::checkAllTheValue()
{
  Serial.print("\nSOI: ");
  positionCheckFunc(qryRestult,SOI,NUM_BYTE_1);
  Serial.print("\nVER: ");
  positionCheckFunc(qryRestult,VER,NUM_BYTE_2);
  Serial.print("\nADR: ");
  positionCheckFunc(qryRestult,ADR,NUM_BYTE_2);
  Serial.print("\nVol cell 1: ");
  positionCheckFunc(qryRestult,VOL_CELL_01 ,NUM_BYTE_4);
  Serial.print("\ntemp 1: ");
  positionCheckFunc(qryRestult,TEM_1 ,NUM_BYTE_4);
  Serial.print("\ncurrent: ");
  positionCheckFunc(qryRestult,CURRENT ,NUM_BYTE_4);
  Serial.print("\nTOT_VOL: ");
  positionCheckFunc(qryRestult,TOT_VOL ,NUM_BYTE_4);
  Serial.print("\nFULL_CAPACITY: ");
  positionCheckFunc(qryRestult,FULL_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nDES_CAPACITY: ");
  positionCheckFunc(qryRestult,DES_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nCHECKSUM: ");
  positionCheckFunc(qryRestult,CHECKSUM ,NUM_BYTE_4);
}

void BatteryManager::getAllValueIntoSubarray()
{
  int32_t outputDigit;

  Serial.print("\nSOI: ");
  extractSubarray(qryRestult,SOI,NUM_BYTE_1,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nVER: ");
  extractSubarray(qryRestult,VER,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nADR: ");
  extractSubarray(qryRestult,ADR,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nVol cell 1: ");
  extractSubarray(qryRestult,VOL_CELL_01 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\ntemp 1: ");
  extractSubarray(qryRestult,TEM_1 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\ncurrent: ");
  extractSubarray(qryRestult,CURRENT ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nTOT_VOL: ");
  extractSubarray(qryRestult,TOT_VOL ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nFULL_CAPACITY: ");
  extractSubarray(qryRestult,FULL_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nDES_CAPACITY: ");
  extractSubarray(qryRestult,DES_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nCHECKSUM: ");
  extractSubarray(qryRestult,CHECKSUM ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);
}





/**
 * getCellVoltage - Retrieves the voltage of a specific cell.
 * 
 * This function extracts the subarray from the query result array that represents the voltage
 * of the specified cell. The extracted subarray is then converted to a decimal value using the 
 * hexToDecimal function. The decimal value is returned as the voltage of the specified cell.
 * 
 * @param cellNumber The number of the cell to retrieve the voltage for.
 * @return The voltage of the specified cell as a decimal value. Returns -1 if extraction fails or invalid input.
 */
int32_t BatteryManager::getCellVoltage(int8_t cellNumber)
{
  if (cellNumber < 1 || cellNumber > 15)
  {
    return -1; // Return -1 for invalid cell number
  }
  
  int startPos = VOL_CELL_ALL + ((cellNumber - 1) * NUM_BYTE_4);
  char cell_vol_buf[10];
  
  // Extract the subarray representing the voltage of the specified cell
  if (!extractSubarray(qryRestult, startPos, NUM_BYTE_4, cell_vol_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  // Convert the extracted subarray to a decimal value
  int32_t outputDigit = hexToDecimal(cell_vol_buf);
  
  // Print the decimal value for debugging purposes
  Serial.print("Cell ");
  Serial.print(cellNumber);
  Serial.print(" Voltage = ");
  Serial.println(outputDigit);

  return outputDigit; // Return the voltage of the specified cell as a decimal value
}