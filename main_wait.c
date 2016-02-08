#include <stddef.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/reg.h>
#include <sys/user.h>

int main() {
  pid_t pid;

  pid = fork();

  if(pid == -1) {
    fputs("fork failed\n", stderr);
  } else if(pid == 0) {
    int i;

    for(i = 0; i < 100; ++i) {
      usleep(1000000);
      puts("child");
    }
  } else {
    int wait_status;

    printf("%d\n", pid);
      
    do {
      waitpid(pid, &wait_status, WUNTRACED | WCONTINUED);
      if(WIFEXITED(wait_status)){ 
           printf("exited : %d \n", WEXITSTATUS(wait_status));
      } else if(WIFSIGNALED(wait_status)){
           printf("signalled : %d \n", WTERMSIG(wait_status));
      } else if(WIFSTOPPED(wait_status)){
           printf("stopped : %d \n", WSTOPSIG(wait_status));
      } else if(WIFCONTINUED(wait_status)){
           printf("continued \n");
      }
    } while(!WIFEXITED(wait_status) && !WIFSIGNALED(wait_status));
  }

  return 0;
}
