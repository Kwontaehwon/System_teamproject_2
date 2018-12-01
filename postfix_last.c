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
  int size_2; //자연수 자리수 저장
  //int size_3; // delete_all 함수쓸때 쓰는 함수
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
  temp -> head = NULL ;
  temp -> size = 0 ;
  temp -> size_1 = 0 ;
  temp -> size_2 = 0 ;
  return temp;
}

void append(DLL *list, Node *newnode);
void print(DLL *list);
void postfix(DLL *list,DLL *list_1);
void getnumber(DLL *list);
void cal(DLL *list,DLL *stack_3);
void reverse(DLL *list, DLL *list_1);

int GreaterOpr(char opr1, char opr2);
void POP_all(DLL *stack, DLL *list_1);
void PushOrPop(DLL *stack, char input_opr, DLL *list_1);

void insert(DLL *list_1,DLL *list_3);
void zero(DLL *stack_1, DLL *stack_2 ); // 소수점의 자릿수를 맞춰주는 함수
void insertAt(DLL *stack_3, int index, Node *newnode); // 소수점 삽입을 위한 함수
int insertAt_int(DLL *stack_3, int index, Node *newnode); // 자연수 부분에 0을 삽입하기 위한 함수
void copy_1(DLL *list_1 , DLL *list_3);

int deleteAt(DLL *list, int index);
void delete_all(DLL *list1);

void DEL_DLL(DLL *list_1);

int main(){
  DLL *list = newDLL(); // 입력을 받을 list
  getnumber(list); // 입력을 받아오는 함수
  printf("\n");
  DLL *list_1 = newDLL(); //후위표기법으로 바뀐값을 넣어줄 list_1
  postfix(list,list_1);  // 후위표기법으로 바뀐 list_1
  print(list_1);

  
  DLL *list_2 = newDLL(); // 계산할 값을 넣어줄 list_2
  printf("\n");
  DLL *list_3 = newDLL();
  DLL *list_4 = newDLL();
  cal(list_1,list_2);  // 계산된 list_2
  reverse(list_2,list_3);
  printf("\nanswer\n");
  delete_all(list_1);
  print(list_3);
  
  /*
  copy_1(list_1,list_3);
  printf("\nlist_1\n");
  print(list_1);
  */


  /*
  insert(list_1,list_3);
  printf("\ncombine\n");
  print(list_3);
  */
  /*
  free_1(list_1);
  free_1(list_2);
  copy_1(list_1,list_3);
  free_1(list_3);
  printf("\nanswer\n");
  print(list_1);
  */

  //// 두번쨰 계산
  /*
  printf("\nsecond\n");
  cal(list_1,list_2); // cal이문제임
  printf("\ncal play\n");
  reverse(list_2,list_3);
  print(list_2);
  */




}

void delete_all(DLL *list1){
  int a = list1->size;
  for(int i=0; i<a;i++)
    deleteAt(list1,0);
}

