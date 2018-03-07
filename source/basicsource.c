
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
extern unsigned int charData[2048];
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160
#define SCREEN_HEIGHT_BOT 0
#define SCREEN_WIDTH_BOT 0


//#include <stdio.h>


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	
	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	irqInit();
	irqEnable(IRQ_VBLANK);

	// generic setup function
	//consoleDemoInit();
	
	//Creating Int values for object and background Tile data and setting it to the hex data.
	unsigned int * obj = (unsigned int *)0x06010020;
	unsigned int * background = (unsigned int *)0x06000000;
	
	//setting the character choice int to 0 (being used as a bool value).
	unsigned int CharacterChoice = 0;

	//Setting up my key values for GBA.
	unsigned short keys;
	
	//Creating a 32bit short value to hold my colourPallet and setting it to the Hex value in memory.
	unsigned short * colourPallet = (unsigned short *)0x05000000;
	unsigned short * colourPalletOBJ = (unsigned short *)0x05000200;
	unsigned short * OAM = (unsigned short *)0x07000000;
	
	
	
	unsigned short * DISPCNT = (unsigned short *)0x4000000;
	unsigned short * BG0CNT = (unsigned short *)0x04000008;
	unsigned short * BG1CNT = (unsigned short *)0x0400000A;
	unsigned short * BG2CNT = (unsigned short *)0x0400000C;
	unsigned short * BG3CNT = (unsigned short *)0x0400000E;
	
	
	DISPCNT[0] = ((1 << 6) | (1 << 8) | (0 << 9) | (0 << 10) | (0 << 11)|(1 << 12));
	
	int i;
	
	//Assigning my external charData to the Background and Object map memory.
	for (i = 0; i < 2048; i++)
	{
		background[i] = charData[i];
		obj[i] = charData[i];
	}
	
	//Setting my colour Pallet based upon RGB values in Paint.
	colourPallet[0] = ((31 << 0) | (31 << 5) | (31 << 10));
	colourPallet[1] = ((15 << 0) | (15 << 5) | (15 << 10));
	colourPallet[2] = ((17 << 0) | (0 << 5) | (3 << 10));
	colourPallet[3] = ((29 << 0) | (3 << 5) | (4 << 10));
	colourPallet[4] = ((31 << 0) | (29 << 5) | (0 << 10));
	colourPallet[5] = ((4 << 0) | (22 << 5) | (9 << 10));
	colourPallet[6] = ((0 << 0) | (20 << 5) | (28 << 10));
	colourPallet[7] = ((8 << 0) | (9 << 5) | (25 << 10));
	colourPallet[8] = ((17 << 0) | (9 << 5) | (20 << 10));
	colourPallet[9] = ((22 << 0) | (15 << 5) | (11 << 10));
	colourPallet[10] = ((31 << 0) | (21 << 5) | (24 << 10));
	colourPallet[11] = ((13 << 0) | (8 << 5) | (6 << 10));
	colourPallet[12] = ((22 << 0) | (28 << 5) | (4 << 10));
	colourPallet[13] = ((31 << 0) | (16 << 5) | (0 << 10));
	colourPallet[14] = ((31 << 0) | (21 << 5) | (24 << 10));
	colourPallet[15] = ((13 << 0) | (8 << 5) | (6 << 10));
	
	colourPalletOBJ[0] = ((31 << 0) | (31 << 5) | (31 << 10));
	colourPalletOBJ[1] = ((15 << 0) | (15 << 5) | (15 << 10));
	colourPalletOBJ[2] = ((17 << 0) | (0 << 5) | (3 << 10));
	colourPalletOBJ[3] = ((29 << 0) | (3 << 5) | (4 << 10));
	colourPalletOBJ[4] = ((31 << 0) | (29 << 5) | (0 << 10));
	colourPalletOBJ[5] = ((4 << 0) | (22 << 5) | (9 << 10));
	colourPalletOBJ[6] = ((0 << 0) | (20 << 5) | (28 << 10));
	colourPalletOBJ[7] = ((8 << 0) | (9 << 5) | (25 << 10));
	colourPalletOBJ[8] = ((17 << 0) | (9 << 5) | (20 << 10));
	colourPalletOBJ[9] = ((22 << 0) | (15 << 5) | (11 << 10));
	colourPalletOBJ[10] = ((31 << 0) | (21 << 5) | (24 << 10));
	colourPalletOBJ[11] = ((13 << 0) | (8 << 5) | (6 << 10));
	colourPalletOBJ[12] = ((22 << 0) | (28 << 5) | (4 << 10));
	colourPalletOBJ[13] = ((31 << 0) | (16 << 5) | (0 << 10));
	colourPalletOBJ[14] = ((31 << 0) | (21 << 5) | (24 << 10));
	colourPalletOBJ[15] = ((13 << 0) | (8 << 5) | (6 << 10));
	
	//Bitshifting my layer setups for background layers 0 through to 3.
	BG0CNT[0] = ((0 << 0) | (0 << 2) | (11 << 8) | (0 << 14));
	BG1CNT[1] = ((1 << 0) | (0 << 2) | (10 << 8) | (0 << 14));
	BG2CNT[2] = ((2 << 0) | (0 << 2) | (9 << 8) | (0 << 14));
	BG3CNT[3] = ((3 << 0) | (0 << 2) | (8 << 8) | (0 << 14));
	
	
	//creating 2 32bit short values, 1 for each characters base block


	//setting the spawn position of 2 characters (X and Y co-ordinates)
	int p1x = 20;
	int p2x = 20;
	
	//Blue Char
	OAM[0] = 50;
	OAM[1] = ((20 << 8) | (1 << 14));
	OAM[2] = 5;
	OAM[3] = 0;
	//Red Char
	OAM[4] = 10;
	OAM[5] = ((20 << 8) | (1 << 14));
	OAM[6] = 12;
	OAM[7] = 0;
	
	int Walls;
	int x;
	
	//Walls Top Row
	OAM[8] = 0;
	OAM[9] = 0;
	OAM[10] = 2;
	OAM[11] = 0;
	
	OAM[12] = 0;
	OAM[13] = 8;
	OAM[14] = 2;
	OAM[15] = 0;
	
	OAM[16] = 0;
	OAM[17] = 16;
	OAM[18] = 2;
	OAM[19] = 0;
	
	OAM[20] = 0;
	OAM[21] = 24;
	OAM[22] = 2;
	OAM[23] = 0;
	
	OAM[24] = 0;
	OAM[25] = 32;
	OAM[26] = 2;
	OAM[27] = 0;
	
	OAM[28] = 0;
	OAM[29] = 40;
	OAM[30] = 2;
	OAM[31] = 0;
	
	OAM[32] = 0;
	OAM[33] = 48;
	OAM[34] = 2;
	OAM[35] = 0;
	
	OAM[36] = 0;
	OAM[37] = 56;
	OAM[38] = 2;
	OAM[39] = 0;
	
	OAM[40] = 0;
	OAM[41] = 64;
	OAM[42] = 2;
	OAM[43] = 0;
	
	OAM[44] = 0;
	OAM[45] = 72;
	OAM[46] = 2;
	OAM[47] = 0;
	
	OAM[48] = 0;
	OAM[49] = 80;
	OAM[50] = 2;
	OAM[51] = 0;
	
	OAM[52] = 0;
	OAM[53] = 88;
	OAM[54] = 2;
	OAM[55] = 0;
	
	OAM[56] = 0;
	OAM[57] = 96;
	OAM[58] = 2;
	OAM[59] = 0;
	
	OAM[60] = 0;
	OAM[61] = 104;
	OAM[62] = 2;
	OAM[63] = 0;
	
	OAM[64] = 0;
	OAM[65] = 112;
	OAM[66] = 2;
	OAM[67] = 0;
	
	OAM[68] = 0;
	OAM[69] = 120;
	OAM[70] = 2;
	OAM[71] = 0;
	
	OAM[72] = 0;
	OAM[73] = 128;
	OAM[74] = 2;
	OAM[75] = 0;
	
	OAM[76] = 0;
	OAM[77] = 136;
	OAM[78] = 2;
	OAM[79] = 0;
	
	OAM[80] = 0;
	OAM[81] = 142;
	OAM[82] = 2;
	OAM[83] = 0;
	
	OAM[83] = 0;
	OAM[85] = 150;
	OAM[86] = 2;
	OAM[87] = 0;
	
	OAM[88] = 0;
	OAM[89] = 158;
	OAM[90] = 2;
	OAM[91] = 0;
	
	OAM[92] = 0;
	OAM[93] = 166;
	OAM[94] = 2;
	OAM[95] = 0;
	
	OAM[96] = 0;
	OAM[97] = 174;
	OAM[98] = 2;
	OAM[99] = 0;
	
	OAM[100] = 0;
	OAM[101] = 182;
	OAM[102] = 2;
	OAM[103] = 0;
	
	OAM[104] = 0;
	OAM[105] = 190;
	OAM[106] = 2;
	OAM[107] = 0;
	
	OAM[108] = 0;
	OAM[109] = 198;
	OAM[110] = 2;
	OAM[111] = 0;
	
	OAM[112] = 0;
	OAM[113] = 206;
	OAM[114] = 2;
	OAM[115] = 0;

	OAM[116] = 0;
	OAM[117] = 214;
	OAM[118] = 2;
	OAM[119] = 0;
	
	OAM[120] = 0;
	OAM[121] = 222;
	OAM[122] = 2;
	OAM[123] = 0;
	
	OAM[124] = 0;
	OAM[125] = 230;
	OAM[126] = 2;
	OAM[127] = 0;
	
	OAM[128] = 0;
	OAM[129] = 238;
	OAM[130] = 2;
	OAM[131] = 0;
	
	OAM[132] = 0;
	OAM[133] = 246;
	OAM[134] = 2;
	OAM[135] = 0;
	
	//Walls Bottom
	
	OAM[136] = 152;
	OAM[137] = 0;
	OAM[138] = 2;
	OAM[139] = 0;
	
	OAM[140] = 152;
	OAM[141] = 8;
	OAM[142] = 2;
	OAM[143] = 0;
	
	OAM[144] = 152;
	OAM[145] = 16;
	OAM[146] = 2;
	OAM[147] = 0;
	
	OAM[148] = 152;
	OAM[149] = 24;
	OAM[150] = 2;
	OAM[151] = 0;
	
	OAM[152] = 152;
	OAM[153] = 32;
	OAM[154] = 2;
	OAM[155] = 0;
	
	OAM[156] = 152;
	OAM[157] = 40;
	OAM[158] = 2;
	OAM[159] = 0;
	
	OAM[160] = 152;
	OAM[161] = 48;
	OAM[162] = 2;
	OAM[163] = 0;
	
	OAM[164] = 152;
	OAM[165] = 56;
	OAM[166] = 2;
	OAM[167] = 0;
	
	OAM[168] = 152;
	OAM[169] = 64;
	OAM[170] = 2;
	OAM[171] = 0;
	
	OAM[172] = 152;
	OAM[173] = 72;
	OAM[174] = 2;
	OAM[175] = 0;
	
	OAM[176] = 152;
	OAM[177] = 80;
	OAM[178] = 2;
	OAM[179] = 0;
	
	OAM[180] = 152;
	OAM[181] = 88;
	OAM[182] = 2;
	OAM[183] = 0;
	
	OAM[184] = 152;
	OAM[185] = 96;
	OAM[186] = 2;
	OAM[187] = 0;
	
	OAM[188] = 152;
	OAM[189] = 104;
	OAM[190] = 2;
	OAM[191] = 0;
	
	OAM[192] = 152;
	OAM[193] = 112;
	OAM[194] = 2;
	OAM[195] = 0;
	
	OAM[196] = 152;
	OAM[197] = 120;
	OAM[198] = 2;
	OAM[199] = 0;
	
	OAM[200] = 152;
	OAM[201] = 128;
	OAM[202] = 2;
	OAM[203] = 0;
	
	OAM[204] = 152;
	OAM[205] = 136;
	OAM[206] = 2;
	OAM[207] = 0;
	
	OAM[208] = 152;
	OAM[209] = 142;
	OAM[210] = 2;
	OAM[211] = 0;
	
	OAM[212] = 152;
	OAM[213] = 150;
	OAM[214] = 2;
	OAM[215] = 0;
	
	OAM[216] = 152;
	OAM[217] = 158;
	OAM[218] = 2;
	OAM[219] = 0;
	
	OAM[220] = 152;
	OAM[221] = 166;
	OAM[222] = 2;
	OAM[223] = 0;
	
	OAM[224] = 152;
	OAM[225] = 174;
	OAM[226] = 2;
	OAM[227] = 0;
	
	OAM[228] = 152;
	OAM[229] = 182;
	OAM[230] = 2;
	OAM[231] = 0;
	
	OAM[232] = 152;
	OAM[233] = 190;
	OAM[234] = 2;
	OAM[235] = 0;
	
	OAM[236] = 152;
	OAM[237] = 198;
	OAM[238] = 2;
	OAM[239] = 0;
	
	OAM[240] = 152;
	OAM[241] = 206;
	OAM[242] = 2;
	OAM[243] = 0;

	OAM[244] = 152;
	OAM[245] = 214;
	OAM[246] = 2;
	OAM[247] = 0;
	
	OAM[248] = 152;
	OAM[249] = 222;
	OAM[250] = 2;
	OAM[251] = 0;
	
	OAM[252] = 152;
	OAM[253] = 230;
	OAM[254] = 2;
	OAM[255] = 0;
	
	OAM[256] = 152;
	OAM[257] = 238;
	OAM[258] = 2;
	OAM[259] = 0;
	
	OAM[260] = 152;
	OAM[261] = 246;
	OAM[262] = 2;
	OAM[263] = 0;
	
	
	
	// main loop
	
	
	while (1) 
	{

		// ansi escape sequence to clear screen and home cursor
		// /x1b[line;columnH
		//iprintf("\x1b[2J");
		VBlankIntrWait();
		// ansi escape sequence to set print co-ordinates
		// /x1b[line;columnH
		//iprintf("\x1b[10;10HWEEK 1 EXAMPLE");

		scanKeys();
		keys = keysHeld();
		
		//if (keys & KEY_RIGHT)
		//{
			//if (CharacterChoice == 0)
			//{
				//OAM[1]++;
			//}
			
			//else
				
			//{
				//OAM[5]++;
			//}
		//}
		
		//if (keys & KEY_LEFT)
		//{
			//if(CharacterChoice == 0)
			//{
				//OAM[1]--;
			//}
			
			//else
				
			//{
				//OAM[5]--;
			//}
		//}
		
		if (keys & KEY_DOWN)
		{
			if(CharacterChoice == 0)
			{
				OAM[0]++;
			}
			else
			{
				OAM[4]++;
			}
		}
		
		if (keys & KEY_UP)
		{
			if(CharacterChoice == 0)
			{
				OAM[0]--;
			}
			else
			{
				OAM[4]--;
			}
			
			
		}
	
		if (keys & KEY_R)
		{
			//Disable 1 character and enable another!
			if (CharacterChoice == 0)
			{
				CharacterChoice = 1;
			}
			else
			{
				CharacterChoice = 1;
			}
			
			
		}
		
		if (keys & KEY_L)
		{
			//Disable 1 character and enable another!
			if (CharacterChoice == 1)
			{
				CharacterChoice = 0;
			}
			else
			{
				CharacterChoice = 0;
			}
		}
		
		if(OAM[0] >= 136)
		{
			OAM[0]= 136;
		}	
		
		if(OAM[0] <= 8)
		{
			OAM[0]= 8;
		}
		
		if(OAM[4] >= 136)
		{
			OAM[4]= 136;
		}	
		
		if(OAM[4] <= 8)
		{
			OAM[4]= 8;
		}
		
		//if(OAM[5] >= SCREEN_WIDTH)
		//{
		//	OAM[5] = 1;
		//}	
		
		//if(OAM[5] <= SCREEN_WIDTH_BOT)
		//{
		//	OAM[5] = 239;
		//}
	}
	
	
}


