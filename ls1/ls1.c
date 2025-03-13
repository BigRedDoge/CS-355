#include <stdio.h>
#include <dirent.h>


void do_ls(char *dirname) {
    DIR *dir_ptr;
    dir_ptr = opsendir(dirname);

}


int main() {
    do_ls(".");
    return 0;
}