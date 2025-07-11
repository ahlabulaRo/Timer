#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>

void citire(char** timp){
    printf("Type the value of the time for timer(x hours y minutes z seconds): ");
    fgets((*timp) ,  100 , stdin);
    (*timp)[strcspn(*timp , "\n")] = '\0';
}

int verificare_citire(char* timp , int* vec){
    if((strstr(timp , "hours") == NULL) &&
    (strstr(timp , "minutes") == NULL) &&
    (strstr(timp , "seconds") ==  NULL))  return 0;
    
    if( (vec[0] < 0) || (vec[1] < 0) || (vec[2] < 0) ) return 0;
    return 1;
}

int* vector_date(char* timp){
    int* vec = (int*)calloc(3 , sizeof(int));

    char* copie = (char*)malloc(100 * sizeof(char));
    strncpy(copie , timp , 99);
    copie[99]='\0';

    char* p;
    p=strstr(copie , "hours");
    if(p != NULL){
        if (isdigit(*(p - 2)) && !isdigit(*(p - 3))) {
            vec[0] = atoi(p - 2);
            }else vec[0] = atoi(p - 3);
        }

    p = strstr(copie, "minutes");
    if (p != NULL) {
        if (isdigit(*(p - 2)) && !isdigit(*(p - 3))) {
            vec[1] = atoi(p - 2);
            }else vec[1] = atoi(p - 3);
        }

    p = strstr(copie, "seconds");
    if (p != NULL) {
        if (isdigit(*(p - 2)) && !isdigit(*(p - 3))) {
            vec[2] = atoi(p - 2);
            }else vec[2] = atoi(p - 3);
        }

    free(copie);
    return vec;
}

void temporizator(int h , int m , int s){
    while(h>0 || m>0 || s>0){
        printf("\rHours:%3d\t Minutes:%3d\t Seconds:%3d\t",h,m,s);
        fflush(stdout);
        sleep(1);
        if(s>0) s--;
        else{
            if(m>0){
                m--;
                s=59;
            }
            else{
                if(h>0){
                    h--;
                    m=59;
                    s=59;
                }
                else break;
            }
        }
    }
    printf("\nTime is out!\n");
}

int main(){
    char* timp = (char*)malloc(100 * sizeof(char));
    citire(&timp);
    int* vec = vector_date(timp);
    if(!verificare_citire(timp , vec)) printf("Invalid data!\n");
    else{
        printf("Time set at: %d hours, %d minutes, %d seconds!\n" , vec[0] , vec[1] , vec[2]);
        sleep(1);
        printf("We'll start in: 3");
        fflush(stdout);
        sleep(1);
        printf(", 2");
        fflush(stdout);
        sleep(1);
        printf(", 1\n");
        fflush(stdout);
        sleep(1);
        printf("GO:\n");
    }
    temporizator(vec[0] , vec[1] , vec[2]);
    free(vec);
    free(timp);
    vec = NULL;
    timp = NULL;
    return 0;
}
