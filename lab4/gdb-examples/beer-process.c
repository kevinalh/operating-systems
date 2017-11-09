#include <stdio.h>
#include <unistd.h>

static void PrintMessage(int i);
static void GoToSleep(void);


int main(void)
{
	int i = 100000;

	while ( 1 )
	{
		PrintMessage( i );
		GoToSleep();
		i -= 1;
	}

	return 0;
}



void PrintMessage(int i)
{
		printf("%d bottles of beer on the wall.\n", i);
}



static void GoToSleep(void)
{
	sleep(3);
}
