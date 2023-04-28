// #include "lab3.h"

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
	setLED(PED_RED, 1);
	setLED(NS_RED, 1);
	setLED(EW_RED, 1);
	return;
}

void STAGE_2()
{
	// ALL_OFF();
	setLED(PED_RED, 1);
	setLED(NS_GREEN, 1);
	setLED(EW_RED, 1);
	return;
}

void STAGE_3()
{
	setLED(NS_YELLOW, 1);
	res = 0;
	do
	{
		res = checkPed(3000);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	setLED(NS_YELLOW, 0);
	setLED(NS_RED, 1);
	res = 0;
	do
	{
		res = checkPed(5000);
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
	setLED(EW_GREEN, 1);
	setLED(PED_RED, 1);
	setLED(NS_RED, 1);
	return;
}

void STAGE_5()
{
	int res = 0;
	setLED(NS_RED, 1);
	setLED(PED_RED, 1);
	setLED(EW_YELLOW, 1);
	do
	{
		res = checkPed(3000);
		if (res == 1)
		{
			PED_Stage1();
		}
	} while (res == 1);
	
	res = 0;
	setLED(EW_YELLOW, 0);
	setLED(EW_RED, 1);
	do
	{
		res = checkPed(5000);
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
	setLED(PED_GREEN, 1);
	setLED(NS_RED, 1);
	setLED(EW_RED, 1);
	delay(15000);
	setLED(PED_GREEN, 0);
	setLED(PED_RED, 1);
	return;
}

void PED_Stage2(char Direction)
{
	ALL_OFF();
	int k = 0;
	setLED(PED_RED, 1);
	if (Direction == 'N')
	{
		setLED(EW_RED, 1);
		while (k <= 9)
		{
			setLED(NS_YELLOW, 1);
			delay(333);
			setLED(NS_YELLOW, 0);
			delay(333);
			setLED(NS_YELLOW, 1);
			delay(333);
			k++;
		}
	}
	else if (Direction == 'E')
	{
		setLED(NS_RED, 1);
		while (k <= 9)
		{
			setLED(EW_YELLOW, 1);
			delay(333);
			setLED(EW_YELLOW, 0);
			delay(333);
			setLED(EW_YELLOW, 1);
			delay(333);
			k++;
		}
	}
	setLED(NS_YELLOW, 0);
	setLED(EW_YELLOW, 0);
	setLED(PED_RED, 0);
	setLED(PED_GREEN, 1);
	setLED(NS_RED, 1);
	setLED(EW_RED, 1);
	delay(15000);
	setLED(PED_GREEN, 0);
	setLED(PED_RED, 1);
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
			res = checkPed(10000);
			if (res == 1)
			{
				PED_Stage1();
				curr_state--;
			}
			break;
		case 2:
			STAGE_2();
			res = checkPed(20000);
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
			res = checkPed(20000);
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
