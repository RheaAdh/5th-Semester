#include <stdio.h>
#define PI 31.4
int main(){
 int x=100;
 int y;
 int z;
 /*
 a
 b
 c
 d
 */ int a;
 while(x--){
 if(x%2==0){
 printf("%d",x);
 }
 }
 printf("shld show->/*hello this is a comment inside a printf -multiline*/");
 printf("shld show->//hello this is a comment inside a printf - single line");
}