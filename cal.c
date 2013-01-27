#include <stdio.h>
#include <time.h>
#include <string.h>

#define CAL_H 7
#define CAL_V 6
#define HEADER_LEN 21;

int days(int month, int year){
    int pos_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2 && year % 4 == 0){
        return 29;
    }else{
        return pos_days[month - 1];
    }
}

int week(int day, int month, int year){
    struct tm date;

    date.tm_sec = 0;
    date.tm_min = 0;
    date.tm_hour = 0;
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    date.tm_isdst = 0;
    mktime(&date);

    return date.tm_wday;
}

void make_cal(int month, int year, int cal[CAL_V][CAL_H]){
    int nd, wd;
    int i, j, d;
    for(i=0;i<CAL_V;i++){
        for(j=0;j<CAL_H;j++){
            cal[i][j] = 0;
        }
    }

    nd = days(month, year);
    wd = week(1, month, year);

    for(d=1, i=0, j=wd;d<=nd;d++, j++){
        if(j>=CAL_H){
            j = 0;
            i++;
        }
        cal[i][j] = d;
    }
}

/*
void make_header(int mon, int ye, char h[HEADER_LEN]){
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    sprintf(h, "%s %04d", months[mon-1], ye);
    centering(h, HEADER_LEN);
}

void centering(char *s, int size){
    int len = strlen(s);
    int indent = (size - len) / 2;
    int i;

    for(i=len;i>=0;i--){
        s[i+indent] = s[i];
        s[i] = ' ';
    }
}
*/

main(){
    int cal[CAL_V][CAL_H];
    //char header[HEADER_LEN];
    int i, j;
    int year, month;
    time_t tt_now;
    struct tm st_now;

    tt_now = time(NULL);
    st_now = *localtime(&tt_now);
    month = st_now.tm_mon + 1;
    year = st_now.tm_year + 1900;


    //make_header(month, year, header);
    //printf("%s\n", header);
    printf("Su Mo Tu We Th Fr Sa\n");

    make_cal(month, year, cal);

    for(i=0;i<CAL_V;i++){
        for(j=0;j<CAL_H;j++){
            if(cal[i][j] != 0){
                printf("%2d ", cal[i][j]);
            }else{
                printf("   ");
            }
        }
        printf("\n");
    }
}
