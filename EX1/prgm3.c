#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
   pid_t pid2,pid3;

   pid2=fork();

   if(pid2==0)
   {
      printf("P2: PID=%d,Parent PID=%d\n",getpid(),getppid());

      pid3=fork();

      if(pid3==0)
      {
      printf("P3: PID=%d,Parent PID=%d\n",getpid(),getppid());
      }
   }
   else
   {
      wait(NULL);
      printf("P1: PID=%d\n",getpid());
   }
   return 0;
}
