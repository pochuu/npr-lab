
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main (void)
{
    printf ("connecting to unixlaba\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    char buffer[100];
    zmq_connect (subscriber, "tcp://unixlab.cs.put.poznan.pl:6005");
    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE, "", 0);
    printf ("connected\n");
    zmq_recv (subscriber, buffer, 100, 0);   
    printf ("received\n");
    printf("msg: %s\n",buffer);
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}