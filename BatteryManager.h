#ifndef BatteryManager_H
#define BatteryManager_H

#include <Arduino.h>

#define BUFFER_SIZE 256
#define COMM_TIMEOUT 1000


struct BatteryStatus 
{
  uint8_t numberOfCells;
  float cellVoltages[16];
  uint8_t numberOfTemperatures;
  float temperatureReadings[6];
  float packVoltage;
  float packCurrent;
  float remainingCapacity;
  float fullCapacity;
  uint32_t dischargeCycle;
  float designCapacity;
  uint16_t checksum;
};

class BatteryManager 
{
	public:
    // Constructor(s)
    BatteryManager(Stream *port);

    // Destructor
    ~BatteryManager();

    public:
        // public Member functions
        void sendCommandToGetAllBatInfo();
        void sendCommand(int8_t no);

        void readDataStream(char* buffer, int bufferSize = BUFFER_SIZE, unsigned long timeout = 1000);
        void readDataStream2(char* buffer, int bufferSize = BUFFER_SIZE, unsigned long timeout = 1000);

        void send_receive();

        void dischargeBattery();
        BatteryStatus getBatteryStatus();


        // Add more member functions as needed
        void checkAllTheValue();
        void getAllValueIntoSubarray();
        


        int8_t getNumberOfCell();

        /**
         * getCellVoltage - Retrieves the voltage of a specific cell in the battery pack.
         * 
         * This function takes the cell number as input and returns the voltage of the corresponding cell
         * in the battery pack. The cell number should be within the range of 1 to 15.
         * 
         * @param cellNumber  The number of the cell to retrieve the voltage for.
         * @return The voltage of the specified cell, or -1 if the cell number is invalid or extraction fails.
         */
        float getCellVoltage(int8_t cellNumber); 
        int8_t getNumberOfTemperature();
        float getTemperatureReading(int8_t temperature_serial);
        float getPackCurrent();
        float getPackVoltage();
        float getRemainingCapacity();

        

    public: 
        // public Member variable
         BatteryStatus batteryStatus;

    private:
        // private memver functions

        //
        void clearStream();
        void clearBuffer(char *buffer, int bufferSize);
        void printBuffer(char* buffer, int bufferSize); 

        /**
         * getActualVoltage - Converts the input voltage to actual voltage in float.
         * 
         * This function takes an input voltage as an integer value and converts it to
         * the actual voltage in float by dividing it by the voltage factor. The voltage
         * factor is used to scale the input voltage to the appropriate value.
         * 
         * @param input The input voltage as an integer value.
         * @return The actual voltage in float.
         */
        float getActualVoltage(int32_t input);
        float getActualTemperature(int32_t input);
        


	private:
        // Member variables
        // Add member variables as needed
		Stream *dataStream;
        char dataStreamBuffer[BUFFER_SIZE];
        char* arrayPtr;
        char output_arr_buf[10]; // handle subarray

};



#endif // BatteryManager_H