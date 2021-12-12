/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id | id, Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//#define INPUT "input.sql"

const char* keywords[]={"select","from","where"};
char special_symbols[]={',','=','\''};
int row=1,col=1;
char buffer[256];

typedef struct TOK{
    char lexeme[50];
    int row,col;
    char type[50];
}Token;

int isSpecial(char c){
    int len=3;
    //len = sizeof(special_symbols)/sizeof(char);
    
    for(int i=0; i< len ; ++i){
        if(c==special_symbols[i])
            return 1;
    }
    return 0;
}

int iskeyword(char *w){
    for(int i=0 ; i< 3 ;++i){
        if(strcmp(keywords[i],w)==0)
            return 1;
    }
    return 0;
}

void newLine(){
    ++row;
    col=1;
}

void make_token(Token* tkn, int r,int c,char *lex, char *type){
    strcpy(tkn->lexeme,lex);
    strcpy(tkn->type,type);
    tkn->row = r;
    tkn->col = c;
    //printf("<%s,%d,%d,%s>\n",tkn->lexeme,tkn->row,tkn->col,tkn->type);
}

Token getNextToken(FILE *fp){
    char c;
    int gotToken=0;
    Token token;
    token.row=-1;
    
    while((c=fgetc(fp))!=EOF && !gotToken){
        //printf("scanned %c:\t",c);
        if(isspace(c)){
            ++col;
        }

        if(c=='\n'){
            newLine();
        }

        if(isSpecial(c)){
                char symbol[2];
                symbol[0]=c;
                symbol[1]='\0';
                make_token(&token,row,col,symbol,"Special Symbol");
                col+=1;
                gotToken=1;
        }

        else
          if(isalpha(c)){
            int k=0;
            char string[256];
            string[k++]=c;

            while((c=fgetc(fp))!= EOF && isalnum(c)){
                string[k++]=c;
            }
            //printf("%c\t",c);
            fseek(fp,-1,SEEK_CUR);
            //c=fgetc(fp);
            //printf("%c\t",c);
            //fseek(fp,-1,SEEK_CUR);
            string[k]='\0';
            //printf("%s\n",string);

            if(iskeyword(string)){
                make_token(&token,row,col,string,"keyword");
                col+=strlen(string);
                gotToken=1;
            }

            else{
                make_token(&token,row,col,string,"id");
                col+=strlen(string);
                gotToken=1;
            }
        }
           
        else{
            ++col;
        }
    }

    return token;
}

/*void GetNextToken(){
    Token token;
    FILE *fp;
    fp = fopen(INPUT,"r");

    while((token=getNextToken(fp)).row != -1){
        printf("<%s,%d,%d,%s>\n",token.lexeme,token.row,token.col,token.type);
    }

    fclose(fp);
    //return 0;
}*/