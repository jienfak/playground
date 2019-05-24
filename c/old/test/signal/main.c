#include <signal.h>
#include <stdio.h>
#include <time.h>

static volatile int keepRunning = 1 ;

void intHandler(int dummy){
	puts("I'm in 'intHandler.'");
	keepRunning = 0 ;
}

int main(void){
	puts("I'm in 'main'.");
	signal(SIGINT, intHandler);

	while(keepRunning){
		puts("Doing something...");
		sleep(1);
	}
	return 0 ;
}
