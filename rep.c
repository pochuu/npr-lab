
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("connecting to unixlaba\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    int indeks=140107;
    zmq_connect (requester, "tcp://unixlab.cs.put.poznan.pl:5555");
    printf ("connected\n");
    char buffer [100];
    zmq_send (requester, &indeks, sizeof(indeks), 0);
    printf ("sent\n");
    zmq_recv (requester, buffer, 100, 0);   
    printf ("received\n");
    printf("msg: %s\n",buffer);
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}