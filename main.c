#include "header1.h"

// typedef enum
// {
// 	STAGE_1,   // Both intersections red
// 	STAGE_2,   // North-South green, East-West red
// 	STAGE_3,   // North-South yellow
// 	STAGE_4,   // East-West green, North-South red
// 	STAGE_5,   // East-West yellow
// 	PED_STAGE    // Pedestrian crossing mode
// }State;


// void ALL_OFF()
// {
// 	setLED(LED_PED_GREEN, 0);
// 	setLED(LED_PED_RED, 0);
// 	setLED(LED_NS_GREEN, 0);
// 	setLED(LED_NS_YELLOW, 0);
// 	setLED(LED_NS_RED, 0);
// 	setLED(LED_EW_GREEN, 0);
// 	setLED(LED_EW_YELLOW, 0);
// 	setLED(LED_EW_RED, 0);
// 	return;
// }
void STAGE_1()
{
	// ALL_OFF();
	setLED(PED_RED, ON);
	setLED(NS_RED, ON);
	setLED(EW_RED, ON);
	return;
}

void STAGE_2()
{
	// ALL_OFF();
	setLED(PED_RED, ON);
	setLED(NS_GREEN, ON);
	setLED(EW_RED, ON);
	return;
}

void STAGE_3()
{
	setLED(NS_YELLOW, ON);
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

void STAGE_4()
{
	// ALL_OFF();
	setLED(EW_GREEN, ON);
	setLED(PED_RED, ON);
	setLED(NS_RED, ON);
	return;
}

void STAGE_5()
{
	int res = 0;
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

void PED_Stage1()
{
	ALL_OFF();
	setLED(PED_GREEN, ON);
	setLED(NS_RED, ON);
	setLED(EW_RED, ON);
	delay(DELAY15);
	setLED(PED_GREEN, OFF);
	setLED(PED_RED, ON);
	return;
}

void PED_Stage2(char Direction)
{
	ALL_OFF();
	int k = 0;
	setLED(PED_RED, ON);
	if (Direction == 'N')
	{
		setLED(EW_RED, ON);
		while (k <= 9)
		{
			setLED(NS_YELLOW, ON);
			delay(Flashing);
			setLED(NS_YELLOW, OFF);
			delay(Flashing);
			setLED(NS_YELLOW, ON);
			delay(Flashing);
			k++;
		}
	}
	else if (Direction == 'E')
	{
		setLED(NS_RED, ON);
		while (k <= 9)
		{
			setLED(EW_YELLOW, ON);
			delay(Flashing);
			setLED(EW_YELLOW, OFF);
			delay(Flashing);
			setLED(EW_YELLOW, ON);
			delay(Flashing);
			k++;
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
				PED_Stage2('N');
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
				PED_Stage2('E');
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
