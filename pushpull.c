#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


int main (void) 
{
    struct timeval stop, start;
    void *context = zmq_ctx_new ();
    //  Socket to send messages to
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sender, "tcp://unixlab.cs.put.poznan.pl:6002");
    gettimeofday(&start, NULL);
    zmq_send (sender, "Jonasz Kasprzak", 15, 0);
    gettimeofday(&stop, NULL);
    printf("Sent, took: %lu ms\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}
