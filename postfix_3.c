#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct Node{
  char val;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  int size;
  int size_1; //소수점 자리수 저장
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
  temp -> size = 0;
  temp -> size_1 = 0;
  return temp;
}

void append(DLL *list, Node *newnode);
void print(DLL *list);
void postfix(DLL *list,DLL *list_1);
void getnumber(DLL *list);
void cal(DLL *list,DLL *stack_3);
void reverse(DLL *list, DLL *list_1);
int GreaterOpr(char opr1, char opr2);
void POP_part(DLL *stack, DLL *list_1);
void POP_all(DLL *stack, DLL *list_1);
void insert(DLL *list_1,DLL *list_3);
void dec(DLL *stack_1, DLL *stack_2 ); // 소수점의 자릿수를 맞춰주는 함수
void insertAt(DLL *stack_3, int index, Node *newnode); // 소수점 삽입을 위한 함수
void copy_1(DLL *list_1 , DLL *list_3);
void free_1(DLL *list_1);

int main(){
  DLL *list = newDLL(); // 입력을 받을 list
  getnumber(list); // 입력을 받아오는 함수
  printf("\n");
  DLL *list_1 = newDLL(); //후위표기법으로 바뀐값을 넣어줄 list_1
  postfix(list,list_1);  // 후위표기법으로 바뀐 list_1
  print(list_1);
  DLL *list_2 = newDLL(); // 계산할 값을 넣어줄 list_2
  printf("\n");
  cal(list_1,list_2);  // 계산된 list_2
  DLL *list_3 = newDLL();
  reverse(list_2,list_3);
  print(list_3);


  /*
  printf("\n");
  insert(list_1,list_3); //list _3 에 저장
  list_1 -> head = NULL;
  list_1 -> head = list_3->head; //copy함수 사용
  list_3 -> head = NULL;
  list_2 -> head = NULL;
  print(list_1);
  //// 두번쨰 계산
  printf("\nsecond\n");
  cal(list_1,list_2); // cal이문제임
  printf("\ncal play\n");
  reverse(list_2,list_3);
  print(list_2);
  */





}

void free_1(DLL *list_1){
  Node *curr = list_1 ->head;
  while(1){
    if (curr ->next == NULL){
      free(curr);
      break;
    }
    else{
      free(curr);
      curr = curr->next;
    }
  }
}

void copy_1(DLL *list_1 , DLL *list_3){ //아예 비워진 list_1 에 list_3에 값을 넣어줘야됌
  Node *curr = list_3 -> head;
  while(1){
    if (curr ->next == NULL){
      append(list_1,newnode(curr->val));
      break;
    }
    else{
      append(list_1,newnode(curr->val));
      curr = curr -> next;
    }
  }
}

void dec(DLL *stack_1, DLL *stack_2 ){ // 소수점의 자릿수를 맞춰줌.
  Node *curr = stack_1 ->head;
  Node *curr_1 = stack_2 ->head;
  int a = 0 ;
  int b = 0 ;
  while(1){
    if(curr -> val == '.' || curr -> next == NULL) break;
    else curr = curr -> next;
  }
  while(1){
    if (curr->next == NULL) break;
    else {
      a++;
      curr = curr -> next ;
    }
  }
  while(1){
    if(curr_1 -> val == '.' || curr_1->next == NULL ) break;
    else curr_1 = curr_1 -> next;
  }
  while(1){
    if (curr_1->next == NULL) break;
    else {
      b++;
      curr_1 = curr_1->next ;
    }
  }
  //////////////////
  //printf("\na : %d b : %d\n",a,b);
  //////////////////
  if( a > b){
    int c =  a-b;
    for ( int i = 0 ; i < c ; i++){
      append(stack_2,newnode('0'));
    }
    stack_1 -> size_1 = a;
    stack_2 -> size_1 = a;
  }
  else if ( b > a){
    int c = a - b;
    for (int i = 0 ; i < c; i++ ){
      append(stack_1,newnode('0'));
    }
    stack_1 -> size_1 = b;
    stack_2 -> size_1 = b;
  }
  else {
    stack_1 -> size_1 = a;
    stack_1 -> size_1 = b;
  }

}

