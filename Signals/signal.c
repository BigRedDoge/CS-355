#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void ouch(int);
int ouch_count = 0;

void long_loop() {
    for(int i = 0; i < 10; i++) {
        printf("Hello %d\n", i);
        sleep(1);
    }
}

int main() {
    signal(SIGINT, SIG_IGN);
    long_loop();
    return 0;
}

void ouch(int sig) {
    ouch_count++;
    printf("----OUCH! %d\n", ouch_count);
    if (ouch_count >= 3) {
        printf("You're killing me...\n");
        signal(SIGINT, SIG_DFL);
    }
}