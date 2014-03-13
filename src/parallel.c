#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* TERM signal handler */
void term_handler(int signal)
{
	exit(-1);
}

/* create a single pwm pin instance with the specified
 * initial value and range. Handle errors and exit */
void create_pwm_pin(int pin, int init, int range)
{
	char buf[100];
	int ret_val = softPwmCreate(pin, init, range);

	if ( ret_val )
	{
		sprintf(buf,
			"Error opening PWM pin %i : %i",
			pin, errno);
		perror(buf);
		exit(-1);
	}
}

/* Create pwm pins contained within the passed-in array.
 * Takes initial value and range arguments also */
void create_pwm_array(int pins[], size_t arr_len, int init, int range)
{
	size_t i;
	for (i=0; i<arr_len; i++)
	{
		create_pwm_pin(pins[i], init, range);
	}
}

/* Constant values for the sweep behavior  */
static const unsigned int MIN = 0;
static const unsigned int MAX = 100;
static const unsigned int PERIOD = 10000;

int main()
{
	size_t i;
	int counter;

	/* setup interrupt handler for TERM signal */
	struct sigaction sa;
	sa.sa_handler = term_handler;
	sigaction( SIGINT, &sa, NULL );

	/* setup wiringPi interface*/
	wiringPiSetup();

	/* array of pins to write to */
	int pins[5] = {1, 2, 3, 4, 5};
	
	/* open pwm pins */
	create_pwm_array(pins, 5, 0, 100);

	/* fade value in and out for every pwm pin */
	while (1)
	{
		for (counter = MIN; counter < MAX; counter++)
		{
			for (i=0; i<5; i++)
				softPwmWrite(pins[i], counter);
			usleep(PERIOD);
		}		
		for (counter = MAX; counter > MIN; counter--)
		{
			for (i=0; i<5; i++)
				softPwmWrite(pins[i], counter);
			usleep(PERIOD);
		}
	}

	return 0;
}
