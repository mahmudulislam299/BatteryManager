#ifndef BATTERYCOMMAND_H
#define BATTERYCOMMAND_H


const byte query1[] PROGMEM = { 0x7E, 0x32, 0x35, 0x30, 0x31, 0x34, 0x36, 0x43, 0x32, 0x30, 0x30, 0x30, 0x30, 0x46, 0x44, 0x39, 0x39, 0x0D};
const byte query2[] PROGMEM = { 0x7E, 0x32, 0x35, 0x30, 0x31, 0x34, 0x36, 0x43, 0x31, 0x30, 0x30, 0x30, 0x30, 0x46, 0x44, 0x39, 0x41, 0x0D};
const byte query3[] PROGMEM = { 0x7E, 0x32, 0x35, 0x30, 0x31, 0x34, 0x36, 0x34, 0x32, 0x45, 0x30, 0x30, 0x32, 0x30, 0x31, 0x46, 0x44, 0x33, 0x30, 0x0D};
const byte query4[] PROGMEM = { 0x7E, 0x32, 0x35, 0x30, 0x31, 0x34, 0x36, 0x34, 0x34, 0x45, 0x30, 0x30, 0x32, 0x30, 0x31, 0x46, 0x44, 0x32, 0x45, 0x0D};

char qryRestult[] = "~250F4600307600010F0CAA0CA40CAD0CAC0CAF0CAD0CA30CAC0CAD0CAB0CA90CA40CA80CAC0CA5060BCD0BC80BCA0BC20BB80BEE0000BDF009C403271000002710E2C3";

#define NUM_BYTE_1 						01
#define NUM_BYTE_2 						02
#define NUM_BYTE_4 						04
#define VOLTAGE_FACTOR 				1000
#define TEMPERATURE_FACTOR_1	2730
#define TEMPERATURE_FACTOR_2	10

// position
#define SOI 					00
#define VER 					01
#define ADR 					03
#define	CID1 					05
#define CID2					07
#define	LEN						09
#define	INFO					13
#define	idk						15
#define NUM_PACK			17
#define	VOL_CELL_ALL	19
#define VOL_CELL_01		VOL_CELL_ALL + NUM_BYTE_4 * 00
#define VOL_CELL_02		VOL_CELL_ALL + NUM_BYTE_4 * 01			
#define VOL_CELL_03		VOL_CELL_ALL + NUM_BYTE_4 * 02
#define VOL_CELL_04		VOL_CELL_ALL + NUM_BYTE_4 * 03
#define VOL_CELL_05		VOL_CELL_ALL + NUM_BYTE_4 * 04
#define VOL_CELL_06		VOL_CELL_ALL + NUM_BYTE_4 * 05
#define VOL_CELL_07		VOL_CELL_ALL + NUM_BYTE_4 * 06
#define VOL_CELL_08		VOL_CELL_ALL + NUM_BYTE_4 * 07
#define VOL_CELL_09		VOL_CELL_ALL + NUM_BYTE_4 * 08
#define VOL_CELL_10		VOL_CELL_ALL + NUM_BYTE_4 * 09
#define VOL_CELL_11		VOL_CELL_ALL + NUM_BYTE_4 * 10
#define VOL_CELL_12		VOL_CELL_ALL + NUM_BYTE_4 * 11
#define VOL_CELL_13		VOL_CELL_ALL + NUM_BYTE_4 * 12
#define VOL_CELL_14		VOL_CELL_ALL + NUM_BYTE_4 * 13
#define VOL_CELL_15		VOL_CELL_ALL + NUM_BYTE_4 * 14
#define NUM_TEM				79
#define	TEM_ALL				81
#define	TEM_1					TEM_ALL + NUM_BYTE_4 * 00
#define TEM_2					TEM_ALL + NUM_BYTE_4 * 01
#define TEM_3					TEM_ALL + NUM_BYTE_4 * 02	
#define TEM_4					TEM_ALL + NUM_BYTE_4 * 03	
#define TEM_5					TEM_ALL + NUM_BYTE_4 * 04	
#define TEM_6					TEM_ALL + NUM_BYTE_4 * 05					
#define	CURRENT				105
#define TOT_VOL				109
#define CAPACITY			113
#define CUSTOM				117
#define FULL_CAPACITY	119
#define DIS_CYCLE			123
#define DES_CAPACITY	127
#define CHECKSUM			131




#endif // BATTERYCOMMAND_H