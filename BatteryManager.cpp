#include "BatteryManager.h"
#include "BatteryCommand.h"


// Constructor(s)
BatteryManager::BatteryManager(Stream *port) 
{
  // Constructor implementation
	dataStream = port;
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

