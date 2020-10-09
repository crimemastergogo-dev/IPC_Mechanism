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
    int  connection_socket   = 0;
    int  data_socket         = 0;
    int  result              = 0;
    int  data                = 0;
    int  ret                 = 0;


    /*Closing the opnen socket instance by same name if any*/
    //unlink(SOCKET_NAME);

    connection_socket = socket(AF_UNIX,SOCK_STREAM,0);
    if (0 > connection_socket )
    {
        perror("master socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("master socket created successfully\n");

    memset(&name,0,sizeof(name));

    name.sun_family = AF_UNIX;

    strncpy(name.sun_path,SOCKET_NAME,sizeof(name.sun_path)-1);

    ret = bind(connection_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));
    if (0 > ret )
    {
        perror("binding failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Binbding successfull\n");

    ret = listen(connection_socket,20); /*20 clinets can send data*/
    if (0 > ret )
    {
       perror("listening failed\n");
        exit(EXIT_FAILURE);
    }
    printf("listening successfull\n");

    for (;;)
    {
        printf("Waiting for accpt\n");

        data_socket = accept(connection_socket,NULL,NULL);

        if (0 > ret )
        {
            perror("accept  failed\n");
            exit(EXIT_FAILURE);
        }
        printf("accept successfull\n");
        result = 0;

        for (;;)
        {
            ret = read(data_socket,buffer,BUFFER_SIZE);
            if (0 > ret )
            {
                perror("reading failed\n");
                exit(EXIT_FAILURE);
            }
            printf("read successfull\n");

            memcpy(&data,buffer,sizeof(int));

            if (0 == data)
            {
                break;
            }
            result +=data;
        }

        memset(buffer,0,BUFFER_SIZE);
        sprintf(buffer,"result = %d\n",result);
        ret = write(data_socket,buffer,BUFFER_SIZE);
        if (0 > ret )
        {
            perror("writing failed\n");
            exit(EXIT_FAILURE);
        }
        printf("write successfull\n");

        close(data_socket);
    }

    close(connection_socket);
}
