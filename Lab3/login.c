#include <stdio.h>
#include <time.h>
#include <fcntl.h> // API for open/close
#include <unistd.h> // API incl read/write

#define LOGIN_FILE "login_file.txt"


struct login {
    char user_name[100];
    char terminal_name[100];
    time_t timestamp;
};


int main() {
    struct login currentLogin;
    int intLoginFile;
    int intLoginFileLength = sizeof(currentLogin);
    printf("Login file is %s\n", LOGIN_FILE);

    intLoginFile = creat(LOGIN_FILE, S_IRUSR | S_IWUSR);
    if (intLoginFile == -1) {
        printf("Error creating login file\n");
        return 1;
    }

    // populate the login file with some dummy records
    for (int i = 0; i < 10; i++) {
        sprintf(currentLogin.user_name, "user_%d", i);
        sprintf(currentLogin.terminal_name, "terminal_%d", i);
        time(&currentLogin.timestamp);
        write(intLoginFile, &currentLogin, intLoginFileLength);
        printf("Writing a record for %s\n", currentLogin.user_name);
        sleep(1);
    }

    close(intLoginFile);

    intLoginFile = open(LOGIN_FILE, O_RDONLY);
    if (intLoginFile == -1) {
        printf("Error opening login file\n");
        return 1;
    }

    while (read(intLoginFile, &currentLogin, intLoginFileLength) == intLoginFileLength) {
        printf("%s last logged in on %s on %s\n", currentLogin.user_name, currentLogin.terminal_name, asctime(localtime(&currentLogin.timestamp)));
    }

    return 0;
}