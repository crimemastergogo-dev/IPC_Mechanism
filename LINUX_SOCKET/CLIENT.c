#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/LinuxSocket/file.sock"
#define BUFFER_SIZE  128

int main(int argc ,char *argv[])
{
    struct sockaddr_un name;
    char buffer[BUFFER_SIZE] = {0};
    int  data_socket         = 0;
    int  data                = 0;
    int  ret                 = 0;


    /*Closing the opnen socket instance by same name if any*/
    //unlink(SOCKET_NAME);

    data_socket = socket(AF_UNIX,SOCK_STREAM,0);
    if (0 > data_socket )
    {
        perror("client socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("client socket created successfully\n");

    memset(&name,0,sizeof(name));

    name.sun_family = AF_UNIX;

    strncpy(name.sun_path,SOCKET_NAME,sizeof(name.sun_path)-1);

    ret = connect(data_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));
    if (0 > ret )
    {
        perror("connect failed\n");
        exit(EXIT_FAILURE);
    }
    printf("connect successfull\n");

    do
    {
        printf("Enter number to send \n");
        scanf("%d",&data);
        ret = write(data_socket,&data,sizeof(int));
        if (0 > ret )
        {
            perror("writing failed\n");
            exit(EXIT_FAILURE);
        }
    }while(data);

    memset(buffer,0,BUFFER_SIZE);
    ret = read(data_socket,buffer,BUFFER_SIZE);
    if (0 > ret )
    {
        perror("writing failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Recvd data = %s\n",buffer);

    close(data_socket);
}
