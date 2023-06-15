#include <tonc.h>
#include <string>
#include "mirror.h"
#include "gba_flash.h"
#include "debug.h"

char arr[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char intToHex(unsigned int num)
{
	return arr[num];
}

void printValueAt(vu32 testAdd)
{
	u8 mem[4];

	if (!flash_read(testAdd, &mem[0], 0x04))
	{
		vu32 testNum = *(vu32 *)mem;

		char output[22] = {
			'$',
			intToHex(testAdd >> 28 & 0xF),
			intToHex(testAdd >> 24 & 0xF),
			intToHex(testAdd >> 20 & 0xF),
			intToHex(testAdd >> 16 & 0xF),
			intToHex(testAdd >> 12 & 0xF),
			intToHex(testAdd >> 8 & 0xF),
			intToHex(testAdd >> 4 & 0xF),
			intToHex(testAdd >> 0 & 0xF),
			' ', '=', ' ',
			'0', 'x',
			intToHex(testNum >> 4  & 0xF),
			intToHex(testNum >> 0  & 0xF),
			intToHex(testNum >> 12 & 0xF),
			intToHex(testNum >> 8  & 0xF),
			intToHex(testNum >> 20 & 0xF),
			intToHex(testNum >> 16 & 0xF),
			intToHex(testNum >> 28 & 0xF),
			intToHex(testNum >> 24 & 0xF)};
		tte_write(output);
	}
	else
	{
		char error[17] = {'$',
			intToHex(testAdd >> 28 & 0xF),
			intToHex(testAdd >> 24 & 0xF),
			intToHex(testAdd >> 20 & 0xF),
			intToHex(testAdd >> 16 & 0xF),
			intToHex(testAdd >> 12 & 0xF),
			intToHex(testAdd >> 8 & 0xF),
			intToHex(testAdd >> 4 & 0xF),
			intToHex(testAdd >> 0 & 0xF),
			' ', '=', ' ','E', 'R', 'R', 'O', 'R'};
		tte_write(error);
	}
}

std::string u8ToHexStr(vu8 inputNum){
	std::string output = "";
	for (int i = 0; i < 2; i++){
		output = arr[(inputNum>>(i*4)) & 0xF] + output;
	}
	return "0x" + output;
}