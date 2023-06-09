#include "BatteryManager.h"
#include "BatteryCommand.h"
#include "Utility.h"

#define _DEBUG_

// Constructor(s)
BatteryManager::BatteryManager(Stream *port) 
{
  // Constructor implementation
	dataStream = port;
  arrayPtr = dataStreamBuffer;
}

// Destructor
BatteryManager::~BatteryManager() {
    // Destructor implementation
}

// Member functions implementation


void BatteryManager::clearStream()
{
  while (dataStream -> available())
  {
    dataStream -> read();
  }
}

void BatteryManager::clearBuffer(char *buffer, int bufferSize)
{
  memset(buffer,0,bufferSize);
}


void BatteryManager::printBuffer(char* buffer, int bufferSize) 
{
  Serial.print("print buffer: ");

  for (int i = 0; i < bufferSize; i++) 
  {
    Serial.print(buffer[i]);
  }
  Serial.println();
}


void BatteryManager::sendCommandToGetAllBatInfo() 
{
	Serial.println("sending data of value");
  
	for (int i = 0; i< sizeof(query3); i++)
  {
    dataStream->flush();
    dataStream->write(query3[i]);
    Serial.print(query3[i] , HEX);
    // Serial.print(query3[i]);
    Serial.print(" ");
  }
  Serial.println("");

}

// TODO: need to modify it
void BatteryManager::sendCommand(int8_t no) 
{  
    int len = sizeof(queryAll[no]) / sizeof(byte);
//    Serial.print("len :"); Serial.println(len);
    Serial.print("sending msg ");
    Serial.println(no);
    
    for (int i = 0; i<len ; i++)
    {
      if(queryAll[no][i] == 0)
      {
        break;
      }
      dataStream->flush();
      dataStream->write(queryAll[no][i]);
      Serial.print((char)queryAll[no][i]);
      // Serial.print(" ");
    }
    Serial.println("");

}





void BatteryManager::readDataStream(char* buffer, int bufferSize, unsigned long timeout)
{
  Serial.println("\nwaiting for data received");
  int index = 0;
  unsigned long start_time = millis();
  Serial.println("Received Data: ");
  while (millis() - start_time < timeout) 
  {
    if (dataStream->available() > 0) 
    {
      while (dataStream->available() > 0) 
      {
        
        char c = dataStream->read();
        buffer[index] = c;
        index++;
        //    Serial.print(c,HEX);
        Serial.print(c);
        // Serial.print(" ");
      }     
    }
  }

  buffer[index] = '\0';
  Serial.println(" ");
}

// TODO: function name should be changeds
void BatteryManager::send_receive(uint8_t queryNo)
{
  sendCommand(queryNo);
  clearBuffer(dataStreamBuffer,BUFFER_SIZE);
  printBuffer(dataStreamBuffer,BUFFER_SIZE);
  readDataStream(dataStreamBuffer,BUFFER_SIZE,500);
}

BatteryStatus BatteryManager::getBatteryStatus() 
{

  batteryStatus.numberOfCells = getNumberOfCell();
  batteryStatus.numberOfTemperatures = getNumberOfTemperature();
  
  for(int i = 1; i < 16; i++)
  {
    batteryStatus.cellVoltages[i]= getCellVoltage(i);
  }

  for(int i = 1; i <6; i++)
  {
    batteryStatus.temperatureReadings[i] = getTemperatureReading(i);
  }


  batteryStatus.packVoltage = getPackVoltage();
  batteryStatus.packCurrent = getPackCurrent();
  batteryStatus.remainingCapacity = getRemainingCapacity();
  batteryStatus.fullCapacity = getFullCapacity();
  batteryStatus.designCapacity = getDesignCapacity();
  batteryStatus.dischargeCycle = getDischargeCycle();
  // TODO: @mahmudulislam299
  // batteryStatus.checksum = 

    return batteryStatus;
   
}

