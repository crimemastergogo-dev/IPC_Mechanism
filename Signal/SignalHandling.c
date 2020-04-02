#include<stdio.h>
#include<unistd.h>
#include<signal.h>

/*This function catches the signal SIGINT and handles it
 *This is a signal handler and it is not safe to use printf
 *in a signal handler*/
void ctrl_c_received(int sig)
{
    /*not safe to use printf in signal handler instaed set a flag*/
    fprintf(stderr,"I got signal %d\n",sig);
    /*void (*signal(int sig, void (*func)(int)))(int)
     *signal is a function  that takes two seperate parameters,
     *sig and func. The signal to be caught or ignored is given
     *as argument sig. The function to be called when the specified 
     *signal is received is given as func. This function must be 
     *one that takes a signal int argument  and is of type void*/
     (void) signal(SIGINT,SIG_DFL);
}

int main()
{
    (void) signal(SIGINT,ctrl_c_received);

    while(1)
    {
        fprintf(stdout,"Hello World\n");
        sleep(2);
    }
}
