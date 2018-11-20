#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Node{

  char val;

  struct Node *next;
  struct Node *prev;

} Node;

typedef struct {

  Node *head;

} DLL;

Node *newnode(char c){

  Node *temp =(Node *)malloc(sizeof(Node));

  temp-> val = c;

  temp-> next = NULL;

  temp-> prev = NULL;

  return temp;

}

DLL *newDLL(){

  DLL *temp = (DLL *)malloc(sizeof(DLL));

  temp -> head = NULL;

  return temp;

}

void append(DLL *list, Node *newnode);
void print(DLL *list);



int main(){
  DLL *list = newDLL();

  while(1){

    char temp = getchar() ;

    if( temp == '\n') break;

    else if ( temp == '.' || temp =='('|| temp ==')' || temp == '+'|| temp == '-'|| temp == '*'|| temp == '/' ){

      append(list,newnode(temp));

    }

    else if ( isblank(temp) );

    else if ( isalpha(temp) ) {

      printf(" Wrong Input ! ");

      return 0;
    }

    else if ( isdigit(temp) ){

      append(list,newnode(temp));

    }

    else {

      printf(" Wrong Input ! ");

      return 0;
    }

  }

  print(list);

}



void append(DLL *list,Node *newnode){

  Node *curr ;

  if(list->head == NULL){

    list->head = newnode;

  }

  else{

    curr = list->head;

    while ( curr ->next != NULL){

      curr = curr->next;

    }

    newnode->prev = curr;

    curr->next = newnode;

  }

}

void print(DLL *list){

  Node *curr = list->head;

  while(curr != NULL){

    printf("%c",curr->val);

    curr = curr -> next;

  }

}
