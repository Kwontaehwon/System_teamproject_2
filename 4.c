#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#include <stdio.h>
typedef struct INode{

  int val;
  struct INode *next;
  struct INode *prev;
} INode;

typedef struct {
  INode *head;
  int size;
} IDLL;

INode* newINode(int c){
  INode *temp =(INode *)malloc(sizeof(INode));
  temp-> val = c;
  temp-> next = NULL;
  temp-> prev = NULL;
  return temp;
}

IDLL *newIDLL(){
  IDLL *temp = (IDLL *)malloc(sizeof(IDLL));
  temp -> head = NULL;
  return temp;
}

void I_print(IDLL *list){
  INode *curr = list->head;
  while(curr != NULL){
    printf("%d",curr->val);
    curr = curr -> next;
  }
  printf("\n");
}

void I_print_reverse(IDLL *list){
  INode *curr = list->head;
  while(1){
    if(curr->next == NULL) break;
    else curr = curr -> next;
  }
  while(1){
    printf("%d ",curr->val);
    if(curr->prev == NULL) break;
    else curr = curr -> prev;
  }
  
  printf("\n");
}


void I_append(IDLL *list,INode *newINode){
  INode *curr ;
  if(list->head == NULL){
    list->head = newINode;
  }
  else{
    curr = list->head;
    while ( curr ->next != NULL){
      curr = curr->next;
    }
    newINode->prev = curr;
    curr->next = newINode;
  }
  list->size = list->size+1;
}

typedef struct Node{

  char val;
  struct Node *next;
  struct Node *prev;

} Node;

typedef struct {
  int size;
  Node *head;
} DLL;

Node* newnode(char c){

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

void cal(DLL *list_1){
  int status = 1;
  int size_status = 1;
  IDLL *ans = newIDLL();
  DLL *a = newDLL();
  DLL *b = newDLL();
  DLL *c = newDLL();
  Node *curr = list_1 -> head;
  while(1){
    if(curr->next == NULL) break;
    if(status == 1){
      if( isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
        append(a,newnode(curr->val));
        a->size = a->size + 1;
         if ( curr -> next -> val == ' '){
        
        status++;
        }
      }
    }
    else if(status == 2){
      if(isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
        append(b,newnode(curr->val));
        b->size = b->size + 1;
        if ( curr -> next -> val == ' '){
          status++;
        }
      }
    }
    else if(status == 3){
      Node *a_curr = a->head;
      Node *b_curr = b->head;
      INode *ans_curr = ans->head;
      int size,size_a = a->size,size_b= b->size;
      for(int i=0; i<a->size-1;i++){
          a_curr = a_curr->next;
        }
      for(int i=0; i<b->size-1;i++){
            b_curr = b_curr->next;
          }
      if(size_a > size_b){
        size = size_a;
      } 
      else{
        size = size_b;
        size_status = 2;
      }
      // printf("%d",size);
      // printf("%d",size_status);
      for(int i=0; i<size; i++){
        int a,b;
        if (size_status == 1 && i >= size_b){
          a = a_curr->val - '0';
          I_append(ans,newINode(a));
          a_curr = a_curr->prev;
        }
        else if(size_status == 2 && i >= size_a){
          b = b_curr->val - '0';
          I_append(ans,newINode(b));
          b_curr = b_curr->prev;
        }
        else{
          a = a_curr->val - '0';
          b = b_curr->val - '0';
          I_append(ans,newINode(a+b));
          a_curr = a_curr->prev;
          b_curr = b_curr->prev;
        }
      }
      break;
    }
    // else{
    //   if( isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
    //     append(c,newnode(curr->val));
    //     c->size = c->size + 1;
    //      if (curr -> next -> val == ' '){
    //     for(int i=0; i<c->size-1;i++){
    //       c_curr = c_curr->next;
    //     }
    //     status++;
    //     }
    //   }
    // }
    curr = curr -> next;
  }
  I_print(ans);
  I_print_reverse(ans);
}
//int value = curr->val - '0';

void postfix(DLL *list,DLL *list_1){
  DLL *stack = newDLL(); // 연산자 담아둘 스택
  Node *curr = list -> head;
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
    if(cur -> next == NULL){
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
int getnumber(DLL *list){

  while(1){
    char temp = getchar();
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



void print(DLL *list){

  Node *curr = list->head;
  while(curr != NULL){
    printf("%c",curr->val);
    curr = curr -> next;
  }
  printf("\n");
}



int main(){
  DLL *list = newDLL();
  getnumber(list);
  DLL *list_1 = newDLL();
  postfix(list,list_1); //값이 바뀌지는 않을까?
  print(list_1);
  cal(list_1);
}

