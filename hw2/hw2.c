/* This program receives text as input and based of the given commands the program can print the given text , 
find the frequency of the used words and add synonyms to words through a file */

#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "hw2.h"

void lower(char *word);
int read_synonyms(char *filename, char synonyms[][MAX_WORD_LEN*2]) ;

/* This function receives the input text and arranges the used words to an array*/
void textInput(char Text[MAX_WORDS][MAX_WORD_LEN],char *pointers[MAX_WORDS][2]){
    int i = 0 ;
    int NumWords = 0 ;
    char word[MAX_WORD_LEN] = {'\0'} ;
    int wordCounter = 0 ;

    while(NumWords != MAX_WORDS){
        wordCounter = scanf("%s",word);
        if(wordCounter == EOF){
            break;
        }
        NumWords += wordCounter ;
        lower(word);
        for(i=0; i<NumWords; i++){
            if(strcmp(Text[i],word) == 0){
                pointers[NumWords-1][0] = pointers[i][0];
                break;
            }
        }
        if(i == NumWords){
            strcpy(Text[NumWords-1],word);
            pointers[NumWords-1][0] = Text[NumWords-1];
        }
    }
}
/* This function prints the given text based on the array that the words are placed. */
void textPrint(char *pointArray[MAX_WORDS][2],int linelen){
    int length = 1 ;
    int words = 0 ;
    int a = 0;
    int capital = 0;

    printf("\n");
    *pointArray[0][0] = toupper(*pointArray[0][0]);
    printf("%s",pointArray[0][0]);
    words++ ;
    length += strlen(pointArray[0][0]);
    *pointArray[0][0] = tolower(*pointArray[0][0]);

    if(pointArray[0][1] != NULL){
        printf(" ");
        length ++;
        *pointArray[0][1] = toupper(*pointArray[0][1]);
        length += (strlen(pointArray[0][1]) + 2);
        printf("(%s)",pointArray[0][1]);
        *pointArray[0][1] = tolower(*pointArray[0][1]);
    }
    *pointArray[0][0] = tolower(*pointArray[0][0]);

    for(a=1; words != MAX_WORDS && pointArray[a][0] != NULL; a++){
        if(a+1 < MAX_WORDS && pointArray[a+1][0] != NULL){
            if(strcmp(pointArray[a][0],".") == 0){
                *pointArray[a+1][0] = toupper(*pointArray[a+1][0]) ; 
                capital++ ;
                if(pointArray[a+1][1] != NULL){
                    *pointArray[a+1][1] = toupper(*pointArray[a+1][1]) ;
                    capital++ ; 
                }
            } 
            if(strcmp(pointArray[a][0],"!") == 0){
                *pointArray[a+1][0] = toupper(*pointArray[a+1][0]) ;
                capital++ ;
                if(pointArray[a+1][1] != NULL){
                    *pointArray[a+1][1] = toupper(*pointArray[a+1][1]) ;
                    capital++ ;
                }
            }
            if(strcmp(pointArray[a][0],"?") == 0){
                *pointArray[a+1][0] = toupper(*pointArray[a+1][0]) ;
                capital++ ; 
                if(pointArray[a+1][1] != NULL){
                    *pointArray[a+1][1] = toupper(*pointArray[a+1][1]) ;
                    capital++ ; 
                }
            }
        }
        words++ ;

        if(length + (strlen(pointArray[a][0]) + 1) == linelen){
            printf(" %s\n", pointArray[a][0]);
            length = 1;
        }else if(length + (strlen(pointArray[a][0]) + 1) > linelen){
            printf("\n");
            length = 1;
            printf("%s", pointArray[a][0]);
            length += strlen(pointArray[a][0]);
        }else if(length == 1){
            printf("%s", pointArray[a][0]);
            length += strlen(pointArray[a][0]);
        }
        else if(length + (strlen(pointArray[a][0]) + 1) < linelen){
            printf(" %s", pointArray[a][0]);
            length += (strlen(pointArray[a][0]) + 1);
        }

        if(pointArray[a][1] != NULL){
            if(length + (strlen(pointArray[a][1]) + 3) == linelen){
                printf(" (%s)\n", pointArray[a][1]);
                length = 1;
            }else if(length + (strlen(pointArray[a][1]) + 3) > linelen){
                printf("\n");
                length = 1;
                printf("(%s)", pointArray[a][1]);
                length += (strlen(pointArray[a][1]) + 2);
            }else if(length == 1){
                printf("(%s)", pointArray[a][1]);
                length += (strlen(pointArray[a][1]) + 2);
            }
            else if(length + (strlen(pointArray[a][1]) + 3) < linelen){
                printf(" (%s)", pointArray[a][1]);
                length += (strlen(pointArray[a][1]) + 3);
            }
        }
        

        if(capital > 0 && *pointArray[a][0] != '.' && *pointArray[a][0] != '!' &&  *pointArray[a][0] != '?'){
            *pointArray[a][0] = tolower(*pointArray[a][0]);
            if(pointArray[a][1] != NULL){
                *pointArray[a][1] = tolower(*pointArray[a][1]);
            }
            capital = 0 ;
        }
    }
    if(length != 1){
        printf("\n");
    }
}

