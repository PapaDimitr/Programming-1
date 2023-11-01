/*
This program receives info about courses and arranges the schedule based on specific prefrences 
given from the user.The user can print the courses info,schedule or even delete a course.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hw3.h"

struct course{
    int CourseID ;
    char ProfessorName[MAX_NAME_LEN] ;
    int NumOfStudents ;
};

struct amphitheater{
    int capacity ;
    struct course *schedule[WORKING_HOURS][WORKING_DAYS];
};

/* This function searches for the course before its added */
struct course *courseSearch(struct course CourseInfo[],int IdNum){
    int b = 0;
    for(b=0; b<MAX_COURSES; b++){
        if(CourseInfo[b].CourseID == IdNum){
            return &CourseInfo[b];
        }
    }
    if(b == MAX_COURSES){
        for(b=0; b<MAX_COURSES; b++){
            if(strcmp(CourseInfo[b].ProfessorName,"\0") == 0){
                return &CourseInfo[b];
            }
        }
    }
    return NULL ;
}

/* This function adds courses to the course array */
int courseAddition(struct course CourseInfo[],int IdNum,int Students,char *Name){
    struct course *searchResult ;

    searchResult = courseSearch(CourseInfo,IdNum);
    if(searchResult == NULL){
        return -1;
    }else if(searchResult->CourseID == IdNum){
        return 0;
    }else{
        searchResult->CourseID = IdNum;
        searchResult->NumOfStudents = Students;
        strcpy(searchResult->ProfessorName,Name) ;
        return 1;
    }
}

/* This function prints the course array */
void coursePrint(struct course CourseInfo[]){
    int h = 0 ;
    int p = 0 ;

    for(h=0; h<MAX_COURSES; h++){
        if(CourseInfo[h].CourseID != 0){
            printf("[%d]", CourseInfo[h].CourseID);
            printf(" %s", CourseInfo[h].ProfessorName);
            printf(" %d\n", CourseInfo[h].NumOfStudents);
            p++;
        }
    }
    if(p == 0){
        printf("No courses.\n");
    }
}

