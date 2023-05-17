#include "BatteryManager.h"
#include "BatteryCommand.h"
#include "Utility.h"


// Constructor(s)
BatteryManager::BatteryManager(Stream *port) 
{
  // Constructor implementation
	dataStream = port;
  arrayPtr = result;
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
  positionCheckFunc(result,SOI,NUM_BYTE_1);
  Serial.print("\nVER: ");
  positionCheckFunc(result,VER,NUM_BYTE_2);
  Serial.print("\nADR: ");
  positionCheckFunc(result,ADR,NUM_BYTE_2);
  Serial.print("\nVol cell 1: ");
  positionCheckFunc(result,VOL_CELL_01 ,NUM_BYTE_4);
  Serial.print("\ntemp 1: ");
  positionCheckFunc(result,TEM_1 ,NUM_BYTE_4);
  Serial.print("\ncurrent: ");
  positionCheckFunc(result,CURRENT ,NUM_BYTE_4);
  Serial.print("\nTOT_VOL: ");
  positionCheckFunc(result,TOT_VOL ,NUM_BYTE_4);
  Serial.print("\nFULL_CAPACITY: ");
  positionCheckFunc(result,FULL_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nDES_CAPACITY: ");
  positionCheckFunc(result,DES_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nCHECKSUM: ");
  positionCheckFunc(result,CHECKSUM ,NUM_BYTE_4);
}

void BatteryManager::getAllValueIntoSubarray()
{
  Serial.print("\nSOI: ");
  extractSubarray(result,SOI,NUM_BYTE_1,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nVER: ");
  extractSubarray(result,VER,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nADR: ");
  extractSubarray(result,ADR,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nVol cell 1: ");
  extractSubarray(result,VOL_CELL_01 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\ntemp 1: ");
  extractSubarray(result,TEM_1 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\ncurrent: ");
  extractSubarray(result,CURRENT ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nTOT_VOL: ");
  extractSubarray(result,TOT_VOL ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nFULL_CAPACITY: ");
  extractSubarray(result,FULL_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nDES_CAPACITY: ");
  extractSubarray(result,DES_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  Serial.print("\nCHECKSUM: ");
  extractSubarray(result,CHECKSUM ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
}
