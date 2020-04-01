/* Made by - Satvik Sharma
 * Last modified on : 1/4/2020*/

/*This program receives the messege send over a message Queue*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>

/*Given structure is the type of data we
 will receive over a message queue*/
typedef struct
{
    long int msg_type;
    char some_text[BUFSIZ]; /*BUFSIZ is a macro defined in stdio.h it is
                             usually the size of the input stream of the conmpiler
                             and it is compiler dependent*/

}My_msg;

int main()
{
    int running = 1;/*for infinte loop*/
    int retval = 0;
    My_msg ReceivedData;
    int msgid;/*this variable holds the returned value from the msg key genrerator*/

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
        /*ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
          this function retrives messages from the message queue
          msgid = msg queue identifier returned from the msgget function
          msgp  = It is the ponter to the message received it must start with a long
          int type
          msg_sz= It is the size of the message pointed to by msgp not including long int
          message type
          msgtype= It allows simple form of reception priority 
          If the message type has the value 0, the first available message in the 
          queue is retrieved. If it is less than 0 the first message that has the
          same type of as or less than the absolute value of msgtype is recieved
          msgdlag = Controls what happens when no message of the appropriate type is waiting 
          to be recieved 
          On success msgrcv returns the number of bytes placed in the receive buffer
          returns -1 in case of error*/
        retval = msgrcv(msgid, (void *)&ReceivedData , BUFSIZ, 0 , 0 );
        if (-1 == retval )
        {
            fprintf(stderr,"msgrcv failed with error : %d",errno);
            exit(EXIT_FAILURE);
        }

        fprintf(stdout,"Message Received:\n");
        fprintf(stdout,"Sender sent :%s\n",ReceivedData.some_text);
        if (strncmp(ReceivedData.some_text, "end",3)==0)
        {
            running = 0;
        }
    }

    /*Deletion of the allocated queue is the responsibilty of receiver*/
    /* int msgctl(int msqid, int cmd, struct msqid_ds *buf);
       This function controls the message queue
       msiqid = It is the identifier returned from msgget
       cmd    = It is the action to take It can take following three values
       IPC_STAT = sets the data in the msqid_ds to reflect the values
       associated with the message queue
       IPC_SET  = If the process has permission to do so , it sets the values
       associated with the msg queue to those provided in the msqid_ds
       IPC_RMID = Delets the queue
       buf    = pointer to the msqid_ds structure 
       struct msqid_ds {
       struct ipc_perm msg_perm;      Ownership and permissions 
       time_t          msg_stime;     Time of last msgsnd 
       time_t          msg_rtime;     Time of last msgrcv
       time_t          msg_ctime;     Time of last change 
       unsigned long   __msg_cbytes;  Current number of bytes in
       queue  
       msgqnum_t       msg_qnum;      Current number of messages
       in queue 
       msglen_t        msg_qbytes;    Maximum number of bytes
       allowed in queue 
       pid_t           msg_lspid;     PID of last msgsnd 
       pid_t           msg_lrpid;     PID of last msgrcv
       };
       0 is returned on sucess and -1 on failure
     */
    if (msgctl(msgid,IPC_RMID,0)==-1)
    {
        fprintf(stderr,"msgctl failed with error: %d",errno);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}



