#include <stdio.h>
#include "common.h"

int main()
{
    /* SUNDAY ... SATURDAY likes MACRO from 0 -> */
    /* each day likes int variable */
    enum week_day {SUNDAY, MONDAY, TUESDAY, WEDSDAY, THURSDAY, FRIDAY, SATURDAY} day1 = 8, day2 = 4, day3 = 2;
    enum week_day yesterday = 1, tomorrow = 2, the_next_day = 4;

    yesterday += 9;

    printf("sizeof(enum week_day) = %ld = %ld = %ld \n", sizeof(day1), sizeof(yesterday), sizeof(SUNDAY));
    printf("SUNDAY = %d \nMONDAY = %d \nTUESDAY = %d \nWEDSDAY = %d \nTHURSDAY = %d \nFRIDAY = %d \nSATURDAY = %d \n", \
           SUNDAY, MONDAY, TUESDAY, WEDSDAY, THURSDAY, FRIDAY, SATURDAY);
    printf("day1 = %d \tday2 = %d \tday3 = %d \n", day1, day2, day3);
    printf("yesterday = %d \ttomorrow = %d \tthe_next_day = %d \n", yesterday, tomorrow, the_next_day);

    return 0;
}