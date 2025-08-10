#include <stdio.h>

#include "socket/SocketBase.h"

int main(int argc, char** argv)
{
    printf("Starting Main\n");

    webserver::SocketBase socket(AF_INET, SOCK_STREAM, 0);

    return 0;
}