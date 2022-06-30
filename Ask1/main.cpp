#include <iostream>
#include <stack>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

ifstream input("input.txt");
stack <char> sAuto;
int state = 0;
int line = 1;
list<string> log;

void Print(char t);
void Automata(char toEnter);
void ReadInput();


void ReadInput(){
    bool hasParentheses = false; //We only need to check the lines with parentheses

    while(!input.eof()){
        char c;
        input.get(c);

        if(c == '(' || c == ')'){
            hasParentheses = true; //This line has parenthesis
            Automata(c);
        }

        if(c == '\n' && hasParentheses){
            //We checked this line because it had parentheses
            hasParentheses = false; //Reset hasParentheses, as line ended
            Automata(c);
        }

        if(state == -1){
            //Input wasn't recognized, no need to keep going
            cout << "NO" << endl;
            cout << endl << "Wrong Parentheses on line " << line << endl << endl;
            break;
        }

        if(c == '\n'){
            line++;
        }
    }

    if(state == 0){
        //Reached End of File
		//The starting symbol ($) is on the top of stack
        //Input was recognized
        cout << endl << "YES" << endl << endl;
    }
}

void Automata(char toEnter){
    char top = sAuto.top();

    Print(toEnter);

    if(top == '$'){
        if(toEnter == ')'){
            state = -1; //Line can't be recognized
        }else if(toEnter == '('){
            sAuto.push(toEnter);
        }else{
            //Line was recognized
            //Moving on to next line
        }
    }else if(top == '('){
        if(toEnter == ')'){
            sAuto.pop();
        }else if(toEnter == '('){
            sAuto.push(toEnter);
        }else{
            state = -1; //Line can't be recognized
        }
    }
}

void Print(char t){
    int s = sAuto.size();
    char toPrint[s];

    stack <char> tempStack;
    tempStack = sAuto;

    //Pass stack to array
    for(int i=0; i<s; i++){
        toPrint[s-i-1] = tempStack.top(); //New array needs to be reversed
        tempStack.pop();
    }

    if(t == '\n'){
        t = 'n'; //This is the char that will appear. If left '\n', it would appear as a new line.
    }

    //Int to Str
    ostringstream temp;
    temp << state;

    ostringstream temp2;
    temp2 << line;

    //Writing a new line
    string newString = "Line " + temp2.str() + "\n" + "State = " + temp.str() + "\n" + "Stack = ";

    for(int i=0; i<s; i++){
        newString += toPrint[i];
    }

    newString += '\n';
    newString += "Input Char = ";
    newString += t;
    newString += '\n';
    newString += '\n';

    //Adding new line to log
    log.push_back(newString);
}

int main(){
    sAuto.push('$'); //Initialize stack

    ReadInput();

    char c;

    cout << "Enter 'Y'/'y' to see the procedure step-by-step. Press any other key to exit." << endl;
    cin >> c;

    if(c == 'Y' || c == 'y'){
        cout << endl << endl;

        list<string>::const_iterator i;
        for(i = log.begin(); i != log.end(); i++){
            cout << *i;
        }

        cout << "Final State is: " << state << endl;
    }


    char x;
    cout << endl << endl << "Enter something to exit" << endl;
    cin >> x;

    return 0;
}