void copy_1(DLL *list_1 , DLL *list_3){ // list_1 에 list_3에 값을 복사해줌.
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

void zero(DLL *stack_1, DLL *stack_2 ){ // 소수점과 자연수의 자릿수를 맞춰줌.
  Node *curr = stack_1 ->head;
  Node *curr_1 = stack_2 ->head;
  DLL *stack_3 = newDLL(); // 임시로 값을 저장해둘 DLL ,무조건 stack_1이 큰수 이게
  int a = 0 ; // 소수점 자릿수 저장
  int b = 0 ; // 소수점 자릿수 저장
  int c = 0 ; // 자연수 자릿수 저장
  int d = 0 ; // 자연수 자릿수 저장
  while(1){
    if(curr -> val == '.') break;
    else if ( curr -> next == NULL) {
      c++;
      break;
    }
    else{
      c++; // 자연수 자릿수
      curr = curr -> next;
    }
  }
  while(1){
    if (curr->next == NULL) break;
    else {
      a++;
      curr = curr -> next ;
    }
  }
  while(1){
    if(curr_1 -> val == '.') break;
    else if (curr_1 ->next ==NULL){
      d++;
      break;
    }
    else{
      d++; // 자연수 자릿수
      curr_1 = curr_1 -> next;
    }
  }
  while(1){
    if (curr_1->next == NULL) break;
    else {
      b++; //소수점 자릿수
      curr_1 = curr_1->next ;
    }
  }
  //////////////////
  printf("\na : %d b : %d\n",a,b);
  printf("\nc : %d d : %d\n",c,d);
  //////////////////
  stack_1 -> size_2 = c; // 자연수 자릿수 저장
  stack_2 -> size_2 = d;
  if ( a == 0 && b != 0) {
    append(stack_1,newnode('.'));
  }
  if ( b == 0 && a != 0 ) append(stack_2,newnode('.'));
  if ( c > d ){ // 앞수의 자연수 자리가 더 큰경우
    int f = c-d ; //0을 몇개를 넣을 것인가?
    //printf("\nf : %d\n",f);
    for (int i = 0 ; i < f ; i++){
      insertAt_int(stack_2,0,newnode('0'));
    }
    //stack_1 -> size_2 = c;
    //stack_2 -> size_2 = d;
  }
  else if ( d > c ) { //뒷수의 자연수 자리가 더 큰 경우
    int f = d - c;
    //stack_1 -> size_2 = c;
    //stack_2 -> size_2 = d;
    for (int i = 0 ; i < f ; i++ ){
      insertAt_int(stack_1,0,newnode('0'));
    }
    //stack_1 -> size_2 = c;
    //stack_2 -> size_2 = d;
  }
  else{
    //stack_1 -> size_2 = c;
    //stack_2 -> size_2 = d;
  }

  if( a > b){
    int c =  a-b;
    for ( int i = 0 ; i < c ; i++){
      append(stack_2,newnode('0'));
    }
    stack_1 -> size_1 = a;
    stack_2 -> size_1 = a;
  }
  else if ( b > a){
    int c = b - a;
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

  if ( c < d){ // 뒷수가 더 큰수 일때
    printf("\nthis play1\n");
    copy_1(stack_3,stack_1);
    delete_all(stack_1);
    copy_1(stack_1,stack_2);
    delete_all(stack_2);
    copy_1(stack_2,stack_3);
    delete_all(stack_3);
  }
  else if ( c == d){
    int m = stack_1 -> head -> val -48;
    int n = stack_2 -> head -> val -48;
    if( n > m ){
      printf("\nthis play2\n");
      copy_1(stack_3,stack_1);
      delete_all(stack_1);
      copy_1(stack_1,stack_2);
      delete_all(stack_2);
      copy_1(stack_2,stack_3);
      delete_all(stack_3);
    }
  }
}

void insert(DLL *list_1,DLL *list_3){ // 계산된 DLL에 원래 있던 후위표기법 식이랑 합침
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

  zero(stack_1,stack_2);

  printf("\nstack\n");
  print(stack_1);
  printf("\n");
  print(stack_2);
  printf("\n");
  printf("\nint number\n");
  printf("c : %d d : %d\n",stack_1->size_2,stack_2->size_2); //


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
    //////////////////
    //printf("\nplus a : %c b : %c\n",curr_1->val,curr_2->val);
    //////////////////
    int count = 0 ; //올림을 할때 쓰기위함
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

      a = curr_1 -> val - 48 ;
      b = curr_2 -> val - 48 ;
      ////////////
      //printf("\nplus a : %d b : %d\n",a,b);
      ////////////
      /* 모든 자릿수를 0으로 대체해줘서 해줄 필요는 없을듯
      if ( curr_1 != NULL) a = curr_1 -> val - 48 ;
      else a = 0;
      if ( curr_2 != NULL) b = curr_2 -> val - 48 ;
      else b = 0;
      */

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
      //printf("\ninsert value : %d \n",c);
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
      //printf("\nd : %d\n",d);
      if ( d > 0) insertAt(stack_3,d,newnode('.'));
    } // if +문에 걸림

    /*
    마이너스
    */
else if( curr ->val == '-' ){
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
   while(1){
     if ( curr_1 ->val == '.') {
       curr_1 = curr_1 -> prev;
     }
     if ( curr_2 -> val == '.') {
       curr_2 = curr_2 -> prev;
     }
     a = curr_1 -> val - 48 ;
     b = curr_2 -> val - 48 ;
     c = a-b;
     if (count == 1){
       c--;
       count = 0;
     }
     if (c< 0){
       c = c+10;
       count = 1;
     }
     if ( curr_1 != NULL) curr_1 = curr_1 ->prev;
     if ( curr_2 != NULL) curr_2 = curr_2 ->prev;
     c = c + 48;
     append(stack_3,newnode(c));
     if ( curr_1 == NULL && curr_2 == NULL){
         break;
        }
     }
   int d = stack_1 ->size_1;
     //printf("\nd : %d\n",d);
     if ( d > 0) insertAt(stack_3,d,newnode('.'));
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

int GreaterOpr(char opr1, char opr2) // 연산자의 우선순위를 결정하는 함수
{
	if(opr1 == '*') {
		if (opr2 == '+' || opr2 == '-' || opr2 == ')' )
			return TRUE;
		else if (opr2 == '*')
			return TRUE;
		else if (opr2 == '(')
			return FALSE;

	}
	else if (opr1 == '+' || opr1 == '-'){
		if (opr2 == '+' || opr2 == '-'|| opr2 == ')')
			return TRUE;
		else if(opr2 == '*'||opr2 == '(')
			return FALSE;
	}
	else if (opr1 == '(') {
		if (opr2 == ')')
			return TRUE;
		else
			return FALSE;
	}
	else if (opr1 == ')')
		return TRUE;
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
		int ssize = stack->size;
		if (ssize == 0) {
			append(stack,newnode(input_opr));
			ssize+=1;
			break;
		}
		else {
			Node *bigyo = stack->head;
			while (bigyo->next != NULL)
				bigyo = bigyo -> next;
			if (GreaterOpr(bigyo->val,input_opr) == FALSE){
				append(stack,newnode(input_opr));
				ssize+=1;
				break;
			}
			else {
				if (ssize == 1) {
					POP_all(stack,list_1);
					append(stack,newnode(input_opr));
					ssize+=1;
					break;
				}
				else if (ssize >= 2) {
					append(list_1,newnode(bigyo->val));
					bigyo=bigyo->prev;
					bigyo->next = NULL;
					ssize -= 1;
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
    while (curr ->next != NULL){
      curr = curr->next;
    }
    newnode->prev = curr;
    curr->next = newnode;
  }
  list->size = list->size + 1;
}

void print(DLL *list) {
	Node *curr = list->head;
	while (curr != NULL) {
		printf("%c",curr->val);
		curr = curr->next;
	}
}

int insertAt_int(DLL *list, int index, Node *newnode){
	int count = 0;
	Node *curr = list->head;
	if( index == 0 ){
		list->head = newnode;
		curr->prev = newnode;
		list->head->next = curr;
		return 0;
	}
	while(count != index){
		count++;
		curr = curr->next;
		if ( curr->next == NULL) break;
	}
	if(curr->next == NULL){
			newnode->prev = curr;
			curr->next = newnode;
			return 0;
	}
	newnode->prev = curr->prev;
	newnode->next = curr;
	curr->prev->next = newnode;
	curr->prev = newnode;
}

void insertAt(DLL *stack_3, int index, Node *newnode){ // 소수점 삽입을 위한 함수
	Node *curr = stack_3->head;
  int count = 0 ;
  while(1){
    if(curr->next == NULL) {
      count++;
      break;
    }
    else {
      curr = curr->next;
      count ++;
    }
  }
  index = count - index;
  for (int i = 0 ; i < index ; i++){
    curr = curr->prev;
  }
	newnode->prev = curr;
	newnode->next = curr->next ;
  curr->next->prev = newnode;
	curr->next = newnode;
}

int deleteAt(DLL *list, int index){
   Node *curr = list->head;
   int count = 0;
   if(list->size >1){
   if (index == 0){
      list->head->next->prev = NULL;
      list ->head = list->head->next;
      list -> size = list -> size - 1;
      return 0;
   }
   while(count != index){
      count++;
      curr = curr->next;
      if(curr == NULL ) {
         printf("DELETE ERROR: Out of Bound.\n");
         return 0;
      }
   }
   if(count == index){
      if(curr->next == NULL){
         curr->prev->next = NULL;
         list -> size = list -> size - 1;
         return 0;
      }
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      list -> size = list -> size - 1;
   }
 }
 else{
  list->size = list-> size - 1;
  list->head->prev = NULL;
  list->head->next = NULL;
  list->head = NULL;
  }
}

void DEL_DLL(DLL *list_1) {
/*	Node *head = stack->head;
	while (head != NULL) {
		if (head -> val == '(' || head -> val == ')')
		{
			Node *prev = head -> prev;
			Node *next = head -> next;
		}
		head = head-> next;
	}*/
}
