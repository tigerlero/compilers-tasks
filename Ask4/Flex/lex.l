%{
int state = 0;
%}
name [a-zA-Z][a-zA-Z0-9_]*
type "integer"|"real"|"boolean"|"char"
declaration {name}(" "*","" "*{name})*" "*":"" "*{type}";"
%%
^"var"" "+{declaration} {if(state == 0)state = 1;else{state = -1;}}
. {state = -1;}
(\n{declaration})* {if(state == 1){state = 2;}else if(state == 0){state = -1;}}
<<EOF>> {if(state != -1){state = 3;} return 0;}
%%
main() {
	yylex();

	if(state == 3){
		printf("Successful");
	}else{
		printf("Failed");
	}
}
