#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
   pid_t p2,p3,p4,p5,p6,p7,p8;
   p2=fork();
   if(p2==0)
   {
      printf("P2 PID=%d,Parent=%d\n",getpid(),getppid());
      p4=fork();
      if(p4==0)
      {
        printf("P4 PID=%d,Parent=%d\n",getpid(),getppid());
        p8=fork();
        if(p8==0)
        {
           printf("P8 PID=%d,Parent=%d\n",getpid(),getppid());
        }
        else
        {
           wait(NULL);
        }
      }
      else
      {
         wait(NULL);
         p5=fork();
         if(p5==0)
         {
           printf("P5 PID=%d,Parent=%d\n",getpid(),getppid());
         }
         else
         {
            wait(NULL);
         }
      }
   }
   else
   {
      wait(NULL);
      p3=fork();
      if(p3==0)
      {
         printf("P3 PID=%d,Parent=%d\n",getpid(),getppid());
         p6=fork();
         if(p6==0)
         {
            printf("P6 PID=%d,Parent=%d\n",getpid(),getppid());
         }
         else
         {
            wait(NULL);
            p7=fork();
            if(p7==0)
            {
               printf("P7 PID=%d,Parent=%d\n",getpid(),getppid());
            }
            else
            {
               wait(NULL);
            }
         }
      }
      else
      {
         wait(NULL);
         printf("P1 PID=%d,Parent=%d\n",getpid(),getppid());
      }
   }
   return 0;
}
