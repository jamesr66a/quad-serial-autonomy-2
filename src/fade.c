#include <wiringPi.h>
#include <softPwm.h>
#include <assert.h>
#include <unistd.h>

static const unsigned int PERIOD = 100000;
static const unsigned int MIN = 10;
static const unsigned int MAX = 20;

int main()
{
	int counter = 0;
	wiringPiSetup();

	int status = softPwmCreate(1, 0, 100);
	assert(!status);

	while (1)
	{
		for (counter = MIN; counter < MAX; counter++)
		{
			softPwmWrite(1, counter);
			usleep(PERIOD);
		}
		for (counter = MAX; counter >= MIN; counter--)
		{
			softPwmWrite(1, counter);
			usleep(PERIOD);
		}
	}
}
