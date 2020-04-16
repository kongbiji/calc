#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 중위 표기법 -> 후위 표기법 변환 함수
void infix_to_postfix(char * exp, char * tmp, int index, int idx_stack, int idx_tmp){
    char stack[50]; // 연산자 저장용 스택
    for(int i=0; i<index; i++){ // 입력받은 수식 exp 처음부터 끝까지 검사
        if(exp[i]!='+' && exp[i]!='-' && exp[i]!='/' && exp[i]!='*'){ // 연산자가 아닐 경우 = 숫자인 경우
            tmp[idx_tmp] = exp[i]; // tmp 배열에 하나씩 저장한다.
            idx_tmp++; // tmp 배열의 인덱스를 한칸 늘린다
            continue; // 밑을 실행하지 않고 바로 i++로 건너뛴다
        }
        if(idx_stack == 0){ // 만약 연산자가 나왔는데, 스택이 비어있는 경우
            tmp[idx_tmp] = ','; // 지금까지 저장한 숫자를 구분하기 위해 구분자 , 추가
            idx_tmp++; // tmp 배열의 인덱스를 한칸 늘린다
            stack[idx_stack] = exp[i]; // 스택에 연산자를 push
            idx_stack++; // 스택 인덱스 증가
            continue;
        }else{
            // 현재 보고있는 연산자가 스택에 들어있는 연산자보다 우선순위가 높은 경우에는
            // 현재 보고있는 연산자를 그냥 스택에 push
            if((exp[i]=='/' || exp[i]=='*') && (stack[idx_stack-1]=='+' || stack[idx_stack-1]=='-')){
                tmp[idx_tmp] = ',';
                idx_tmp++;
                stack[idx_stack] = exp[i];
                idx_stack++;
            }else{ // 만약 현재 보고있는 연산자가 스택에 들어있는 연산자보다 우선순위가 낮거나 같은 경우에는
                // 스택에 있던 연산자를 꺼내서(pop) tmp 배열(후위 표기법으로 작성중인 배열)에 넣고, 현재 연산자를 스택에 push
                tmp[idx_tmp] = stack[idx_stack-1];
                idx_tmp++;
                stack[idx_stack-1] = 0;
                stack[idx_stack-1] = exp[i]; // 해당 부분이 현재 연산자를 스택에 push 하는 부분
            }
        }
    }

    idx_tmp = strlen(tmp)-1; // 처음 제공된 수식이 끝난 경우에는, 
    // 스택에 들어있는 연산자를 차례대로 pop 해서 tmp 배열에 추가하여 후위 표기법을 완성한다
    if(idx_stack != 0){
        int i = idx_stack-1;
        while(i >= 0){
            tmp[idx_tmp] = stack[i];
            i--;
            idx_tmp++;
        }
    }
}

// 후위 표기법 수식 연산 할 때, 연산자를 만나면 스택에 들어있던 피연산자를 두개 꺼내서 값을 계산할 수 있도록 스택을 정리한다.
void pop_stack(int *stack, int * idx_stack, int * a, int *b){
    *a = stack[*idx_stack-2];
    *b = stack[*idx_stack-1];
    stack[*idx_stack-2] = 0;
    stack[*idx_stack-1] = 0;
    *idx_stack -= 2;
}

int evalPostfix(char * exp){ // 후위 표기법 수식 연산 함수
    int stack[100] = {0,}; // 이번엔 피연산자를 저장할 스택
    int a, b = 0; // 계산에 사용하기 위해 임시 변수 마련
    int idx, idx_stack = 0;
    int ret = 0; // 리턴값 저장
    char tmp[10]; // 스택에 int 형태로 저장하기 위해, 문자열 배열 tmp, num tjsdjs
    char num[10];
    memset(tmp,0,10); // 초기화
    memset(num,0,10);

    for(int i=0; i<strlen(exp); i++){ // 후위 표기법 수식 처음부터 끝까지 검사
        if(exp[i]==','){ // ,를 만난 경우는 숫자가 완성된 경우이므로 atoi 함수를 통해 int 형으로 바꿔서 스택에 push
            strncpy(num,tmp,idx);
            stack[idx_stack] = atoi(num);
            idx_stack++;
            memset(tmp,0,10);
            memset(num,0,10);
            idx=0;
            continue;
        }
        if(exp[i]=='+'){ // + 연산자를 만남
            if((exp[i-1]!='+' && exp[i-1]!='-' && exp[i-1]!='/' && exp[i-1]!='*')){
                // + 연산자 전에 숫자가 나왔을 경우는, 위와 동일하게 스택에 추가하는 작업 진행
                strncpy(num,tmp,idx);
                stack[idx_stack] = atoi(num);
                idx_stack++;
                memset(tmp,0,10);
                memset(num,0,10);
                idx=0;
            }
            pop_stack(stack, &idx_stack, &a, &b); // 연산자를 만났으므로 계산하는 과정
            stack[idx_stack] = a + b; // 계산하여 스택에 추가 (이건 밑에 if문들도 모두 동일하고, 연산자만 다름)
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
            idx_stack++;
            continue;        
        }
        tmp[idx] = exp[i]; // 수식에서 숫자만 따로 저장해서 스택에 추가하기 위해, 연산자와 구분자를 만나기 전까지 계속 저장하도록 한다.
        idx++;
    }

    ret = stack[0]; // 최종적으로 스택에 남아있는 값이 마지막 

    return ret;
}