void insert(DLL *list_1,DLL *list_3){ // 계산된 DLL을 원래 있던 후위표기법 식이랑 합쳐줌
  append(list_3,newnode(' '));
  Node *curr = list_1->head ;
  Node *curr_1 = list_3->head ;

  while(1){ //지울 연산자의 다음 포인터
    if ( curr -> val == '+' || curr ->val == '-' || curr->val == '*') {
      curr = curr->next;
      break;
    }
    else {
      curr = curr->next;
    }
  }
  while(1){
    if(curr_1 ->next  == NULL) break;
    else curr_1 = curr_1 ->next;
  }
  curr_1 -> next = curr;
}

void cal(DLL *list,DLL *stack_3){ //reverse
  DLL *stack_1 = newDLL(); // 숫자1
  DLL *stack_2 = newDLL(); // 숫자2
  Node *curr = list -> head ;
  while(1){ // + - 만날때 까지 노드움직임
    if( curr->val == '+' || curr->val == '-'){
      curr = curr->prev;
      curr = curr->prev;
      break;
    }
    else{
      curr = curr->next;
    }
  }
  while(1){ //첫번째 인자수 맨앞 빈칸
    if( curr->prev == NULL || curr->val == ' '){
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  curr = curr->next;
  while(1){ //첫번째 수 저장
    if( curr->val == ' ' ){
      curr = curr->prev;
      break;
    }
    else{
      append(stack_2,newnode(curr->val));
      curr = curr->next;
    }
  }
  while(1){ //첫번째 수 넘어감
    if( curr -> val == ' ' || curr->prev == NULL){
      curr = curr->prev;
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  while(1){ //두번째수 앞 빈칸까지
    if( curr->val == ' ' || curr->prev == NULL){
      break;
    }
    else{
      curr = curr->prev;
    }
  }
  while(1){ //두번째 수 저장
    if( curr->val == ' ' ){
      break;
    }
    else{
      append(stack_1,newnode(curr->val));
      curr = curr->next;
    }
  }

  dec(stack_1,stack_2);

  printf("\nstack\n");
  print(stack_1);
  printf("\n");
  print(stack_2);
  printf("\n");

  while(1){ // +나 - 만날때 까지 노드움직임
    if (curr ->val == '+' || curr->val =='-' || curr->val == '*'){
      break;
    }
    else{
      curr = curr->next;
    }
  }

  if( curr ->val == '+' ){
    Node *curr_1 = stack_1 ->head;
    Node *curr_2 = stack_2 ->head;
    while(1){ // 노드 끝까지 보냄
      if (curr_1->next == NULL) break;
      else curr_1 = curr_1 ->next;
    }
    while(1){ // 노드 끝까지 보냄
      if (curr_2->next == NULL) break;
      else curr_2 = curr_2 ->next;
    }

    int count = 0 ;
    int a  = curr_1 -> val - 48 ;
    int b  = curr_2 -> val - 48 ;
    int c ;

    while (1){ // + 계산시작
      // 수가 끝낫을경우 0으로 처리

      if ( curr_1 ->val == '.') {
        curr_1 = curr_1 -> prev;
      }
      if ( curr_2 -> val == '.') {
        curr_2 = curr_2 -> prev;
      }

      ////////////
      printf("\na : %d b : %d\n",a,b);
      ////////////

      if ( curr_1 != NULL) a = curr_1 -> val - 48 ;
      else a = 0;
      if ( curr_2 != NULL) b = curr_2 -> val - 48 ;
      else b = 0;

      c = a+b;

      if (count == 1){
        c++;
        count = 0 ;
        if ( c >= 10){
          c = c-10;
          count = 1;
        }
      }
      else {
        if ( c >= 10 ){
          c = c - 10;
          count = 1;
        }
      }

      if ( curr_1 != NULL) curr_1 = curr_1 ->prev;
      if ( curr_2 != NULL) curr_2 = curr_2 ->prev;
      ////////////////
      //if ( curr_1 == NULL) printf("\ncurr_1 NULL\n");
      //if ( curr_2 == NULL) printf("\ncurr_2 NULL\n");
      ////////////////

      //////////////
      printf("\ninsert value : %d \n",c);
      ///////////
      c = c + 48;
      append(stack_3,newnode(c));
      if ( curr_1 == NULL && curr_2 == NULL){
        if ( count == 1){ // 수를 더해서 자리수가 올라갈경우
          append(stack_3,newnode('1'));
          count = 0 ;
          }
         break;
        }
      } // while문

      int d = stack_1 ->size_1;
      printf("\nd : %d\n",d);
      if ( d > 0) insertAt(stack_3,d,newnode('.'));

    } // if +문에 걸림
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
      break;
    }
    else if ( isdigit(temp) ){
      append(list,newnode(temp));
    }
    else {
      printf(" Wrong Input ! ");
      break;
    }
  }
}

int GreaterOpr(char opr1, char opr2)
{
	if(opr1 == '*') {
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else if (opr2 == '*')
			return TRUE;

	}
	else if (opr1 == '+' || opr1 == '-'){
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else if(opr2 == '*')
			return FALSE;
	}
}

void POP_all(DLL *stack,DLL *list_1)
{
  Node *cur = stack->head;
  while(cur->next != NULL){
		cur = cur->next;
	}
  while(1){
    if( cur -> prev == NULL){
      append(list_1, newnode(cur->val));
      break;
    }
    else{
      append(list_1, newnode(cur->val));
      cur = cur->prev;
    }
  }
  free(stack);
  stack = newDLL();
}

void POP_part(DLL *stack, DLL *list_1)
{
	Node *cur = stack->head;
	while(cur->next != NULL) {
		cur = cur -> next;
	}
	append(list_1, newnode(cur->val));
	Node *prev = cur->prev;
	free(cur);
	prev->next= NULL;
	stack->size -= 1;
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
      if (stack -> size == 0){
		  append(stack,newnode(curr->val));
		  stack -> size += 1;
		  curr = curr->next;
	  }
	  else{
		  Node *head = stack->head;
		  while (head -> next != NULL)
			  head = head -> next;
		  if (GreaterOpr(stack->head->val,curr->val)){
		  	POP_all(stack,list_1);
			append(stack,newnode(curr->val));
			stack->size += 1;
			curr = curr->next;
		  }
		  else {
			  append(stack,newnode(curr->val));
			  stack->size += 1;
			  curr = curr->next;
		  }

	  }
    }
  }

  POP_all(stack,list_1);
}

void reverse(DLL *list, DLL *list_1){ //
  Node *curr = list->head;
  while(1){ // 노드를 끝까지 보냄
    if ( curr -> next == NULL) break;
    else curr = curr -> next;
  }
  while(1){
    if( curr -> prev == NULL){
       append(list_1,newnode(curr->val));
       break;
    }
    else {
      append(list_1,newnode(curr->val));
      curr = curr -> prev;
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

void print(DLL *list) {
	Node *curr = list->head;
	while (curr != NULL) {
		printf("%c",curr->val);
		curr = curr->next;
	}
}

void insertAt(DLL *stack_3, int index, Node *newnode){ // 소수점 삽입을 위한 함수
  
	Node *curr = stack_3->head;

  while(1){
    if(curr->next == NULL) break;
    else curr = curr->next;
  }
  for (int i = 0 ; i < index ; i++){
    curr = curr->prev;
  }
	newnode->prev = curr;
	newnode->next = curr->next ;
  curr->next->prev = newnode;
	curr->next = newnode;
}
