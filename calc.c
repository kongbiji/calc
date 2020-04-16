#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "function.h"

int main(){
    char exp[100], tmp[100];
    unsigned int idx_stack = 0;
    unsigned int idx_tmp = 0;

    memset(exp,0,100);
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
    exp[index] = 0;
        
    printf("[*] Infix Notation : %s\n", exp);

    infix_to_postfix(exp,tmp,index,idx_stack,idx_tmp);

    printf("[+] Postfix Notation : %s\n", tmp);

    int ret = evalPostfix(tmp);

    printf("[+] answer >> %d\n", ret);
}