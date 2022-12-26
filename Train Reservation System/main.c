#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct Trains{
    char PNR[100];
    char Name[1000];
    char From[100];
    char To[100];
    int km;
    int time[2];
    int departure[2];
} Trains;
Trains train[100];
int length;
typedef struct tm Time;
void Read();
void Book();
int main(){
    Read();
    Book();
    return 0;
}
int Menu(){
    int n;
    printf("Welcome to E-Ticketing System\n");
    printf("*****************************\n");
    printf("1. Book Ticket\n");
    printf("2. Cancel Ticket\n");
    printf("3. Check Train\n");
    printf("4. Exit\n");
    printf("Enter your choice (1,2,3,4): ");
    scanf("%d",&n);
}
char* substr(const char *src, int m, int n){
    int i,len=n-m;
    char *dest = (char*)malloc(sizeof(char)*(len + 1));
    for(i=m;i<n && (*(src+i)!='\0');i++,dest++) *dest = *(src+i);
    *dest = '\0';
    return dest - len;
}
void Read(){
    int i,j;
    FILE *file = fopen("Trains.csv","r");
    char line[1024];
    for(i=0;fgets(line, sizeof(line), file);i++){
        char* value = strtok(line, ",");
        for(j=0;value;j++){
            switch(j){
                case 0: strcpy(train[i].PNR, value); break;
                case 1: strcpy(train[i].Name, value); break;
                case 2: strcpy(train[i].From, value); break;
                case 3: strcpy(train[i].To, value); break;
                case 4: train[i].km = atoi(value); break;
                case 5:
                    train[i].time[0] = atoi(substr(value,0,2));
                    train[i].time[1] = atoi(substr(value,3,5));
                    break;
                case 6: 
                    train[i].departure[0] = atoi(substr(value,0,2));
                    train[i].departure[1] = atoi(substr(value,3,5));
                    break;
            }
            value = strtok(NULL, ",");
        }
    }
    length = i;
    fclose(file);
}
Time DOD(int d, int m, int y, int* tod){
    Time time;
    time.tm_sec = 0;
    time.tm_min = *(tod+1);
    time.tm_hour = *tod;
    time.tm_mday = d;
    time.tm_mon = m-1;
    time.tm_year = y-1900;
    time.tm_isdst = -1;  
    return time;
}
Time DOA(int d, int m, int y, int* t, int* tod){
    Time time;
    int minutes = *(t+1) + *(tod+1);
    int hours = *t + *tod + minutes/60;
    int days = d + hours/24;
    time.tm_sec = 0;
    time.tm_min = minutes%60;
    time.tm_hour = hours%24;
    time.tm_mday = days%30;
    time.tm_mon = m+days/30-1;
    time.tm_year = y-1900;
    time.tm_isdst = -1;  
    return time;
}
void display_coach(int n){
    FILE *file = fopen("Seats.csv","r+");
    int ac1,ac2,ac3,sl;
    float p,pac1,pac2,pac3,psl;
    printf("Seats Available:\tAC1 (1)\t\tAC2 (2)\t\tAC3 (3)\t\tSL (4)");
    fseek(file,n*30+12,SEEK_SET);
    fscanf(file, "%f,%d,%d,%d,%d",&p,&ac1,&ac2,&ac3,&sl);
    train[n].km/=2;
    pac1 = p*train[n].km+3000;
    pac2 = p*train[n].km+1000;
    pac3 = p*train[n].km+500;
    psl = (p/2)*train[n].km;
    printf("\n\t\t\t%d\t\t%d\t\t%d\t\t%d\nPrice/Person:\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f",ac1,ac2,ac3,sl,pac1,pac2,pac3,psl);
    fclose(file);
}
void Book(){
    char from[100],to[100],sdoa[100],sdod[100];
    int d,m,y,i,c=0,a[100],f;
    printf("Train Booking\n");
    printf("*************\n");
    printf("From: ");
    gets(from);
    printf("To: ");
    gets(to);
    printf("Date (dd/mm/yyyy): ");
    scanf("%d/%d/%d",&d,&m,&y);
    printf("Available Trains: \n");
    printf("S.No\tPNR\t\tName\t\t\tFrom\t\tTo\t\t\tDistance\tDate of Departure\t\tDate of Arrival\n");
    for(i=0;i<length;i++){
        if(strcmp(train[i].From, from)==0 && strcmp(train[i].To, to)==0){
            Time dod = DOD(d,m,y,train[i].departure);
            Time doa = DOA(d,m,y,train[i].time,train[i].departure);
            strftime(sdod, sizeof(dod), "%c", &dod);
            strftime(sdoa, sizeof(doa), "%c", &doa);
            a[c]=i-1;
            c++;
            printf("(%d)\t%s\t%s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%s\n",c,train[i].PNR,train[i].Name,train[i].From,train[i].To,train[i].km/2,sdod,sdoa);
        }
    }
    if(c){
        printf("Choose Train: ");
        scanf("%d",&i);
        display_coach(a[i]);
    }
}
