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
  return temp;
}

void append(DLL *list, Node *newnode);
void print(DLL *list);
void postfix(DLL *list,DLL *list_1);
void getnumber(DLL *list);
void cal(DLL *list,DLL *stack_3);
void plus(Node *curr_1, Node *curr_2,DLL *stack_3);
void reverse(DLL *list, DLL *list_1);
int GreaterOpr(char opr1, char opr2);
void PushOrPop(DLL *stack, char input_opr, DLL *list_1);
void POP_all(DLL *stack, DLL *list_1);

int main(){
  DLL *list = newDLL(); // 입력을 받을 list
  getnumber(list);
  DLL *list_1 = newDLL();
  postfix(list,list_1); // 후위표기법으로 바뀐 list_1
  print(list_1);
  DLL *list_2 = newDLL();
  printf("\n");
  cal(list_1,list_2); // 계산된 list_2
  DLL *list_3 = newDLL(); // 값의 순서를 바꿀 list_3
  reverse(list_2,list_3);
  print(list_3);
  Node *curr = list_1->head ;
  while(1){
    if ( curr->val == ' ') break;
    else curr = curr->next;
  }
}


void cal(DLL *list,DLL *stack_3){ //reverse
  DLL *stack_1 = newDLL(); // 숫자1
  DLL *stack_2 = newDLL(); // 숫자2
  Node *curr = list -> head ;
  while(1){ // + - 만날?? 까지 노드움직임
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

  while(1){ // +나 - 만날때 까지 노드움직임
    if (curr ->val == '+' || curr->val =='-'){
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
    int a = curr_1 -> val - 48 ;
    int b = curr_2 -> val - 48 ;
    int c ;

    while (1){
      // 수가 끝낫을경우 0으로 처리
      if ( curr_1 != NULL) a = curr_1 -> val - 48 ;
      else a = 0;
      if (curr_2 != NULL) b = curr_2 -> val - 48 ;
      else b = 0;
      c = a+b;
      if ( count == 1){
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
    } // if +문에 걸림
}

void plus(Node *curr_1, Node *curr_2,DLL *stack_3){
  while (1){
    int count = 0;
    int a = curr_1 -> val - 48 ;
    int b = curr_2 -> val - 48 ;
    int c ;
    if(curr_1 -> prev == NULL){ // 앞수가 끝났을 경우
        if (count == 1) { // 넘어노는 수가 있을경우
          b++;
          c = b;
          count = 0 ;
          if ( c >= 10){
            count = 1;
            c = c- 10;
          }
          curr_2 = curr_2 ->prev;
        }
        else{
          c = b;
          if ( c >= 10){
            count = 1;
            c = c-10;
          }
          curr_2 = curr_2 ->prev;
          }
      }
      else if (curr_2-> prev == NULL){ // 뒷수가 끝났을 경우
        if (count == 1) { // 넘어오는 수가 있을경우
          a++;
          c = a;
          count = 0 ;
          if ( c >= 10){
            count = 1;
            c = c- 10;
          }
          curr_1 = curr_1 ->prev;
        }
        else{
          c = a;
          if ( c >= 10){
            count = 1;
            c = c-10;
          }
          curr_1 = curr_1 ->prev;
        }
      }
      else{ // 숫자 아직 남아있음
        if (count == 1){
          c = a + b;
          c++;
          count = 0;
          if ( c >= 10){
            c = c - 10;
            count = 1;
          }
          curr_1 = curr_1 ->prev;
          curr_2 = curr_2 ->prev;
        }
        else{
          c = a + b;
          if ( c >= 10){
            c = c - 10;
            count = 1;
          }
		  curr_1 = curr_1 ->prev;
          curr_2 = curr_2 ->prev;
        }
      }

    c = c + 48;
    append(stack_3,newnode(c));
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

void PushOrPop(DLL *stack, char input_opr, DLL *list_1)
{
	while (1) {
		if (stack->size == 0) {
			append(stack,newnode(input_opr));
			stack->size+=1;
			break;
		}
		else {
			Node *bigyo = stack->head;
			while (bigyo->next != NULL)
				bigyo = bigyo -> next;
			if (GreaterOpr(bigyo->val,input_opr) == FALSE){
				append(stack,newnode(input_opr));
				stack->size+=1;
				break;
			}
			else {
				if (stack->size == 1) {
					POP_all(stack,list_1);
					append(stack,newnode(input_opr));
					stack->size+=1;
					break;
				}
				else if (stack->size >= 2) {
					append(list_1,newnode(bigyo->val));
					bigyo=bigyo->prev;
					bigyo->next = NULL;
					stack->size -= 1;
				}
			}
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
      PushOrPop(stack, curr->val, list_1);
	  curr = curr -> next;
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
