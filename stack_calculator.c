#include <stdio.h>
#include <string.h>

#define MAX 100
#define TRUE 1
#define False 0

//operator, operand stack
char OperatorStack[100];
char OperandStack[100];

int OperatorTop;
int OperandTop;
//스택 초기화
void InitializeStack(void);
//연산자,피연산자 pop or push
void OperatorPush(char);
void OperandPush(int);
char OperatorPop(void);
int OperandPop(void);

//빈 스택 확인
int IsEmptyOperatorStack(void);
int IsEmptyOperandStack(void);

//연산자 우선순위 
int GreaterOpr(char, char);
//계산해주는 함수
int Calculate(int, int, char);

void main() {
	char buf[80];
	int len, i;
	int opn1, opn2;
	char opr, c;
	char tmpopr;
	InitializeStack();
	//컴마 뒤에 DLL받아야됨 strcpy(buf,);
	len = strlen(buf);
	i = 0;
	while (i < len) {
		c = buf[i++];
		if (c == ' ')
			continue;
		else if (c <= '9' && c >= '0') // 숫자일 때
			OperandPush(c - '0'); //숫자로 저장
		else if (c == '+' || c == '-' || c == '*' || c == '/') { //연산자일 때
			if (IsEmptyOperatorStack()) // 빈스택이면 푸시
				OperatorPush(c);
			else { // 빈스택 아니면 우선순위 따지고 더 높으면 바로 푸시 아니면 연산자 우선순위 따지고
				opr = OperatorPop();
				if (GreaterOpr(opr, c)) {
					opn2 = OperandPop();
					opn1 = OperandPop();
					opn1 = Calculate(opn1, opn2, opr);
					OperandPush(opn1);
					OperatorPush(c);
				}
				else {
					OperatorPush(opr);
					OperatorPush(c);
				}
			}
		}
		while (!IsEmptyOperatorStack()) {
			opn1 = OperandPop();
			opn2 = OperandPop();
			opr = OperatorPop();
			opn1 = Calculate(opn1, opn2, opr);
			OperandPush(opn1);
		}
		printf("%s = %d \n", buf, OperandPop());
	}
}
void InitializeStack(void) {
	OperatorTop = 0;
	OperandTop = 0;
}

void OperatorPush(char opr) {
	OperatorStack[OperatorTop++] = opr;
}

void OperandPush(int opn) {
	OperandStack[OperandTop++] = opn;
}

char OperatorPop(void) {
	return OperatorStack[--OperatorTop];
}

int OperandPop(void) {
	return OperandStack[--OperandTop];
}

int IsEmptyOperandStack(void) {
	if (OperandTop == 0)
		return TRUE;
	else
		return FALSE;
}

int GreaterOpr(char opr1, char opr2) {
	if (opr1 == '*' || opr1 == '/') {
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else
			return FALSE;
	}
	else // opr1 == '+' 이거나 '-' 일때
		return FALSE;
}
/*이거 구현..............
int Calculate(int opn1, int opn2, char opr) {
	switch (opr) {
	case '+' :
	case '-':
	case '*':
	case '/':
	}
}
*/