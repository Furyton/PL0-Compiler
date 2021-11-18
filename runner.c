#include "runner.h"

void run(int entry) {
    pc = entry;
    
    int status;

    while((status = exec(&codes[pc])) == 1);
    if (status == -1) printf("failed!!!!");
    else printf("success!!!");
}

int exec(Code* code) {
    switch (code->instr)
    {
    case C_ASSIGN:
        if (code->s1->kind == CONST) {
            code->dst->u.place->val = code->s1->u.val;
        } else {
            code->dst->u.place->val = code->s1->u.place->val;
        }
        break;
    case C_ODD:
        ALU = (code->s1->u.place->val) & 1;
        break;
    case C_NEG:
        code->dst->u.place->val = -code->s1->u.place->val;
        break;
    case C_PLUS:
        code->dst->u.place->val = code->s1->u.place->val + code->s2->u.place->val;
        break;
    case C_MINUS:
        code->dst->u.place->val = code->s1->u.place->val - code->s2->u.place->val;
        break;
    case C_MULT:
        code->dst->u.place->val = code->s1->u.place->val * code->s2->u.place->val;
        break;
    case C_DIV:
        code->dst->u.place->val = code->s1->u.place->val / code->s2->u.place->val;
        break;
    case C_EQ:
        ALU = (code->s1->u.place->val) == (code->s2->u.place->val);
        break;
    case C_LS:
        ALU = (code->s1->u.place->val) < (code->s2->u.place->val);
        break;
    case C_LE:
        ALU = (code->s1->u.place->val) <= (code->s2->u.place->val);
        break;
    case C_GT:
        ALU = (code->s1->u.place->val) > (code->s2->u.place->val);
        break;
    case C_GE:
        ALU = (code->s1->u.place->val) >= (code->s2->u.place->val);
        break;
    case C_NEQ:
        ALU = (code->s1->u.place->val) != (code->s2->u.place->val);
        break;
    case C_JMP:
        pc = code->s1->u.val;
        return 1;
        break;
    case C_J0:
        if (!ALU) {
            pc = code->s1->u.val;
            return 1;
        }
        break;
    case C_READ:
        scanf("%d", &code->dst->u.place->val);
        break;
    case C_WRITE:
        printf("%d\n", code->s1->u.place->val);
        break;
    case C_CALL:
        top++;
        stack[top] = pc + 1;
        pc = code->s1->u.place->val;
        return 1;
        break;
    case C_RET:
        pc = stack[top];
        top--;
        if (top < 0) return 0;
        return 1;
        break;
    default:
        return -1;
    }
    pc++;
    return 1;
}