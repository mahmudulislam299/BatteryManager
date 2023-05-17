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
        void chargeBattery();
        void dischargeBattery();
        void getBatteryStatus();


        // Add more member functions as needed
        void checkAllTheValue();
        void getAllValueIntoSubarray();
        

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
        int32_t getCellVoltage(int8_t cellNumber);

        

    public: 
        // public Member variable

    private:
        // private memver functions


	private:
        // Member variables
        // Add member variables as needed
		Stream *dataStream;
        char* arrayPtr;
        char output_arr_buf[10]; // handle subarray

};
#endif // BatteryManager_H