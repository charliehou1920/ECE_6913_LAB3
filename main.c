#include "header1.h"
#include <stdio.h>

// typedef enum
// {
// 	STAGE_1,   // Both intersections red
// 	STAGE_2,   // North-South green, East-West red
// 	STAGE_3,   // North-South yellow
// 	STAGE_4,   // East-West green, North-South red
// 	STAGE_5,   // East-West yellow
// 	PED_STAGE    // Pedestrian crossing mode
// }State;


//restart and all light off
void RESTART()
{
	setLED(NS_GREEN, OFF);
	setLED(NS_YELLOW, OFF);
	setLED(NS_RED, OFF);
	setLED(EW_GREEN, OFF);
	setLED(EW_YELLOW, OFF);
	setLED(EW_RED, OFF);
	setLED(PED_GREEN, OFF);
	setLED(PED_RED, OFF);
	return;
}

// Both intersections red
void STAGE_1()
{
	RESTART();
	
	setLED(PED_RED, ON);
	setLED(NS_RED, ON);
	setLED(EW_RED, ON);
	return;
}

// North-South green, East-West red
void STAGE_2()
{
	RESTART();
	setLED(PED_RED, ON);
	setLED(NS_GREEN, ON);
	setLED(EW_RED, ON);
	return;
}

// North-South yellow
void STAGE_3()
{	
	RESTART();
	setLED(NS_YELLOW, ON);
	setLED(PED_RED, ON);
	setLED(EW_RED, ON);
	int res = 0;
	do
	{
		res = checkPed(DELAY3);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	setLED(NS_YELLOW, OFF);
	setLED(NS_RED, ON);
	// setLED(EW_RED, OFF);
	res = 0;
	do
	{
		res = checkPed(DELAY5);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	return;
}

// East-West green, North-South red
void STAGE_4()
{
	RESTART();
	setLED(EW_GREEN, ON);
	setLED(PED_RED, ON);
	setLED(NS_RED, ON);
	return;
}

// East-West yellow
void STAGE_5()
{
	int res = 0;
	RESTART();
	setLED(NS_RED, ON);
	setLED(PED_RED, ON);
	setLED(EW_YELLOW, ON);
	do
	{
		res = checkPed(DELAY3);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	
	res = 0;
	setLED(EW_YELLOW, OFF);
	setLED(EW_RED, ON);
	do
	{
		res = checkPed(DELAY5);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	return;
}

/* PED_Stage1:
	(NO green light on both intersections)
	When there no Green light on both intersection, the other light should continue to
	remain red, and the pedestrian light turns green*/
void PED_Stage1()
{
	RESTART();
	setLED(PED_GREEN, ON);
	setLED(NS_RED, ON);
	setLED(EW_RED, ON);
	delay(DELAY15);
	setLED(PED_GREEN, OFF);
	setLED(PED_RED, ON);
	return;
}


/* PED_Stage2 
	(There is a green light on NS or EW)
	the current green light should change to flashing yellow for 10 seconds, then switch to
	red to allow pedestrians to cross for 15 secs.*/
void PED_Stage2(int Direction)
{
	RESTART();
	setLED(PED_GREEN, ON);
	// when direction is 0, which means north-south have green light
	if (Direction == 0)
	{
		setLED(EW_RED, ON);
		// flashing yellow for 10 seconds
		for(int i = 1; i <= 10; i++)
		{
			setLED(NS_YELLOW, ON);
			delay(Flashing);
			setLED(NS_YELLOW, OFF);
			delay(Flashing);
			setLED(NS_YELLOW, ON);
			delay(Flashing);
		}
	}
	// when direction is 0, which means east-west have green light
	else if (Direction == 1)
	{
		setLED(NS_RED, ON);
		//flashing yellow for 10 seconds
		for(int i = 1; i <= 10; i++ )
		{
			setLED(EW_YELLOW, ON);
			delay(Flashing);
			setLED(EW_YELLOW, OFF);
			delay(Flashing);
			setLED(EW_YELLOW, ON);
			delay(Flashing);
		}
	}
	setLED(NS_YELLOW, OFF);
	setLED(EW_YELLOW, OFF);
	setLED(PED_RED, OFF);
	setLED(PED_GREEN, ON);
	setLED(NS_RED, ON);
	setLED(EW_RED, ON);
	delay(DELAY15);
	setLED(PED_GREEN, OFF);
	setLED(PED_RED, ON);
	return;
}


int main()
{
	int res;
	setupGPIO();

	int curr_state = 1;

	while (1)
	{
		switch (curr_state)
		{
		case 1:
			STAGE_1();
			res = checkPed(DELAY10);
			if (res == 1)
			{
				PED_Stage1();
				curr_state--;
			}
			break;
		case 2:
			STAGE_2();
			res = checkPed(DELAY20);
			if (res == 1)
			{
				PED_Stage2(0);
				curr_state--;
			}
			break;
		case 3:
			STAGE_3();
			break;
		case 4:
			STAGE_4();
			res = checkPed(DELAY20);
			if (res == 1)
			{
				PED_Stage2(1);
				curr_state--;
			}
			break;
		case 5:
			STAGE_5();
			break;
		}
		curr_state++;
		if (curr_state == 6)
		{
			curr_state = 1;
		}
	}

	return 0;
}
