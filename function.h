#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void infix_to_postfix(char * exp, char * tmp, int index, int idx_stack, int idx_tmp){
    char stack[50];
    for(int i=0; i<index; i++){
        if(exp[i]!='+' && exp[i]!='-' && exp[i]!='/' && exp[i]!='*'){
            tmp[idx_tmp] = exp[i];
            idx_tmp++;
            continue;
        }
        if(idx_stack == 0){
            tmp[idx_tmp] = ',';
            idx_tmp++;
            stack[idx_stack] = exp[i];
            idx_stack++;
            continue;
        }else{
            if((exp[i]=='/' || exp[i]=='*') && (stack[idx_stack-1]=='+' || stack[idx_stack-1]=='-')){
                tmp[idx_tmp] = ',';
                idx_tmp++;
                stack[idx_stack] = exp[i];
                idx_stack++;
            }else{
                tmp[idx_tmp] = stack[idx_stack-1];
                idx_tmp++;
                stack[idx_stack-1] = 0;
                stack[idx_stack-1] = exp[i];
            }
        }
    }

    idx_tmp = strlen(tmp)-1;
    if(idx_stack != 0){
        int i = idx_stack-1;
        while(i >= 0){
            tmp[idx_tmp] = stack[i];
            i--;
            idx_tmp++;
        }
    }
}

void pop_stack(int *stack, int * idx_stack, int * a, int *b){
    *a = stack[*idx_stack-2];
    *b = stack[*idx_stack-1];
    stack[*idx_stack-2] = 0;
    stack[*idx_stack-1] = 0;
    *idx_stack -= 2;
}

int evalPostfix(char * exp){
    int stack[100] = {0,};
    int a, b = 0;
    int idx, idx_stack = 0;
    int ret = 0;
    char tmp[10];
    char num[10];
    memset(tmp,0,10);
    memset(num,0,10);

    int calc_num = 0;

    for(int i=0; i<strlen(exp); i++){
        if(exp[i]==','){
            strncpy(num,tmp,idx);
            stack[idx_stack] = atoi(num);
            idx_stack++;
            memset(tmp,0,10);
            memset(num,0,10);
            idx=0;
            continue;
        }
        if(exp[i]=='+'){
            if((exp[i-1]!='+' && exp[i-1]!='-' && exp[i-1]!='/' && exp[i-1]!='*')){
                strncpy(num,tmp,idx);
                stack[idx_stack] = atoi(num);
                idx_stack++;
                memset(tmp,0,10);
                memset(num,0,10);
                idx=0;
            }
            pop_stack(stack, &idx_stack, &a, &b);
            stack[idx_stack] = a + b;
            calc_num++;
            printf("%d: %d + %d = %d\n", calc_num, a, b, a+b); // 중간 계산값 출력
            idx_stack++;
            continue;
        }
        if(exp[i]=='-'){
            if((exp[i-1]!='+' && exp[i-1]!='-' && exp[i-1]!='/' && exp[i-1]!='*')){
                strncpy(num,tmp,idx);
                stack[idx_stack] = atoi(num);
                idx_stack++;
                memset(tmp,0,10);
                memset(num,0,10);
                idx=0;
            }
            pop_stack(stack, &idx_stack, &a, &b);
            stack[idx_stack] = a - b;    
            calc_num++;
            printf("%d: %d - %d = %d\n", calc_num, a, b, a-b); // 중간 계산값 출력
            idx_stack++;
            continue;        
        }
        if(exp[i]=='/'){
            if((exp[i-1]!='+' && exp[i-1]!='-' && exp[i-1]!='/' && exp[i-1]!='*')){
                strncpy(num,tmp,idx);
                stack[idx_stack] = atoi(num);
                idx_stack++;
                memset(tmp,0,10);
                memset(num,0,10);
                idx=0;
            }
            pop_stack(stack, &idx_stack, &a, &b);
            stack[idx_stack] = a / b;
            calc_num++;
            printf("%d: %d / %d = %d\n", calc_num, a, b, a/b); // 중간 계산값 출력
            idx_stack++;
            continue;          
        }
        if(exp[i]=='*'){
            if((exp[i-1]!='+' && exp[i-1]!='-' && exp[i-1]!='/' && exp[i-1]!='*')){
                strncpy(num,tmp,idx);
                stack[idx_stack] = atoi(num);
                idx_stack++;
                memset(tmp,0,10);
                memset(num,0,10);
                idx=0;
            }
            pop_stack(stack, &idx_stack, &a, &b);
            stack[idx_stack] = a * b;   
            calc_num++;
            printf("%d: %d * %d = %d\n", calc_num, a, b, a*b); // 중간 계산값 출력
            idx_stack++;
            continue;        
        }
        tmp[idx] = exp[i];
        idx++;
    }

    ret = stack[0];

    return ret;
}
