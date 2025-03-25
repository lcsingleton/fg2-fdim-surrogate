#pragma once

enum MsCanId
{
	RDS_MESSAGE = 0x2F5,
	ICC_BUTTONS = 0x2FC,
	ICC = 0x307,
	INTACTTEMP = 0x313,
	MENU_OPTIONS_ICC = 0x315,

	// NFI??
	PCM_CRS_ECON = 0x425,

	FDM_KEEPALIVE = 0x55C,

	// WTF??
	MSG2 = 0x6f8
};

enum FdmId
{
	
};

struct FdmKeyStatus
{

};


struct CanMessage
{
	MsCanId id;
	union CanData
	{
		unsigned[4] _unsigned;
		char[8] _char;

	} canData;
};



struct 
{
	unsigned padding1: 16;
	unsigned padding2: 16;
	bool isTempActive: 1;
	unsigned temp: 7
	char b5: 8;
	unsigned padding3: 16;
};

