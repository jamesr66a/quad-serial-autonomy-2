#include <wiringPi.h>
#include <softPwm.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* Define preprocessor directive LED if you want to test with
 * visible LED brightness range and oscillation period */

#ifndef LED
static const unsigned int PERIOD = 100000;
static const unsigned int MIN = 10;
static const unsigned int MAX = 20;
#else
static const unsigned int PERIOD = 10000;
static const unsigned int MIN = 0;
static const unsigned int MAX = 100;
#endif

/* Determine which pin to output PWM on */
static const unsigned int PIN = 14;


/* signal TERM handler */
void term_handler(int signal)
{
	usleep(PERIOD);
	softPwmWrite(PIN, 0);
	exit(0);
}

int main()
{
	/*setup interrupt handler to break out of loop */
	struct sigaction sa;
	sa.sa_handler = term_handler;
	
	sigaction( SIGINT, &sa, NULL );

	/* setup for the PWM signal on the specified
	   wiringPi pin */

	int counter = 0;
	wiringPiSetup();

	int status = softPwmCreate(PIN, 0, 100);
	assert(!status);
	
	/* infinite loop to fade signal across range */
	while (1)
	{
		for (counter = MIN; counter < MAX; counter++)
		{
			softPwmWrite(PIN, counter);
			usleep(PERIOD);
		}
		for (counter = MAX; counter > MIN; counter--)
		{
			softPwmWrite(PIN, counter);
			usleep(PERIOD);
		}
	}
}
