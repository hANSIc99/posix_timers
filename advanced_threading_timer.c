#include <stdio.h>
#include <signal.h>
#include <unistd.h>

pid_t gettid(void);

//handle SIGSTOP nopass
//handle SIGSTOP nostop

int main()
{
    struct sigevent sev = { 0 };
    printf("Press Any Key to Exit\n");

    sev.sigev_notify = SIGEV_THREAD_ID; // Linux-specific
    sev._sigev_un._tid = gettid();

    getchar();
    return 0;
}
