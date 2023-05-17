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
  postionCheckFunc(result,SOI,NUM_BYTE_1);
  Serial.print("\nVER: ");
  postionCheckFunc(result,VER,NUM_BYTE_2);
  Serial.print("\nADR: ");
  postionCheckFunc(result,ADR,NUM_BYTE_2);
  Serial.print("\nVol cell 1: ");
  postionCheckFunc(result,VOL_CELL_01 ,NUM_BYTE_4);
  Serial.print("\ntemp 1: ");
  postionCheckFunc(result,TEM_1 ,NUM_BYTE_4);
  Serial.print("\ncurrent: ");
  postionCheckFunc(result,CURRENT ,NUM_BYTE_4);
  Serial.print("\nTOT_VOL: ");
  postionCheckFunc(result,TOT_VOL ,NUM_BYTE_4);
  Serial.print("\nFULL_CAPACITY: ");
  postionCheckFunc(result,FULL_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nDES_CAPACITY: ");
  postionCheckFunc(result,DES_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nCHECKSUM: ");
  postionCheckFunc(result,CHECKSUM ,NUM_BYTE_4);
}

