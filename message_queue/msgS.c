/* Made by - Satvik Sharma
 * Last modified on : 1/4/2020*/

/*This program sends the messege send over a message Queue*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>

#define MAX_SIZE  512
/*Given structure is the type of data we
 will receive over a message queue*/
typedef struct
{
    long int msg_type;       
    char some_text[MAX_SIZE]; /*BUFSIZ is a macro defined in stdio.h it is
                             usually the size of the input stream of the conmpiler
                             and it is compiler dependent*/

}My_msg;

int main()
{
    int running = 1;/*for infinte loop*/
    int retval = 0;
    My_msg SendData;
    int msgid;/*this variable holds the returned value from the msg key genrerator*/
    char buffer[BUFSIZ];

    /*int msgget(key_t key, int msgflg)
      This function create and access a message queue 
        key: It names a particular msg queue
        msgflag: consist of 9 permission flags 
        IPC_CREAT must be bitwise OR with the permission flags 
        to create a new msg queue
        RETURN:
        If successful, the return value will be the message queue identifier
        (a nonnegative integer), otherwise -1  with  errno  indicating
        the error.*/
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); /*key and permision for the message queue*/

    if (-1 == msgid )
    {
        fprintf(stderr,"Message ID failed to prepare with the error: %d",errno);
        exit(EXIT_FAILURE);

    }

    while(running)
    {
        fprintf(stdout,"Enter Messgae to send: \n");
        fgets(buffer,BUFSIZ,stdin);
        SendData.msg_type = 1;
        strcpy(SendData.some_text,buffer);
        /*int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
          msqid = The msg queue identifier  returned from msgget
          msgp  = pointer to the msg being send
          msgsz = It is the size of the message to be sent
          msgflag = controls what happens if the current msg
                    queue is full or system limit is reached 
         returns -1 on failure and 0 for success*/
        retval = msgsnd(msgid, (void *)&SendData , MAX_SIZE, 0);
        if (-1 == retval )
        {
            fprintf(stderr,"msgsnd failed with error : %d",errno);
            exit(EXIT_FAILURE);
        }

        if (strncmp(SendData.some_text, "end",3)==0)
        {
            running = 0;
        }
    }

    exit(EXIT_SUCCESS);
}



