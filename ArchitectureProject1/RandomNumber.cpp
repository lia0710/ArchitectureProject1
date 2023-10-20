#include "RandomNumber.h"
#include "time.h"
#include <cstdlib>

RandomNumber::RandomNumber() 
{
}

int RandomNumber::GetRandomNumber(int min, int max)
{
	//generate a random number between min and max
	float value = 0;

	srand(time(NULL));

	value = ((float)rand() / (float)RAND_MAX);
	value = value * 1000000;

	int intvalue = (int)value;
	intvalue = min + intvalue % (max+1);
	return intvalue;
}