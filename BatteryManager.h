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

        void send_receive();

        BatteryStatus getBatteryStatus();
        void printBatteryStatus(BatteryStatus& batteryStatus);


        // Add more member functions as needed
        void checkAllTheValue();
        void getAllValueIntoSubarray();
        


        int8_t getNumberOfCell();
        float getCellVoltage(int8_t cellNumber); 
        int8_t getNumberOfTemperature();
        float getTemperatureReading(int8_t temperature_serial);
        float getPackCurrent();
        float getPackVoltage();
        float getRemainingCapacity();
        float getFullCapacity();
        float getDesignCapacity();
        int32_t getDischargeCycle();
        // TODO:
        uint32_t calculateChecksum();
        int32_t getCustomValue();

        

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
         * calculateActualVoltage - Converts the input voltage to actual voltage in float.
         * 
         * This function takes an input voltage as an integer value and converts it to
         * the actual voltage in float by dividing it by the voltage factor. The voltage
         * factor is used to scale the input voltage to the appropriate value.
         * 
         * @param input The input voltage as an integer value.
         * @return The actual voltage in float.
         */
        float calculateActualVoltage(int32_t input);
        float calculateActualTemperature(int32_t input);
        float calculateActualCurrent(int32_t input);
        float calculateActualCapacity(int32_t input);
        


	private:
        // Member variables
        // Add member variables as needed
		Stream *dataStream;
        char dataStreamBuffer[BUFFER_SIZE];
        char* arrayPtr;
        char output_arr_buf[10]; // handle subarray

};



#endif // BatteryManager_H