#include <stdio.h>
#include <stdalign.h>
#include "common.h"

struct date_of_birth {
    unsigned char day;
    char ten_thang[10];
    unsigned short nam;
};

typedef struct {
    char name[20];
    struct date_of_birth birthday;
} worker;

worker hardworker;

int main(void)
{
    printf("size of date_of_birth = %ld \n", sizeof(struct date_of_birth));
    printf("size of worker = %ld \n", sizeof(worker));
    printf("align of date_of_birth = %ld \n", alignof(struct date_of_birth));
    printf("align of worker = %ld \n", alignof(worker));

    /* ltsnnh 10 jun 1997 */
    scanf("%s", hardworker.name);
    scanf("%hhu", &hardworker.birthday.day);
    scanf("%s", hardworker.birthday.ten_thang);
    scanf("%hu", &hardworker.birthday.nam);
    putchar('\n');
    puts(hardworker.name);
    printf("%hhu\t%s\t%hu\n", hardworker.birthday.day, \
        hardworker.birthday.ten_thang, hardworker.birthday.nam);

    return 0;
}
