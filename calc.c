#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "function.h"

int main(){
    char exp[100], tmp[100]; // 입력받은 수식 exp, 후위표기법으로 변환한 수식 tmp
    unsigned int idx_stack = 0; // stack 인덱스
    unsigned int idx_tmp = 0; // 후위표기법 변환 시 사용할 인덱스

    memset(exp,0,100); // 변수 초기화
    memset(tmp,0,100);

    printf(">> Input : ");
    fgets(exp, 100, stdin); // 공백 입력 가능

    int index = 0;
    for(int i = 0; exp[i] < 100; i++){ // 공백 제거
        if(exp[i] != ' '){
            exp[index] = exp[i];
            index++;
        }
    }
    exp[index] = 0; // 수식 마지막 NULL 문자 추가 - 문자열의 끝
        
    printf("[*] Infix Notation : %s\n", exp); // 공백 없앤 중위 표기법 형식 출력
 
    infix_to_postfix(exp,tmp,index,idx_stack,idx_tmp); // 중위 표기법 -> 후위 표기법 변환

    printf("[+] Postfix Notation : %s\n", tmp); // 후위 표기법 출력

    int ret = evalPostfix(tmp); // 후위 표기법으로 수식 연산

    printf("[+] answer >> %d\n", ret); // 연산 결과 출력
}