/* This function calculates the frequency of the used words*/
void wordFrequency(char *wordPointers[MAX_WORDS][2],int numArray[]){
    int j = 0,k = 0 ;
    int sameWords = 0;

    for(j=0; j<MAX_WORDS && wordPointers[j][0] != NULL; j++){
        for(k=0; k<j; k++){
            if(wordPointers[j][0] == wordPointers[k][0]){
                numArray[k] += 1;
                sameWords++ ;
                break;
            }
        }
        if(k == j){
            numArray[j - sameWords] += 1;
        }
    }
}

/* This function finds the highest frequency */
int highestVolume(int intergerArray[]){
    int t ;
    int w ;
    int error = 0 ;

    for(t=0; intergerArray[t] != 0 && t<=MAX_WORDS; t++){
        error = 0;
        for(w=0; intergerArray[w] != 0 &&  w<=MAX_WORDS; w++){
            if((intergerArray[t] >= intergerArray[w]) == 0){
                error++;
                break ;
            }
        }
        if(error == 0){
            return intergerArray[t];
        }
    }
    return 400;
}

/*This function using the highest frequency finds other words with similar frequencies*/
int commonWordArray(char wordArray[MAX_WORDS][MAX_WORD_LEN],
                    char *pointerArray[MAX_WORDS][2],
                    char frequentWords[MAX_WORDS][MAX_WORD_LEN]){
    int numOfword[MAX_WORDS] = {0};
    int emptySpace = 0;
    int q = 0 ;

    wordFrequency(pointerArray,numOfword);
    for(q=0; q<MAX_WORDS && numOfword[q] != 0; q++){
        if(numOfword[q] == highestVolume(numOfword)){
           strcpy(frequentWords[q-emptySpace],wordArray[q]);
        }
        else{
            emptySpace++ ;
        }
    }
    return highestVolume(numOfword) ;
}

/* This function prints the words with the highest frequencies*/
void arrayPrint(char strArray[MAX_WORDS][MAX_WORD_LEN]){
    int r = 0 ;
    printf("\n");
    for(r=0; r<MAX_WORDS && strcmp(strArray[r],"\0") != 0; r++){
        printf("%s\n",strArray[r]);
    }
}

/* This function matches the given words with their synonyms*/
void synonymFinder(char *pArray[MAX_WORDS][2],char synonymsArray[MAX_SYNONYMS][MAX_WORD_LEN*2]){
    int p, m, q ;
    
    for(p=0; p<MAX_WORDS && pArray[p][0] != NULL; p++){
        for(q=0; q<MAX_SYNONYMS; q++){
            if(strcmp(synonymsArray[q],pArray[p][0]) == 0){
                pArray[p][1] = (synonymsArray[q] + strlen(pArray[p][0]) + 1);
                for(m=p; m<MAX_WORDS && pArray[p][0] != NULL; m++){
                    if(pArray[p][0] == pArray[m][0]){
                        pArray[m][1] = (synonymsArray[q] + strlen(pArray[p][0]) + 1) ;
                    }
                } 
            }
        }
    }
}

