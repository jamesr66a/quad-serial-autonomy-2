#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include <signal.h>


/* TERM signal handler */
void term_handler(int signal)
{

}

int main()
{
	/* setup interrupt handler for TERM signal */
	struct sigaction sa;
	sa.sa_handler = term_handler;
	sigaction( SIGINT, &sa, NULL );


}