/* This function schedules the courses based on rooms available and other prefrences*/
int coursePlacement(struct amphitheater SpaceInfo[],struct course *CourseInfo,int Duration){
    int i = 0, t = 0, d = 0, a = 0, h = 0 ;

    for(i=0; i<MAX_ROOMS && SpaceInfo[i].capacity != 0; i++){
        if(SpaceInfo[i].capacity >= CourseInfo->NumOfStudents){
            for(t=0; t<WORKING_HOURS; t++){
                for(d=0; d<WORKING_DAYS; d++){
                    if(WORKING_HOURS - t >= Duration){
                        for(a = 0; a<Duration; a++){
                            if(SpaceInfo[i].schedule[t+a][d] != NULL){
                                break;
                            }
                            for (h = 0; h < MAX_ROOMS; h++){
                                if(SpaceInfo[h].schedule[t+a][d] != NULL && 
                                   strcmp(SpaceInfo[h].schedule[t+a][d]->ProfessorName,CourseInfo->ProfessorName) == 0){
                                    break;
                                }
                            }
                            if(h < MAX_ROOMS){
                                break;
                            }
                        }
                    }
                    if(a == Duration){
                        for(a=0; a<Duration; a++){
                            SpaceInfo[i].schedule[t+a][d] = CourseInfo;
                        }
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

/* This function prints a selected space's schedule */
void roomPrint(struct amphitheater *room){
    char *days[] = {"MON","TUE","WED","THU","FRI"} ;
    int d, t;

    printf("\n[%d]\n", room->capacity);
    printf("       ");
    for(d=0; d<WORKING_DAYS; d++){
        if(d+1 == WORKING_DAYS){
            printf("%s", *(days+d));
        }else{
            printf("%s ", *(days+d));
        }
    }
    printf("\n");
    for(t=0; t<WORKING_HOURS; t++){
        printf("%02d:00  ", t+10);
        for(d=0; d<WORKING_DAYS; d++){
            if(room->schedule[t][d] != NULL){
                printf("%-4d", room->schedule[t][d]->CourseID);
            }else{
                printf(" -  ");
            }
        }
        printf("\n");
    }

}

/* This function prints the whole schedule */
void spacesPrint(struct amphitheater SpaceInfo[]){
    int i;

    for(i=0; i<MAX_ROOMS && SpaceInfo[i].capacity != 0; i++){
        roomPrint(SpaceInfo+i);
    }
}

/* This function removes courses from the course array */
int courseRemoval(struct course CourseInfo[],int IdNum,struct amphitheater SpaceInfo[]){
    int a,t,d,i;


    for(a=0; a<MAX_COURSES; a++){
        if(CourseInfo[a].CourseID == IdNum){
            for(i=0; i<MAX_ROOMS && SpaceInfo[i].capacity != 0; i++){
                if(SpaceInfo[i].capacity >= CourseInfo[a].NumOfStudents){
                    for(d=0; d<WORKING_DAYS; d++){
                        for(t=0; t<WORKING_HOURS; t++){
                            if(SpaceInfo[i].schedule[t][d] != NULL 
                               && SpaceInfo[i].schedule[t][d]->CourseID == IdNum){
                                SpaceInfo[i].schedule[t][d] = NULL ;
                            }
                        }
                    }
                }
            }
            CourseInfo[a].CourseID = 0 ;
            CourseInfo[a].NumOfStudents = 0;
            strcpy(CourseInfo[a].ProfessorName,"\0");
            return 2 ;
        }
    }
    return 0;
}

int main (int argc, char *argv[]) {
    int i = 0;
    struct course CourseInfo[MAX_COURSES] = {0};
    struct amphitheater SpaceInfo[MAX_ROOMS] = {{0,{{NULL}}}} ;
    char Name[MAX_NAME_LEN];
    char formatStr[MAX_NAME_LEN];
    int IdNum;
    char choice ;
    int Students ;
    int EndResult;
    int Duration = 0 ;

    if(argc-1 > MAX_ROOMS || argc == 1){
        printf("Incorrect command-line arguments!\n");
        return -1;
    }
    for(i=1; i<argc; i++){
        if(atoi(argv[i]) < atoi(argv[i-1]) && i != 1){
            printf("Incorrect command-line arguments!\n");
            return -1;
        }
        if(atoi(argv[i]) <= 0){
            printf("Incorrect command-line arguments!\n");
            return -1;
        }
        SpaceInfo[i-1].capacity = atoi(argv[i]) ;
    }

    while(1){
        print_menu();
        scanf(" %c", &choice);
        if(choice == 'q'){
            return 0;
        }
        else if(choice == 'a'){
            printf("Professor course students:\n");
            sprintf(formatStr,"%%%ds", MAX_NAME_LEN-1);
            scanf(formatStr, Name);
            scanf("%d %d",&IdNum, &Students);
            EndResult = courseAddition(CourseInfo,IdNum,Students,Name);
            if(EndResult == -1){
                printf("No space.\n");
            }else if(EndResult == 0){
                printf("%d exists.\n", IdNum);
            }else if(EndResult == 1){
                printf("%d added.\n", IdNum);
            }
        }
        else if(choice == 'c'){
            coursePrint(CourseInfo);
        }
        else if(choice == 's'){
            printf("Course duration:\n");
            scanf("%d %d",&IdNum, &Duration);
            if(Duration < 1){
                printf("Invalid duration.\n");
            }
            else{
                for(i=0; i<MAX_COURSES; i++){
                    if(IdNum == CourseInfo[i].CourseID){
                        EndResult = coursePlacement(SpaceInfo,CourseInfo + i,Duration);
                        if(EndResult != -1){
                            printf("%d scheduled in %d.\n", IdNum, EndResult);
                        }
                        else{
                            printf("%d not scheduled.\n", IdNum);
                        }
                        break;
                    }
                }
                if(i == MAX_COURSES){
                    printf("%d not found.\n", IdNum);
                }
            }
        }
        else if(choice == 'p'){
            spacesPrint(SpaceInfo);
        }
        else if(choice == 'r'){
            printf("Course:\n");
            scanf("%d", &IdNum);
            EndResult = courseRemoval(CourseInfo,IdNum,SpaceInfo);
            if(EndResult != 0){
                printf("%d deleted.\n",IdNum);
            }else{
                printf("%d not deleted.\n",IdNum);
            }
        }
        else{
            printf("Invalid choice.\n");
        }
    }

	return 0;
}
