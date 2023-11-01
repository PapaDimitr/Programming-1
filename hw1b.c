/* 
  ONOMATEPWNYMO Dimitris Papadimitriou
  AEM 03750
 */
/*To programma lamvanei ta stoixeia kai tis pshfous kathe pshfoforou se dekaexadikh 
kwdikopoihsh kai eksagei to nikhth kai ta antistoixa stoixeia kai statistika*/

#include <stdio.h>
#include"hw1.h"

int main (int argc, char *argv[]) {
	unsigned short int VoterNum ;
	int voter = 0 ;
	int candidate = 0;
	int CCounter = 0 ;
	unsigned short int voterInfo[MAX_VOTERS][3] = {{0}};
	unsigned int candidateInfo[NUM_CANDIDATES][3] = {{0}} ;
	unsigned int results[NUM_CANDIDATES] = {0} ;
	unsigned int resultsGender[3] = {0};
	unsigned int AgeGroups[4] = {0};
	int Vote, VoteCounter = 0;
	int gender = 0;
	int Age = 0 ;
	int digit = 0 ;
	int ActualVote = 0;
	int winner = 0;
	int genderC = 0 ;
	int VoteCompa = 0 ;
	char selection ;
	char genderChar ;
	int error ;
	int ActualVoters = 0 ;


  /*Eisodos stoixeiwn pshfoforwn*/

	for (voter = error = 0; voter < MAX_VOTERS; voter++){
		printf("Enter voter info:\n");
		scanf("%hx", &VoterNum);

		if(VoterNum == 0){
			break ;
		}

     /*Apokwdikopoihsh stoixeiwn pshfoforwn*/

	    Vote = VoterNum & 0x7F ;
	    VoterNum >>= 7 ;
	    gender = VoterNum & 0x3 ;
	    VoterNum >>= 2 ;
	    Age = VoterNum & 0x7F ;

		VoteCounter = 0;
		if(Vote != 0){
			for(digit = 0; digit <= 6; digit++){
		    VoteCounter += ((Vote & (0x1 << digit)) >> digit) ;
		    if(((Vote & (0x1 << digit)) >> digit) == 1){
			ActualVote = digit ;
			}
		  }
		}else{
			ActualVote = '-' ;
		}

		if(Age < 18){
			printf("Invalid age %d.\n", Age);
			error ++ ;
		}
		if(gender < 1 || gender > 3){
			printf("Invalid gender.\n");
			error ++ ;
		}
		if(VoteCounter > 1){
			printf("Invalid votes %d.\n", VoteCounter);
			error ++ ;
		}

		/* Kataxwrhsh stoixeiwn pshfoforwn */

		if(error == 0){
			voterInfo[voter][0] = ActualVote;
			voterInfo[voter][1] = gender;
			voterInfo[voter][2] = Age;

			if(ActualVote != '-'){
			 candidateInfo[voterInfo[voter][0]][voterInfo[voter][1] - 1] += 1 ;
			 results[voterInfo[voter][0]] += 1 ;
			}
			if(Age >= 18 && Age <= 29){
				AgeGroups[0] += 1;
			}
			else if(Age >= 30 && Age <= 44){
				AgeGroups[1] += 1;
			}
			else if(Age >= 45 && Age <= 59){
				AgeGroups[2] += 1;
			}
			else if(Age >= 60){
				AgeGroups[3] += 1;
			}
		}else if (error != 0){
			voter -- ;
			error = 0;
		}
	}
	ActualVoters = voter ;
    
	/* Euresh nikhth */

	for(candidate = 0; candidate<NUM_CANDIDATES; candidate++){
		for(CCounter = VoteCompa = 0; CCounter<NUM_CANDIDATES; CCounter++){
			VoteCompa += results[candidate] >= results[CCounter];
		}
		if(VoteCompa == NUM_CANDIDATES){
			winner = candidate ;
			break;
		}
	}

    /* Euresh nikhth se kathe filo */

	for(genderC = 0; genderC<3; genderC++){
	   for(candidate = 0; candidate<NUM_CANDIDATES; candidate++){
		 for(CCounter = VoteCompa = 0 ; CCounter<NUM_CANDIDATES; CCounter++){
			VoteCompa += candidateInfo[candidate][genderC] >= candidateInfo[CCounter][genderC] ;
		 }
		 if(VoteCompa == NUM_CANDIDATES){
			resultsGender[genderC] = candidate;
			break;
		 }
	   }
	}

	while(1){
		printf("\n");
		printf("[P/p] Print voter info\n");
        printf("[C/c] Print candidate info\n");
        printf("[W/w] Print winner\n");
        printf("[G/g] Print choice by gender\n");
        printf("[A/a] Print ages\n");
        printf("[Q/q] Quit\n");
		printf("\n");

		scanf(" %c", &selection);

		if(selection == 'P' || selection == 'p'){
			printf("\n##\n");
			for(voter = 0; voter<ActualVoters; voter++){
				if(voterInfo[voter][1] == 1){
					genderChar = 'M' ;
				}else if(voterInfo[voter][1] == 2){
					genderChar = 'F' ;
				}else{
					genderChar = 'O' ;
				}
				printf("%3d: %3d %c", voter, voterInfo[voter][2], genderChar);
				if(voterInfo[voter][0] == '-'){
					printf(" -\n");
				}
				else{
					printf(" %d\n", voterInfo[voter][0]);
				}
			}
		}
		else if(selection == 'C' || selection == 'c'){
			printf("\n##\n");
			for(candidate = 0; candidate<NUM_CANDIDATES; candidate++){
				printf("%3d:",candidate);
				printf(" %3d",candidateInfo[candidate][0]);
				printf(" %3d",candidateInfo[candidate][1]);
				printf(" %3d\n",candidateInfo[candidate][2]);
			}
		}
		else if(selection == 'W' || selection == 'w'){
			printf("\n##\n");
			printf("%d: %d\n", winner, results[winner]);
		}
		else if(selection == 'G' || selection == 'g'){
			printf("\n##\n");
			printf("M: %d (%d)\n", resultsGender[0], candidateInfo[resultsGender[0]][0]);
			printf("F: %d (%d)\n", resultsGender[1], candidateInfo[resultsGender[1]][1]);
			printf("O: %d (%d)\n", resultsGender[2], candidateInfo[resultsGender[2]][2]);
		}
		else if(selection == 'A' || selection == 'a'){
			printf("\n##\n");
			printf("[18-29]: %d\n", AgeGroups[0]);
			printf("[30-44]: %d\n", AgeGroups[1]);
			printf("[45-59]: %d\n", AgeGroups[2]);
			printf("[60-127]: %d\n", AgeGroups[3]);
		}
		else if(selection == 'Q' || selection == 'q'){
			break;
		}
		else{
			printf("Error. Invalid option.\n");
		}
	}
	
	return 0;
}
