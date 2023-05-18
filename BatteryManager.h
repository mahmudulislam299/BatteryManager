#ifndef BatteryManager_H
#define BatteryManager_H

#include <Arduino.h>

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

        void readDataStream(char* buffer, int bufferSize = 256, unsigned long timeout = 5000);
        void readDataStream2(char* buffer, int bufferSize = 256, unsigned long timeout = 5000);

        void send_receive();

        void dischargeBattery();
        void getBatteryStatus();


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
        float getTemperature(int8_t temperature_serial);
        float getPackCurrent();
        float getPackVoltage();
        float getRemainingCapacity();

        

    public: 
        // public Member variable

    private:
        // private memver functions

        //
        void clearBufferStream();

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
        char dataStreamBuffer[256];
        char* arrayPtr;
        char output_arr_buf[10]; // handle subarray

};
#endif // BatteryManager_H