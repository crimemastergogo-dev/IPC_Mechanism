#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

static int alarm_fire = 0;

void  ding(int sig)
{
    alarm_fire =1;
}

int main()
{
    pid_t pid;

    fprintf(stdout,"ALARM APPLICATION \n");
    fprintf(stdout,"Creating Child process \n");

    pid = fork();

    switch(pid)
    {
        case -1 : 
         perror("fork failed");
         exit(1);

        case 0:
         fprintf(stdout,"In Child process  pid %d:\n",getpid());
         sleep(5);
         kill(getppid(),SIGALRM);
         exit(0);
    }
    fprintf(stdout,"In parent process pid %d: \n",getpid());
    fprintf(stdout,"Waiting to alarm go off\n");
    (void)signal(SIGALRM,ding);

    /*int pause(void)
     *suspends execution till  a signal occurs, when it receives
     *a signal any established handler is run and execution
     *continues as normal
     * return -1 with errno set to EINTR when interrupted by signal*/
    pause();
    if (alarm_fire)
    {
        fprintf(stdout,"DING!!!\n");
    }
    fprintf(stdout,"Done\n");

    exit(0);
}
