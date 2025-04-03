#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void do_find(char *dir_name, char *filename, int indent);

// convert file mode into a printable string
void mode_to_string(int mode, char str[]) {
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0]='d'; // directory?
    if(S_ISCHR(mode)) str[0]='c'; // terminal?
    if(S_ISBLK(mode)) str[0]='b'; // disk?
    if(S_ISLNK(mode)) str[0]='l'; // link?

    if(mode & S_IRUSR) str[1]='r'; // bits for the user
    if(mode & S_IWUSR) str[2]='w';
    if(mode & S_IXUSR) str[3]='x';

    if(mode & S_IRGRP) str[4]='r'; // bits for the group
    if(mode & S_IWGRP) str[5]='w';
    if(mode & S_IXGRP) str[6]='x';

    if(mode & S_IROTH) str[7]='r'; // bits for the others
    if(mode & S_IWOTH) str[8]='w';
    if(mode & S_IXOTH) str[9]='x';
}

// this function is called for every encountered directory entry
void process_entry(char *dir_entry_name, char* filename, int indent) {
   struct stat info;
   if(stat(dir_entry_name, &info)==-1)
       perror(dir_entry_name);
   else {
       if(S_ISDIR(info.st_mode)) {      // if this directory entry is a subdirectory
           printf("%s\n", dir_entry_name);
           //do_find(dir_entry_name, filename, indent+1);  // explore this subdirectory
       }
       // use strstr() to check if the current directory entry's name matches the substring
       if (strstr(dir_entry_name, filename) != 0) {
            for (int i = 0; i < indent; i++) {
                printf("   ");
            }
            char modestring[11];
            mode_to_string(info.st_mode, modestring);
            printf("%s %s", dir_entry_name, modestring);
       }
   }
}

// explore all entries of the given directory
void do_find(char *dir_name, char *filename, int indent) {
    DIR *dir_ptr;               // pointer to a directory structure
    struct dirent *dirent_ptr;  // pointer to the current directory entry
    dir_ptr = opendir(dir_name);
    if(dir_ptr==0) {            // opendir could fail, possibly because
        perror(dir_name);       // the directory does not exist
    }
    else {                      // iterate over all directory entries
        while((dirent_ptr=readdir(dir_ptr)) != 0) {
            if (strcmp(dirent_ptr->d_name, dir_name) != 0) {
                process_entry(dirent_ptr->d_name, filename, indent);
            }
        }
        closedir(dir_ptr);
    }   
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Incorrect number of arguments\n");
        return 1;
    } else if (argc == 2) {
        // No directory specified
        //printf("%s", argv[1]);
        do_find(".", argv[1], 0);
    } else if (argc == 3) {
        // Directory specified
        do_find(argv[2], argv[1], 0);
    }

   return 0;
}