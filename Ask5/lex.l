%{
#include <math.h>

int flag = 0;

int state = 0;
%}
verb [A-Z]{1}[a-z]*
shape [a-z]*
%%
^{verb} {if(state == 0){printf("%s : is verb\n", yytext);state = 1;}}
{shape} {if(state == 1){printf("%s : is shape\n", yytext);state = 2;}}

[A-E]{1,5} {
	if(state == 2){
		flag = 0;
	
		char a,b,c,d,e;
		a = yytext[0];
		b = yytext[1];
		c = yytext[2];
		d = yytext[3];
		e = yytext[4];
	
		if(yyleng == 1){
			flag = 1;
		}else if(yyleng == 2){
			if(a != b){
				flag = 1;
			}
		}else if(yyleng == 3){
			if(a != b && a != c && b != c){
				flag = 1;
			}
		}else if(yyleng == 4){
			if(a != b && a != c && a != d && b != c && b != d && c != d){
				flag = 1;
			}
		}else if(yyleng == 5){
			if(a != b && a != c && a != d && a != e && b != c && b != d && b != e && c != d && c != e && d != e){
				flag = 1;
			}
		}

		if(flag == 1){
			printf("%s : is name\n", yytext);
			state = 3;
		}else{
			printf("\nRepeating letters in name");
		}
	}
}

.
%%
main() {
	yylex();
	
	if(state != 3){
		printf("\nWrong input");
	}
}
