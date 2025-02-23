#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<stdbool.h>
int pool_size = 1024*1024;
int *text;
int *old_text;
int *stack;
char *data;


enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
    OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
    OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };


int *pc,*bp,*sp,ax,cycle;



int eval() {
    int op,*tmp;
    while(true) {
        op = *pc+=1;
        if(op == IMM) {
            ax = *pc+=1;
        } else if(op == LC) {
            ax = *(char*)ax;
        } else if(op == LI) {
            ax = *(int*)ax;
        }
        else if(op == SC) {
            *(char*)ax = (char)ax;
        } else if(op == SI) {
            *(int*)ax = ax;
        } else if(op == PUSH) {
            *--sp = ax;
        } else if(op == JMP) {
            pc = (int *)*pc;
        } else if(op == JZ) {
            pc = ax?pc+1:(int *)*pc;
        } else if(op == JNZ) {
            pc = ax?(int*)*pc:pc+1;
        } else if(op == CALL) {
            *--sp=(int)(pc+1);
            pc = (int*)*pc;
        } else if(op == ENT) {
            *--sp = (int)bp; 
            bp = sp; 
            sp = sp - *pc++;
        } else if(op ==ADJ) {
            sp = sp+*pc++;
        } else if(op == LEV) {
            sp = bp; 
            bp = (int *)*sp++;
             pc = (int *)*sp++;
        } else if(op == LEA) {
            ax = (int)(bp+*pc++);
        }
        else if (op == OR)  ax = *sp++ | ax;
else if (op == XOR) ax = *sp++ ^ ax;
else if (op == AND) ax = *sp++ & ax;
else if (op == EQ)  ax = *sp++ == ax;
else if (op == NE)  ax = *sp++ != ax;
else if (op == LT)  ax = *sp++ < ax;
else if (op == LE)  ax = *sp++ <= ax;
else if (op == GT)  ax = *sp++ >  ax;
else if (op == GE)  ax = *sp++ >= ax;
else if (op == SHL) ax = *sp++ << ax;
else if (op == SHR) ax = *sp++ >> ax;
else if (op == ADD) ax = *sp++ + ax;
else if (op == SUB) ax = *sp++ - ax;
else if (op == MUL) ax = *sp++ * ax;
else if (op == DIV) ax = *sp++ / ax;
else if (op == MOD) ax = *sp++ % ax;
else if (op == EXIT) { printf("exit(%d)", *sp); return *sp;}
else if (op == OPEN) { ax = open((char *)sp[1], sp[0]); }
else if (op == CLOS) { ax = close(*sp);}
else if (op == READ) { ax = read(sp[2], (char *)sp[1], *sp); }
else if (op == PRTF) { tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
else if (op == MALC) { ax = (int)malloc(*sp);}
else if (op == MSET) { ax = (int)memset((char *)sp[2], sp[1], *sp);}
else if (op == MCMP) { ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
else {
    printf("unknown instruction:%d\n", op);
    return -1;
}
    }

    return 0;
}
int main()
{
    if(!(text = old_text = malloc(pool_size)) ){
        printf("mem alloc failed for size %d for text_area\n",pool_size);
        return -1;
    }
    if(!(data = malloc(pool_size))){
        printf("mem alloc failed for size %d for data_area\n",pool_size);
        return -1;
    }
    if(!(stack = malloc(pool_size))){
        printf("mem alloc failed for size %d for stack_area\n",pool_size);
        return -1;
    }
    memset(text, 0, pool_size);
    memset(data, 0, pool_size);
    memset(stack, 0, pool_size) ;

    bp=sp = (int*)malloc(pool_size+(int)stack);
    ax=0;
    return 0;
}