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

    public: 
        // public Member variable

    private:
        // private memver functions


	private:
        // Member variables
        // Add member variables as needed
		Stream *dataStream;
        char* arrayPtr;

};
#endif // BatteryManager_H