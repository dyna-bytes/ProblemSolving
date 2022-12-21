#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
using namespace std;
#define STA 0b000
#define LDA 0b001
#define BEQ 0b010
#define NOP 0b011
#define DEC 0b100
#define INC 0b101
#define JMP 0b110
#define HLT 0b111

unsigned char ADDER;
unsigned char PC;
unsigned char MEM[32];
bool EXIT;

void decode() {
    unsigned char INST = MEM[PC] >> 5;
    unsigned char X = MEM[PC] & 0b11111;
    if (++PC == 32) PC = 0;

    switch (INST) {
    case STA:
        MEM[X] = ADDER;
        break;
    case LDA:
        ADDER = MEM[X];
        break;
    case BEQ:
        if (ADDER == 0) PC = X;
        break;
    case NOP:
        break;
    case DEC:
        ADDER--;
        break;
    case INC:
        ADDER++;
        break;
    case JMP:
        PC = X;
        break;
    case HLT:
        EXIT = true;
        break;    
    default:
        break;
    }
}

int main() {
    while (true) {
        EXIT = 0;
        ADDER = 0;
        PC = 0;
        memset(MEM, 0, sizeof(MEM));
        for (int i = 0; i < 32; i++) {
            for (int b = 0; b < 8; b++) {
                int bit;
                if (scanf("%1d", &bit) == EOF) return 0;

                MEM[i] <<= 1;
                MEM[i] += bit;
            }
        }

        while (!EXIT) 
            decode();
        for (int i = 7; i >= 0; i--) printf("%1d", (ADDER >> i) & 1);
        printf("\n");
    }    

    return 0;
}