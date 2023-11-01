/*
  ONOMATEPWNYMO Dimitris Papadimitriou
  AEM 03750
 */
/*To parakatw programma lamvanei tis apantiseis mathitwn kai typwnei 
thn vathmologia,ton meso oro kai alla antistoixa statistika gia to synolo*/

#include <math.h>
#include "hw1.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
	int numChoices ;
	char maxChoice ;
	int numAnswers ;
	char rightAnswers[NUM_QUESTIONS];
	char Choice ;
    double penalty ;
	char studentAnswers[NUM_QUESTIONS];
	char studentAnswer ;
	int Students ;
	int numStudentAnswer;
	double studentInfo[NUM_STUDENTS][4];
	int questionChecked;
	int correct = 0 ;
	int wrong = 0 ;
	int empty = 0;
	double Grade ;
	double average ;
	double add = 0 ;
	int column = 0 ;
	double standardDaviation ;
	double series = 0 ;
	int numSection[10] ; 
	char selection ;
	int low, high ;
	int NumInRange = 0;
	int indexRange1 ;
	int indexRange2 ;
	int Ekatontades;
	int Dekades;
	int monades;
	int numHistogram;

    /* Eisodos arithmou epilogwn */
    do{
     printf("Enter number of choices:\n");
	 scanf("%d", &numChoices);
	}
    while((numChoices < 1) || (numChoices > 26));
    maxChoice = '@' + numChoices ;
	printf("Max choice: '%c'\n", maxChoice);

    /* Eisodos swstwn apantisewn */

    printf("Enter answer key:\n");
	for(numAnswers = 0 ; numAnswers < NUM_QUESTIONS; numAnswers++){
		scanf(" %c", &Choice);
	 while(Choice > maxChoice){
		printf("Error. Enter value A-%c:\n", maxChoice);
		scanf(" %c", &Choice);
	 }
	 rightAnswers[numAnswers] = Choice ;
	}

	/*Eisodos poinhs gia lanthasmenes apantiseis*/

	printf("Enter wrong answer penalty:\n");
	scanf("%lf", &penalty);
	while(penalty > 0){
		printf("Error. Enter non-positive value:\n");
        scanf("%lf", &penalty);
	}

    /*Eisodos apantisewn mathhtwn*/

	printf("Enter student answers:\n");
	for(Students = 0 ; Students < NUM_STUDENTS; Students++){
		for(numStudentAnswer = 0 ; numStudentAnswer < NUM_QUESTIONS ; numStudentAnswer++){
		 scanf(" %c", &studentAnswer);
		 while (((studentAnswer > maxChoice) || (studentAnswer <  'A')) && studentAnswer != '-'){
			printf("Error. Enter valid answer:\n");
			scanf(" %c", &studentAnswer);
		 }
		 studentAnswers[numStudentAnswer] = studentAnswer ;
		}

     /*Eleghos apantisewn*/

     for(questionChecked = correct = wrong = empty = 0 ; questionChecked < NUM_QUESTIONS ; questionChecked++){
		 if ((int)rightAnswers[questionChecked] == (int)studentAnswers[questionChecked]){
			 correct++ ;
		 }
		 else if ((rightAnswers[questionChecked] != studentAnswers[questionChecked]) && (studentAnswers[questionChecked] != '-') ){
			 wrong++ ;
		 }
		 else if(studentAnswers[questionChecked] == '-'){
			 empty++ ;
		 }
	 }
	 studentInfo[column][0] = correct ;
	 studentInfo[column][1] = wrong ;

	 Grade = ((correct + (wrong * penalty))/NUM_QUESTIONS)*10;
	 if(Grade < 0){
		studentInfo[column][2] = 0;
	 }
	 else{
	    studentInfo[column][2] = Grade ;
	 }
     
	 studentInfo[column][3] = empty ;

	 column++ ; 

	}

    /*Ypologismos mesou orou*/

    for (Students = column = 0; Students < NUM_STUDENTS ; Students++){
		add += studentInfo[column][2];
		column ++ ;
	}
	
	average = add / NUM_STUDENTS ;
    
    /*Ypologismos standard deviation*/

	for(Students = column = 0; Students <  NUM_STUDENTS ; column++ ,Students++){
		series += pow((studentInfo[column][2] - average),2) ;
	}
    standardDaviation = sqrt(series/NUM_STUDENTS);

	int pos ;

    /* Arxikopoihsh pinaka bathmwn */

	for(pos = 0 ; pos < 10 ; pos++){
		numSection[pos] = 0 ;
	}
    
	/* Topothetish mathhtwn se pinaka vash tou vathmou */

	for(Students = column = 0 ; Students < NUM_STUDENTS ; Students++ ,column++){
		if((int)floor(studentInfo[column][2]) != 10){
		    numSection[(int)floor(studentInfo[column][2])] += 1 ;
		}
		else{
			numSection[(int)floor(studentInfo[column][2]) - 1] += 1 ;
		}
	}
	
	printf("\n");

   while(1){ 
     printf("[M/m] Print mean\n");
     printf("[S/s] Print standard deviation\n");
     printf("[G/g] Print grade range\n");
     printf("[I/i] Print student info in range\n");
     printf("[H/h] Draw histogram\n");   
	 printf("[Q/q] Quit\n");

	 scanf(" %c", &selection);

		if(selection == 'M' || selection == 'm'){ 
		   printf("%0.2lf", average);
		   printf("\n##\n");
		   printf("\n");
		}
		else if (selection == 'S' || selection == 's') {
			printf("%0.2lf", standardDaviation);
			printf("\n##\n");
			printf("\n");
		}
		else if(selection == 'G' || selection == 'g') {
			do{
			   printf("Enter grade range:\n");
			   scanf("%d-%d", &low, &high);
			}
			while(low > 10 || high > 10 || low < 0 || high < 0 || low >= high);

			if(high != 10){
				for (NumInRange = 0; low < high ; low++){
					NumInRange += numSection[low];
				}
				printf("%d", NumInRange);
				printf("\n##\n");
				printf("\n");
			}
			else{
				for(NumInRange = 0; low <= (high - 1); low++){
					NumInRange += numSection[low];
				}
				printf("%d", NumInRange);
				printf("\n##\n");
				printf("\n");
			}
		}
		else if (selection == 'I' || selection == 'i'){
			do{
				printf("Enter index range:\n");
				scanf("%d-%d", &indexRange1, &indexRange2);
			}
			while(indexRange1 >= NUM_STUDENTS || indexRange2 >= NUM_STUDENTS || indexRange1 < 0 || indexRange2 < 0 || indexRange1 > indexRange2);

			for (column = Students = indexRange1; Students <= indexRange2 ; Students++){
				printf("%03d:",column); 
				printf("%4d,",(int)studentInfo[column][0]); 
				printf("%4d,",(int)studentInfo[column][1]); 
				printf("%4d,",(int)studentInfo[column][3]);
				printf("%6.2f\n",studentInfo[column][2]);
				column++ ;

			}
			printf("\n##\n");
			printf("\n");
		}
		else if (selection == 'H' || selection == 'h'){
			for(pos = 0; pos < 10; pos++){
				numHistogram = numSection[pos];
				for(Ekatontades = 0 ; numHistogram >= 100;){
					numHistogram -= 100 ;
					Ekatontades ++;
				}
				for(Dekades = 0; numHistogram >= 10;){
					numHistogram -= 10;
					Dekades ++;
				}
				for(monades = 0; numHistogram > 0;){
					numHistogram -= 1;
					monades ++;
				}
				if(pos + 1 != 10){
					printf("[%2d,%2d): ", pos, pos+1 );
				}
				else{
					printf("[%2d,%2d]: ", pos, pos+1 );
				}
				for(; Ekatontades > 0; Ekatontades--){
					printf("@");
					}
				for(; Dekades > 0; Dekades--){
					printf("*");
				}
				for(; monades > 0; monades--){
					printf("-");
				}
				printf("\n");
			}
			printf("\n##\n");
			printf("\n");
		}else if (selection == 'Q' || selection == 'q'){
			break;
		}
		else{
			printf("Error. Invalid option.\n");
			printf("\n");
		}
    }	
  return 0 ;
}