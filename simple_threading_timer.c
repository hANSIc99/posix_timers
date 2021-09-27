#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void expired(union sigval timer_data);

pid_t gettid(void);

struct t_eventData{
    int myData;
};

// https://stackoverflow.com/questions/5153972/unix-linux-signal-handling-sigev-thread

// https://stackoverflow.com/questions/65675834/sigstop-when-trying-to-debug-application-in-qtcreator-running-on-an-ubuntu-18-04
int main()
{
    int res = 0;
    timer_t timerId = 0;

    struct t_eventData eventData = { .myData = 0 };


    /* specify behaviour when event received */
    struct sigevent sev = { 0 };

    /* specify start delay and interval */
    struct itimerspec its = {   .it_value.tv_sec  = 1,
                                .it_value.tv_nsec = 0,
                                .it_interval.tv_sec  = 1,
                                .it_interval.tv_nsec = 0
                            };

    printf("Simple Threading Timer\n");

    /* SIGEV_THREAD
     *
     * Upon timer expiration, invoke sigev_notify_function as if
     * it were the start function of a new thread.
     */

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &expired;
    sev.sigev_value.sival_ptr = &eventData;


    res = timer_create(CLOCK_REALTIME, &sev, &timerId);


    if ( res != 0){
        fprintf(stderr, "Error timer_create: %s\n", strerror(errno));
        exit(-1);
    }


    res = timer_settime(timerId, 0, &its, NULL);

    if ( res != 0){
        fprintf(stderr, "Error timer_settime: %s\n", strerror(errno));
        exit(-1);
    }

    printf("Press ETNER Key to Exit\n");
    while(getchar()!='\n'){}
    return 0;
}


void expired(union sigval timer_data){
    struct t_eventData *data = timer_data.sival_ptr;
    printf("Timer fired %d - thread-id: %d\n", ++data->myData, gettid());
}
