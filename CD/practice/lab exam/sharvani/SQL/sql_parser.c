#include "sql_la.h"

#define INPUT "input.sql"

/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id | id, Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/

Token token;
int flag=0,unget=0;
FILE *fp;

void Query();
void Parameters();
void Parameters_prime();
void Fclause();
void Wclause();
void Exp();

void Valid(){
    printf("\n****************SUCCESS**************************\n");
}

void Invalid(){
    if(!flag)
        printf("**********ERROR*********************");
}


void CheckandGet(){
    if(!unget){
        token=getNextToken(fp);
    }
    else{
        unget=0;
    }
}

void Query(){
    CheckandGet();
    if(strcmp(token.lexeme,"select")==0){
        Parameters();
        Fclause();
        Wclause();
    }
    else{
        Invalid();
        flag=1;
    }
}


void Parameters(){
    CheckandGet();
    if(strcmp(token.type,"id")==0){
        Parameters_prime();
    }
    else{
        Invalid();
        flag=1;
    }
}

void Parameters_prime(){
    CheckandGet();
    if(strcmp(token.lexeme,",")==0){
        Parameters();
    }
    else{
        unget=1;
    }
}

void Fclause(){
    CheckandGet();
    if(strcmp(token.lexeme,"from")==0){
        Parameters();
    }
    else{
        Invalid();
        flag=1;
    }
}

void Wclause(){
    CheckandGet();
    if(strcmp(token.lexeme,"where")==0){
        Exp();
    }
    else{
        Invalid();
        flag=1;
    }
}

void Exp(){
    CheckandGet();
    if(strcmp(token.type,"id")==0){
        CheckandGet();
        if(strcmp(token.lexeme,"=")==0){
            CheckandGet();
            if(strcmp(token.lexeme,"\'")==0){
                CheckandGet();
                if(isalpha(token.lexeme[0])){
                    CheckandGet();
                    if(strcmp(token.lexeme,"\'")==0){
                        Valid();
                    }
                    else{
                        Invalid();
                        flag=1;
                    }
                }
                else{
                    Invalid();
                    flag=1;
                }
            }
            else{
                Invalid();
                flag=1;
            }
        }
        else{
            Invalid();
            flag=1;
        }
    }
    else{
        Invalid();
        flag=1;
    }
}

int main(){

    fp =fopen(INPUT,"r");
    Query();
    fclose(fp);
    return 0;
}