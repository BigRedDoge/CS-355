#include <stdio.h>
#include <string.h>

struct dataRecord {
    int intId;
    int intAge;
    char strName[100];
    float salary;
};

void printDataRecord(const struct dataRecord *p) {
    // p->strName == (*p).strName
    printf("Name: %s\n", p->strName);
    printf("Age: %d\n", p->intAge);
    printf("ID: %d\n", p->intId);
}

int main() {
    struct dataRecord John;
    John.intId = 12345;
    John.intAge = 25;
    John.salary = 15.69;
    strcpy(John.strName, "John Doe");
    printDataRecord(&John);

    John.intAge = 26;
    printDataRecord(&John);

    struct dataRecord *alias=0;
    alias = &John;
    alias->salary += 0.75;
    printDataRecord(alias);

    return 0;
}