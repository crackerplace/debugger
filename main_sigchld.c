##include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


static void multi_handler(int sig, siginfo_t *siginfo, void *context) {
    // get pid of sender,
    pid_t sender_pid = siginfo->si_pid;

    printf("Got a SIGCHLD signal from [%d]\n", (int)sender_pid);

    return;
}

int main(){

        // prepare sigaction
        struct sigaction siga;
        siga.sa_sigaction = &multi_handler; 
        siga.sa_flags = SA_SIGINFO; // get detail info
        // change signal action,
        sigaction(SIGCHLD, &siga, NULL);
        int i;
        printf("my pid is %d \n",(int)getpid());
        for(i = 0; i < 100; ++i) {
           usleep(1000000);
           printf("in loop %d \n", i);
        }
                        
} 
