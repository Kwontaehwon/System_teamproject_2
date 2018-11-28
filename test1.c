#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

// int DLL,node
// int node

typedef struct Inode{

  int val;
  struct Inode *next;
  struct Inode *prev;
} Inode;

typedef struct {
  Inode *head;
  int size;
} IDLL;

Inode* newInode(int c){
  Inode *temp =(Inode *)malloc(sizeof(Inode));
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
  Inode *curr = list->head;
  while(curr != NULL){
    printf("%d",curr->val);
    curr = curr -> next;
  }
  printf("\n");
}
void I_append(IDLL *list,Inode *newInode){
  Inode *curr ;
  if(list->head == NULL){
    list->head = newInode;
  }
  else{
    curr = list->head;
    while ( curr ->next != NULL){
      curr = curr->next;
    }
    newInode->prev = curr;
    curr->next = newInode;
  }
  list->size = list->size+1;
}


// int dll node end

typedef struct Node{

  char val;
  struct Node *next;
  struct Node *prev;

} Node;

typedef struct {
  Node *head;
} DLL;

Node* newnode(char c){

  Node *temp =(Node *)malloc(sizeof(Node));
  temp-> val = c;
  temp-> next = NULL;
  temp-> prev = NULL;
  return temp;
}

Node* newnode_int(int c){

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
  DLL *ans = newDLL();
  DLL *a = newDLL();
  IDLL *b = newIDLL();
  Node *curr = list_1 -> head;
  while(1){
    if(curr->next == NULL) break;
    if(status == 1){
      if( isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
        append(a,newnode(curr->val));
         if ( curr -> next -> val == ' '){
        status++;
        }
      }
    }
    else if(status == 2){
      if(isdigit(curr->val) || curr->val == '.' ){ // 숫자나 .이나오면 그냥 다 때려박음
        append(b,newnode(curr->val));
        if ( curr -> next -> val == ' '){
        status++;
        }
      }
    }
    else if(status == 3){
      Node *a_curr = a->head;
      Node *b_curr = b->head;
      Inode *ans_curr = ans->head;
      int a,b;
      a = a_curr->val - '0';
      b = b_curr->val - '0';
      printf("%d%d\n",a,b);
      I_append(ans,a+b);
      // a_curr = a_curr->next;
      // b_curr = b_curr->next;
      print_int(ans);
    }
    curr = curr -> next;
  }
  print(a);
  print(b);
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

void print_int(DLL *list){

  Node *curr = list->head;
  while(curr != NULL){
    printf("%d",curr->val);
    curr = curr -> next;
  }
  printf("\n");
}



int main(){
  DLL *list = newDLL();
typedef struct Node{

  int val;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  int size;
} DLL;

Node* newnode(int c){
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

void print(DLL *list){
  Node *curr = list->head;
  while(curr != NULL){
    printf("%d",curr->val);
    curr = curr -> next;
  }
  printf("\n");
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
  list->size = list->size+1;
}

int main(){
  int stack;
  DLL *test = newDLL();
  append(test,newnode(1));
  append(test,newnode(2));
  append(test,newnode(5));
  Node *curr = test->head;
  while(1){
    stack = stack + curr->val;
    if(curr ->next != NULL){
      curr = curr -> next;
    }
    else break;
  }
  printf("%d",stack);
  print(test);
}


  getnumber(list);
  DLL *list_1 = newDLL();
  postfix(list,list_1); //값이 바뀌지는 않을까?
  print(list_1);
  cal(list_1);
}






