/******
 main
******/
int main (int argc, char *argv[]){
    int b = 0;
    int status = 2;
    int commands[3] = {0};
    char textfileName[MAX_FILENAME_LEN] = {'\0'};
    char *scriptP[MAX_WORDS][2] = {{NULL}};
    char script[MAX_WORDS][MAX_WORD_LEN] = {{'\0'}} ;
    char commonWords[MAX_WORDS][MAX_WORD_LEN] = {{'\0'}};
    char synonyms[MAX_SYNONYMS][MAX_WORD_LEN*2] = {{'\0'}};

    /* Argument checking */
    if(*(argv + 1) == NULL){
        printf("Incorrect command-line arguments!\n");
        return 1;
    }
    for(b=1; *(argv + b) != NULL; b++){
        if(strcmp(*(argv + b),"-m") == 0){
            *commands += 1;
        }
        else if(strcmp(*(argv + b),"-p") == 0){
            *(commands + 1) += 1;
        }
        else if(argc > b+1 && strcmp(*(argv + b),"-r") == 0){
            status = read_synonyms(*(argv + b + 1),synonyms);
            if(status == 1){
                strcpy(textfileName,*(argv + b + 1));
                *(commands + 2) += 1;
                b++;
            }else{
                printf("Incorrect command-line arguments!\n");
                return 1;
            }
        }      
        else if(strcmp(*(argv + b),"-r") == 0 || (strcmp(*(argv + b),"-m") != 0 && strcmp(*(argv + b),"-p") != 0)){
            printf("Incorrect command-line arguments!\n");
            return 1;
        }
    }

    textInput(script,scriptP);

    if(*commands != 0){
        printf("Max: %d",commonWordArray(script,scriptP,commonWords));
        arrayPrint(commonWords);
    }
    if((*commands + 2) != 0){
        synonymFinder(scriptP,synonyms);
    }
    if(*(commands + 1) != 0){
        textPrint(scriptP,MAX_LINE_LEN);
    }
    return 0;
}

/****************************************
 Converts the given string to lowercases
*****************************************/
void lower(char *word) {
    while (*word) {
        *word = tolower(*word);
        word++;
    }
}

    
/************************************************************
 Reads pairs of words and their synonyms from the given file
 and stores them in the table, one pair per line.
 The words of a pair are separated by a '\0'.

  Assumes the table has MAX_SYNONYMS rows.

  Returns 1 on success, 0 on failure.
*************************************************************/
int read_synonyms(char *filename, char synonyms[][MAX_WORD_LEN*2]) {
    int i;
    char word[MAX_WORD_LEN]={'\0'}, word_synonym[MAX_WORD_LEN]={'\0'};
    char format[30];
    FILE *fp;
  
    fp = fopen(filename, "r");
    if(!fp) {
        fprintf(stderr, "Error: Could not open file \"%s\" for reading\n", filename);
        return 0;
    }
  
    sprintf(format, "%%%ds", MAX_WORD_LEN-1);
    memset(synonyms, 0, MAX_SYNONYMS*MAX_WORD_LEN*2);  

    i=0;
    while(i < MAX_SYNONYMS && EOF != fscanf(fp, format, word)) {
        lower(word);
        strcpy(synonyms[i], word);
        if (EOF == fscanf(fp, format, word_synonym))  {   
            fclose(fp);
            fprintf(stderr, "Error: Missing synonym for word \"%s\"\n", word);
            return 0;
        }
        lower(word_synonym);
        strcpy(synonyms[i]+strlen(word)+1, word_synonym);
        i++;
    }
    fclose(fp);
    return 1;
}