void BatteryManager::printBatteryStatus(BatteryStatus& batteryStatus) 
{
  int i, j;
  Serial.println("Battery Status:");
  Serial.print("Number of Cells: ");
  Serial.println(batteryStatus.numberOfCells);

  Serial.println("Cell Voltages:");
  for (i = 1; i < 16; i++) 
  {
    Serial.print("Cell ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println((batteryStatus.cellVoltages[i]),3);
  }

  Serial.print("Number of Temperatures: ");
  Serial.println(batteryStatus.numberOfTemperatures);

  Serial.println("Temperature Readings:");
  for (j = 1; j < 7; j++) 
  {
    Serial.print("Temperature ");
    Serial.print(j);
    Serial.print(": ");
    Serial.println((batteryStatus.temperatureReadings[j]),3);
  }

  Serial.print("Pack Voltage: ");
  Serial.println(batteryStatus.packVoltage,3);
  Serial.print("Pack Current: ");
  Serial.println(batteryStatus.packCurrent,3);
  Serial.print("Remaining Capacity: ");
  Serial.println(batteryStatus.remainingCapacity,3);
  Serial.print("Full Capacity: ");
  Serial.println(batteryStatus.fullCapacity,3);
  Serial.print("Discharge Cycle: ");
  Serial.println(batteryStatus.dischargeCycle);
  Serial.print("Design Capacity: ");
  Serial.println(batteryStatus.designCapacity);
  Serial.print("Checksum: ");
  Serial.println(batteryStatus.checksum);
};


// Implement the remaining member functions here

void BatteryManager::checkAllTheValue()
{
  Serial.print("\nSOI: ");
  positionCheckFunc(dataStreamBuffer,SOI,NUM_BYTE_1);
  Serial.print("\nVER: ");
  positionCheckFunc(dataStreamBuffer,VER,NUM_BYTE_2);
  Serial.print("\nADR: ");
  positionCheckFunc(dataStreamBuffer,ADR,NUM_BYTE_2);
  Serial.print("\nVol cell 1: ");
  positionCheckFunc(dataStreamBuffer,VOL_CELL_01 ,NUM_BYTE_4);
  Serial.print("\ntemp 1: ");
  positionCheckFunc(dataStreamBuffer,TEM_1 ,NUM_BYTE_4);
  Serial.print("\ncurrent: ");
  positionCheckFunc(dataStreamBuffer,PACK_CURRENT ,NUM_BYTE_4);
  Serial.print("\nTOT_VOL: ");
  positionCheckFunc(dataStreamBuffer,PACK_VOLTAGE ,NUM_BYTE_4);
  Serial.print("\nFULL_CAPACITY: ");
  positionCheckFunc(dataStreamBuffer,FULL_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nDES_CAPACITY: ");
  positionCheckFunc(dataStreamBuffer,DES_CAPACITY ,NUM_BYTE_4);
  Serial.print("\nCHECKSUM: ");
  positionCheckFunc(dataStreamBuffer,CHECKSUM ,NUM_BYTE_4);
}

void BatteryManager::getAllValueIntoSubarray()
{
  int32_t outputDigit;

  Serial.print("\nSOI: ");
  extractSubarray(dataStreamBuffer,SOI,NUM_BYTE_1,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nVER: ");
  extractSubarray(dataStreamBuffer,VER,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nADR: ");
  extractSubarray(dataStreamBuffer,ADR,NUM_BYTE_2,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nVol cell 1: ");
  extractSubarray(dataStreamBuffer,VOL_CELL_01 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\ntemp 1: ");
  extractSubarray(dataStreamBuffer,TEM_1 ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\ncurrent: ");
  extractSubarray(dataStreamBuffer,PACK_CURRENT ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nTOT_VOL: ");
  extractSubarray(dataStreamBuffer,PACK_VOLTAGE ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nFULL_CAPACITY: ");
  extractSubarray(dataStreamBuffer,FULL_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nDES_CAPACITY: ");
  extractSubarray(dataStreamBuffer,DES_CAPACITY ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);

  Serial.print("\nCHECKSUM: ");
  extractSubarray(dataStreamBuffer,CHECKSUM ,NUM_BYTE_4,output_arr_buf);
  Serial.print(output_arr_buf);
  outputDigit = hexToDecimal(output_arr_buf);
  Serial.print(" = ");
  Serial.print(outputDigit);
}


int8_t BatteryManager::getNumberOfCell()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, NUM_PACK, NUM_BYTE_2, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int8_t num_of_cell = hexToDecimal(temp_buf);
  #if defined(_DEBUG_)
  Serial.print("number of cell: ");
  Serial.println(num_of_cell);
  #endif //!_DEBUG_

  return num_of_cell;
}

/**
 * getCellVoltage - Retrieves the voltage of a specific cell in the battery pack.
 * 
 * This function takes the cell number as input and returns the voltage of the corresponding cell
 * in the battery pack. The cell number should be within the range of 1 to 15.
 * 
 * @param cellNumber  The number of the cell to retrieve the voltage for.
 * @return The voltage of the specified cell, or -1 if the cell number is invalid or extraction fails.
 */
float BatteryManager::getCellVoltage(int8_t cellNumber)
{
  if (cellNumber < 1 || cellNumber > 16)
  {
    #if defined(_DEBUG_)
    Serial.println("invalid cell number");
    #endif //!_DEBUG_
    return -1; // Return -1 for invalid cell number
  }
  
  int startPos = VOL_CELL_ALL + ((cellNumber - 1) * NUM_BYTE_4);
  char cell_vol_buf[10];
  
  // Extract the subarray representing the voltage of the specified cell
  if (!extractSubarray(dataStreamBuffer, startPos, NUM_BYTE_4, cell_vol_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  // Convert the extracted subarray to a decimal value
  int32_t outputDigit = hexToDecimal(cell_vol_buf);

  // Calculate the actual voltage based on the decimal value
  float actualVoltage = calculateActualVoltage(outputDigit);
  
  #if defined(_DEBUG_)
  // Print the decimal value for debugging purposes
  Serial.print("Cell ");
  Serial.print(cellNumber);
  Serial.print(" Voltage = ");
  Serial.println(actualVoltage,3);
  #endif //!_DEBUG_

  return actualVoltage; // Return the voltage of the specified cell as a decimal value
}

/**
 * calculateActualVoltage - Converts the input voltage to actual voltage in float.
 * 
 * This function takes an input voltage as an integer value and converts it to
 * the actual voltage in float by dividing it by the voltage factor. The voltage
 * factor is used to scale the input voltage to the appropriate value.
 * 
 * @param input The input voltage as an integer value.
 * @return The actual voltage in float.
 */
float BatteryManager::calculateActualVoltage(int32_t input)
{
  // Convert the input voltage to actual voltage by dividing it by the voltage factor
  float output = (float)input / VOLTAGE_FACTOR;
  
  return output; // Return the actual voltage in float
}

int8_t BatteryManager::getNumberOfTemperature()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, NUM_TEM, NUM_BYTE_2, temp_buf))
  {
    #if defined(_DEBUG_)
    Serial.println("failed to get number of temperature");
    #endif //!_DEBUG_
    return -1; // Return -1 if extraction fails or invalid input

  }
  
  int8_t num_of_temp = hexToDecimal(temp_buf);
  #if defined(_DEBUG_)
  Serial.print("number of temp: ");
  Serial.println(num_of_temp);
  #endif //!_DEBUG_

  return num_of_temp;
}

float BatteryManager::getTemperatureReading(int8_t temperature_serial)
{
  if (temperature_serial < 1 || temperature_serial > 6)
  {
    #if defined(_DEBUG_)
    Serial.println("invalid temperature serial");
    #endif //!_DEBUG_

    return -1; // Return -1 for invalid temperature number
  }
  
  int startPos = TEM_ALL + ((temperature_serial - 1) * NUM_BYTE_4);
  char temp_buf[10];
  
  // Extract the subarray representing the voltage of the specified cell
  if (!extractSubarray(dataStreamBuffer, startPos, NUM_BYTE_4, temp_buf))
  {
    #if defined(_DEBUG_)
    Serial.print("failed to get temperature");
    Serial.println(temperature_serial);
    #endif //!_DEBUG_

    return -1; // Return -1 if extraction fails or invalid input
  }
  
  // Convert the extracted subarray to a decimal value
  int32_t outputDigit = hexToDecimal(temp_buf);

  // Calculate the actual voltage based on the decimal value
  // float actualVoltage = calculateActualVoltage(outputDigit);
  float actualTemp = calculateActualTemperature(outputDigit);
  
  #if defined(_DEBUG_)
  // Print the decimal value for debugging purposes
  Serial.print("Temperature ");
  Serial.print(temperature_serial);
  Serial.print(" = ");
  Serial.println(actualTemp,3);
  #endif //!_DEBUG_

  return actualTemp; // Return the voltage of the specified cell as a decimal value
}

float BatteryManager::calculateActualTemperature(int32_t input)
{
  
  float output = ((float)input - TEMPERATURE_FACTOR_1) / TEMPERATURE_FACTOR_2;  
  
  return output; 
}

float BatteryManager::getPackCurrent()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, PACK_CURRENT, NUM_BYTE_4, temp_buf))
  {
    #if defined(_DEBUG_)
    Serial.println("failed to get pack current");
    #endif //!_DEBUG_
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  

  float pack_current = calculateActualCurrent(output);
  #if defined(_DEBUG_)
  Serial.print("pack Current: ");
  Serial.println(pack_current);
  #endif //!_DEBUG_

  return pack_current;
}

float BatteryManager::getPackVoltage()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, PACK_VOLTAGE, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  float pack_voltage = calculateActualVoltage(output);
  #if defined(_DEBUG_)
  Serial.print("pack Voltage: ");
  Serial.println(pack_voltage,3);
  #endif //!_DEBUG_

  return pack_voltage;
}


float BatteryManager::getRemainingCapacity()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, REMAIN_CAPACITY, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  float remain_capacity = calculateActualCapacity(output);
  #if defined(_DEBUG_)
  Serial.print("remain capacity: ");
  Serial.println(remain_capacity,3);
  #endif //!_DEBUG_

  return remain_capacity;
}

float BatteryManager::calculateActualCurrent(int32_t input)
{
  float output = (float)input / CURRENT_FACTOR;
  return output;
}

float BatteryManager::calculateActualCapacity(int32_t input)
{
  float output = (float)input / CAPACITY_FACTOR;
  return output;
}


float BatteryManager::getFullCapacity()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, FULL_CAPACITY, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  float full_capacity = calculateActualCapacity(output);
  #if defined(_DEBUG_)
  Serial.print("full capacity: ");
  Serial.println(full_capacity,3);
  #endif //!_DEBUG_

  return full_capacity;
}

float BatteryManager::getDesignCapacity()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, DES_CAPACITY, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  float design_capacity = calculateActualCapacity(output);
  #if defined(_DEBUG_)
  Serial.print("design capacity: ");
  Serial.println(design_capacity,3);
  #endif //!_DEBUG_

  return design_capacity;
}

int32_t BatteryManager::getDischargeCycle()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, DIS_CYCLE, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  //TODO: check this actual value
  return output;
}

uint32_t BatteryManager::calculateChecksum()
{
  //TODO:
}

int32_t BatteryManager::getCustomValue()
{
  char temp_buf[10];
  
  if (!extractSubarray(dataStreamBuffer, CUSTOM, NUM_BYTE_4, temp_buf))
  {
    return -1; // Return -1 if extraction fails or invalid input
  }
  
  int32_t output = hexToDecimal(temp_buf);
  //TODO: check this actual value
  return output;
}