#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}
 

int main(void){
  char word[100000]; 
  printf("Enter a word: ");
  scanf("%s",word);
  int counter=0; //counts the occurences of the given word
  FILE* review = fopen("movieReviews.txt","r"); //opening movieReviews.txt
  char display[1000000]; //used for storing the lines
  int temp=0;   //the current score in the line
  int score=0;  //total score
  float avg=0;  //average
  while(1){
    fgets(display,999999,review); //gets the line
    
    if(feof(review)) { fclose(review); break;}  //checks the end of file
  
    char * token = strtok(display," ");
    temp= atoi(token);  //the point of the sentence
    while( token != NULL ) {
    
      if (strcmp(toLower(word),toLower(token)) == 0)  {  //checks whether strings are equal
	  counter++;
          score+=temp;      
      }

      token = strtok(NULL," ");
    }
  } 
   if(counter>0)   avg=(float)(score)/(float)(counter); //average
    
   printf("%s appears %d times. \nThe average score for reviews containing the word %s is %.4f\n ",word,counter,word,avg); 
 
  //max occuring word
  
   FILE* wordList = fopen("wordList.txt","r");
   int pos[44];  //positive review array
   int neg[44];  //negative review array
   int t=0;      
   int pos_occ=0;  //positive review counter
   int neg_occ=0;  //negative review counter
   char a[44][100];  //stores the words in the wordList.txt
   char textWord[1000000]; //stores the line in txt files
   fgets(textWord,999999,wordList);
   fclose(wordList);   
   char* tokenizer=strtok(textWord,"\r");
   while(tokenizer !=NULL){    //tokenizing the words and storing in the array
     strcpy(a[t++],tokenizer);	   
     tokenizer=strtok(NULL,"\r");
   }
  
 
   FILE* movieReview;

   for(int j=0;j<44;j++){
    movieReview = fopen("movieReviews.txt","r"); //opens the movieReview.txt
    while(1){
      fgets(textWord,999999,movieReview);  //stores the line in the txt file
      if(feof(movieReview)) { fclose(movieReview);  break; }  //checks the end of the file
      char * token_2 = strtok(textWord," ");  //tokenizing
      temp= atoi(token_2);
      while( token_2 != NULL ) {
        if(strcmp(toLower(a[j]),toLower(token_2)) == 0 ) {  //string comparision
           if(temp>2){
             pos_occ++;   
           }else{
             neg_occ++;
           }  
        }  
        token_2 = strtok(NULL," ");
      }
    }
    pos[j]=pos_occ;
    neg[j]=neg_occ;
    pos_occ=0;  //makes zeros for the new word
    neg_occ=0; 


  }
  
  int timer=0; 
  int pos_max=0;
  int neg_max=0;
  while(timer<44) {
      
      if(pos[pos_max]<pos[timer]){
       pos_max=timer;
      }
      if(neg[neg_max]<neg[timer]){
       neg_max=timer;
      }
      timer++; 

  }

  printf("%s is the most used word with %d appearences in the positive reviews and\n%s is the most used word with %d appearences in the negative reviews\n",a[pos_max],pos[pos_max],a[neg_max],neg[neg_max] );

   return 0;
}
