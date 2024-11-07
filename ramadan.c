#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
    time_t pres_time;
    time(&pres_time);
    char *time = ctime(&pres_time);
    char date_s[3], hour_s[3], minute_s[3];
    date_s[0] = time[8], date_s[1] = time[9], date_s[2] = '\0';
    hour_s[0] = time[11], hour_s[1] = time[12], hour_s[2] = '\0';
    minute_s[0] = time[14], minute_s[1] = time[15], minute_s[2] = '\0';
    // printf("date:%s hour:%s minute:%s", date, hour, minute);
    int date = atoi(date_s), hour = atoi(hour_s), minute = atoi(minute_s);
    // printf("date:%d hour:%d minute:%d", date, hour, minute);
    char position[4];
    int  i_hour, i_minute = 30 ;
    for(int count = 1, start_date = 11; start_date <= date ; )
    {
        if(count==1)
        {sprintf(position, "%c", count + '0'); position[1]='s', position[2]='t', position[3]='\0';}
        else if(count==2)
        {sprintf(position, "%c", count + '0'); position[1]='n', position[2]='d', position[3]='\0';}
        else if(count==3)
        {sprintf(position, "%c", count + '0'); position[1]='r', position[2]='d', position[3]='\0';}
        else if(count>3)
        {sprintf(position, "%c", count + '0'); position[1]='t', position[2]='h', position[3]='\0';}
        if(start_date<date){
            printf("Ramadan Day %d\n\n", count);
            for(int  i_hour = 22; start_date < date && i_hour <= 24 || i_minute < 59 ; i_minute++){
                if(i_hour==22 && i_minute==30)
                    printf("%s Taraweeh done!\n", position);
                if(i_minute==59)
                {
                    i_minute=0;
                    i_hour++;
                    if(i_hour==23){
                        i_hour=0;
                        start_date++;
                    }
                }
                if(i_hour==0 && i_minute==0)
                    printf("date: %d\n", start_date);
                printf("%d:%d\n", i_hour, i_minute);
                if(i_hour==5 && i_minute==45)
                    printf("%s Sehri done!\n", position);
                if(i_hour==18 && i_minute==30)
                    printf("%s Iftar done!\n\n", position);
                if(i_hour==19){
                    count++;
                    break;
                }
            }
        }
        if(start_date==date)break;
    }
    return 0;
}