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
void postfix(DLL *list,DLL *list_1);


int main(){
  DLL *list = newDLL();
  getnumber(list);
  DLL *list_1 = newDLL();
  postfix(list,list_1); //값이 바뀌지는 않을까?
  print(list_1);
}


void cal(DLL *list,DLL *answer){

  DLL *stack_1 = newDLL();

  DLL *stack_2 = newDLL();

  Node *curr = list -> head ;

  while(curr->val != ' '){ // 숫자 1
    append(stack_1,newnode( curr-> val ));
    curr = curr -> next;
  }
  curr -> next;
  while (curr -> val != ' ' ){ // 숫자 2
    append(stack_2,newnode(curr->val));
    curr = curr -> next ;
  }
  while (curr -> val != '+' || curr->val != '-'){
  }

}

void getnumber(DLL *list){

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
}

void postfix(DLL *list,DLL *list_1){

  DLL *stack = newDLL(); // 연산자 담아둘 스택

  Node *curr = list -> head ;

  while(1){

    if( curr -> next == NULL){ //마지막숫자 일 경우
      append(list_1,newnode(curr->val));
      append(list_1,newnode(' '));
      break;

    }
    else if( isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음

      append(list_1,newnode(curr->val));

      if ( curr -> next == NULL) break;

      curr = curr -> next;

    }
    else{  // 연산자들

      append(list_1,newnode(' '));

      append(stack,newnode(curr->val));

      curr = curr ->next;
    }
  }
  Node *cur = stack->head;

  while(1){
    if( cur -> next == NULL){

      append(list_1, newnode(cur->val));

      break;

    }
    else{
      append(list_1, newnode(cur->val));

      cur = cur->next;
    }
  }
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
