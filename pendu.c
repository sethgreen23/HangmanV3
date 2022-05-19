#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pendu* pendu;
typedef struct _pendu S_pendu;

struct _pendu{
  char tries[26];
  int remaining_letter;
  int remaining_errors;
  char* word;
  int len;
};
char* make_uppercase(char* str){
  char* word=malloc(sizeof(char)*strlen(str));
  int i;
  for(i=0;str[i]!='\0';i++){
    char c = str[i];
    if(c>='a' && c<='z'){
      word[i]=str[i]+('A'-'a');
    }
    else{
      word[i]=str[i];
    }   
  }
  word[i]='\0';
  return word;
}

 char pendu_is_letter(char letter){
  if(letter<'A' || letter>'Z')
    return 0;
  return 1;
}
void pendu_debug_char(char tab[]){
  printf("[ ");
  int i;
  for(i=0;i<26;i++){
    if(i!=25)
      printf("%d, ",tab[i]);
    else
      printf("%d",tab[i]);
  }
  printf(" ]");
}
void pendu_debug_pendu(pendu p){
  printf("word: %s\nremaining error: %d\nremaining letter: %d\nword len: %d\ntries: ",p->word,p->remaining_errors,p->remaining_letter,p->len);
  pendu_debug_char(p->tries);
}

void pendu_show_word(pendu p){
  int i=0;
  for(;i<p->len;i++){
    char c = p->word[i];
    if((p->tries[c-'A']==1)||!pendu_is_letter(c)){
      printf("%c",c);
    }else{
      printf("-");
    }
  }
  printf("\n");
}
void pendu_init_count_remining_letters(pendu p,char first){
  int count=0;
  for(int i=0;p->word[i]!='\0';i++){
    if(p->word[i]==first)
      count++;
  }
  p->remaining_letter-=count;
}
void pendu_init_count_remining_letters_if_not_letter(pendu p){
  int count=0;
  char* word = p->word;
  for(int i=0;word[i]!='\0';i++){
    if(!pendu_is_letter(word[i]))
      count++;
  }
  p->remaining_letter-=count;
}
void pendu_init(pendu p, char* word,int error_len){
  //initialise the values
  p->word = word;
  p->len = strlen(p->word);
  p->remaining_errors=error_len;
  p->remaining_letter=p->len;
  for(int i=0;i<26;i++){
    p->tries[i]=0;
  }  
  //mark the first and the last letter as tried
  char first = p->word[0];
  char last = p->word[p->len-1];
  if(pendu_is_letter(first)){
    p->tries[first-'A']=1;
    pendu_init_count_remining_letters(p,first);
  }
  if(pendu_is_letter(last)){
    p->tries[last-'A']=1;
    //count and retrieve count of this letter in the word
    //from the remaining_letter variable
    pendu_init_count_remining_letters(p, last);
  }
  //count the number of the special caracter if they exist 
  //and retrive it from the remaining letters
  pendu_init_count_remining_letters_if_not_letter(p);
  //retrive the count of the two first letters
  // function to retrieve the remaining letter of the first and last word
  
  // p->remaining_letter-=2;
  
}
int pendu_letter_exist_in_word(pendu p,char c){
  int i=0,yes=0;
  for(;p->word[i]!='\0';i++){
    if(p->word[i]==c){
      yes=1;
      break;
    }
  }
  return yes;
}
char pendu_get_user_input(pendu p){
  char input;
  printf("\n");
  pendu_show_word(p);
  printf("You have %d error attempts.\n",p->remaining_errors);
  printf("Please enter a letter\n");
  int ok=0;
  while(ok!=1){
    // get the input
    scanf(" %c",&input);
    printf("\n");
    if(input>='a' && input<='z')
      input -=32;
    //verify if it is not a letter
    if(input<'A' || input>'Z'){
      printf("%c is not a letter please enter a letter:\n",input);
      continue;
    }
    // //make input uppercase
    // // verify that the letter we already chosed it
    if(p->tries[input-'A']==1){
      
      printf("You already chosed the letter %c.Please chose again:\n",input);
      continue;
    }
    //if the letter is newly chosed and is not a special caracter then we can go out from the loop
    ok=1;
  }
  
    if(pendu_letter_exist_in_word(p,input))
      printf("Well done the letter %c exist in the word \n",input);
  // printf("Ok %d",ok);
  return input;
}
void pendu_play_pendu(pendu p){
  //p->remaining_errors>0 && p->remaining_letter>0
  // char flag = 1;
  while(p->remaining_errors>0 && p->remaining_letter>0){
    //function to take the input and to make sure it is letter and it wasnt chosed before
    char input = pendu_get_user_input(p);
    // printf("Letter %c, in the tries: %d",input,p->tries[input-'A']);
    //mark the letter as visite
    p->tries[input-'A']=1;
    // print("pendu_play_pendu: remaining letters %d, word length %d\n",p->remaining_letter,p->len);
    /*
      when i need to take -1 from remaining letter
      when the letter i found the letter in the loop i retrive -1

      when i need to take away from the fehler 
      when the letter is not found it means i take away a fehler

    */
   int i;
   int ok=0;
   char* word = p->word;
   for(i=0;word[i]!='\0';i++){
     char current_letter = word[i];
     if(word[i]==input){
       ok=1;
       p->remaining_letter--;
     }
   }
   if(ok==0){
    p->remaining_errors--;
    printf("The letter %c doesnt exist in the word.\n",input);
    printf("Now you have %d attemps left.\n",p->remaining_errors);
   }

  }
  printf("\n\n");
  if(p->remaining_letter<=0){
    printf("Congratulation you won!!The word is \" %s \".\n",p->word);
    printf("You have %d failling attempts left.",p->remaining_errors);
  }
  if(p->remaining_errors<=0){
    printf("You lost Bro :p\nThe word is \" %s \".\n",p->word);
  }
}

int main(int argc, char** argv){
  char* word;
  int error_len;
  S_pendu p;
  //verifier the input
  if(argc>=2)
    word = argv[1];
  else
    word = "excepti*onnellement.";

  if(argc>=3)
    error_len = atoi(argv[2]);
  else
    error_len=7;

  //put the word in appercase
  word = make_uppercase(word);
  //initialise struct pendu
  pendu_init(&p, word, error_len);
  printf("\nHangman game: You have %d attemps left!!\n",p.remaining_errors);
  // pendu_show_word(&p);
  pendu_play_pendu(&p);
  return EXIT_SUCCESS;
}