#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

// Global alarm time
int alarm_set = 0;
int alarm_hour = -1, alarm_min = -1, alarm_sec = -1;

void set_alarm() {
    printf("\nSet Alarm (HH MM SS): ");
    scanf("%d %d %d", &alarm_hour, &alarm_min, &alarm_sec);

    if (alarm_hour >= 0 && alarm_hour < 24 && alarm_min >= 0 && alarm_min < 60 && alarm_sec >= 0 && alarm_sec < 60) {
        alarm_set = 1;
        printf("Alarm set for %02d:%02d:%02d\n", alarm_hour, alarm_min, alarm_sec);
    } else {
        printf("Invalid time! Alarm not set.\n");
        alarm_set = 0;
    }

#ifdef _WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
}

void check_alarm(int h, int m, int s) {
    if (alarm_set && h == alarm_hour && m == alarm_min && s == alarm_sec) {
        printf("\a\n\n*** ALARM! Time is %02d:%02d:%02d ***\n", h, m, s);
        alarm_set = 0;  // One-time alarm
#ifdef _WIN32
        Sleep(5000);
#else
        sleep(5);
#endif
    }
}

void digital_clock() {
    time_t rawtime;
    struct tm *timeinfo;

    while (1) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        system(CLEAR);
        printf("\n============================\n");
        printf("       DIGITAL CLOCK        \n");
        printf("============================\n");
        printf("        %02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        printf("============================\n");

        if (alarm_set)
            printf("Alarm set for: %02d:%02d:%02d\n", alarm_hour, alarm_min, alarm_sec);
        else
            printf("No alarm set.\n");

        check_alarm(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

#ifdef _WIN32
        Sleep(1000); // sleep for 1 second
#else
        sleep(1);
#endif
    }
}

int main() {
    int choice;

    while (1) {
        system(CLEAR);
        printf("======== MENU ========\n");
        printf("1. Start Digital Clock\n");
        printf("2. Set Alarm\n");
        printf("3. Exit\n");
        printf("======================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                digital_clock();
                break;
            case 2:
                set_alarm();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
#ifdef _WIN32
                Sleep(2000);
#else
                sleep(2);
#endif
        }
    }

    return 0;
}


//gcc digital_clock_alarm.c -o clock
//./clock
