#include <stdio.h>


int main(int argc, char *argv[]) {
    // loop through all arguments
    for (int i = 1; i < argc; i++) {
        // pointer to first character of current argument
        char *argPtr = argv[i];
        int argLen = 1;
        // loop through all characters in current argument
        while (*argPtr != '\0') {
            // if character is a letter aA-zZ based on ascii code
            if ((*argPtr >= 'a' && *argPtr <= 'z') || (*argPtr >= 'A' && *argPtr <= 'Z') && !(*argPtr >= 0 && *argPtr <= 9)) {
                // print out each character of current argument up to current character
                for (int j = argLen - 1; j >= 0; j--) {
                    // if character is a letter aA-zZ based on ascii code
                    if ((*(argPtr - j) >= 'a' && *(argPtr - j) <= 'z') || (*(argPtr - j) >= 'A' && *(argPtr - j) <= 'Z') && !(*(argPtr - j) >= 0 && *(argPtr - j) <= 9)) {
                        printf("%c", *(argPtr - j));
                    }
                }
                printf("\n");
            }
            // increment pointer and length of current argument
            argLen++;
            argPtr++;
        }
    }
}