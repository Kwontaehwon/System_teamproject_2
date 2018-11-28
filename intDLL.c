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

int main(){
	int stack;
	IDLL *test = newIDLL();
	I_append(test,newINode(1));
	I_append(test,newINode(2));
	I_append(test,newINode(5));
	INode *curr = test->head;
	while(1){
    stack = stack + curr->val;
		if(curr ->next != NULL){
			curr = curr -> next;
    }
		else break;
	}
	printf("%d",stack);
	I_print(test);
}

