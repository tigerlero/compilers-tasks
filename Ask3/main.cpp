#include <iostream>
#include <map>
#include <stack>

using namespace std;


map<char,map<char,string > > table;
stack <char> sStack;

void PassToStack(string toPass);
void PrintStack();


void ReadString(string sentence){
    char a = sentence[0]; //First letter of sentence
    char x = sStack.top(); //Top of stack

    cout << endl << "Current Sentence = " << sentence << endl;
    cout << "First letter = " << a << endl;
    cout << "Top of stack = " << x << endl;

    PrintStack();


    if(isupper(x)){ //Returns true if x is uppercase
        //x is Non-Terminal (uppercase chars define Non-Terminals in this grammar)
        string rule = table[x][a];

        if(rule == ""){
            //Sentence can't be recognized by this grammar
            cout << endl << "Fail" << endl;
            return;
        }else{
            //Replace top of stack with new rule (in reverse)
            sStack.pop();
            PassToStack(rule);
        }
    }else{
        //x is Terminal (lowercase chars define Terminals in this grammar)
        if(x == a){
            if(a != '$'){
                //a has been recognized
                sStack.pop(); //Remove top of stack
                sentence.erase(sentence.begin()); //Remove a from sentence
            }else{
                //Identification process has finished successfully
                cout << endl << "Success" << endl;
                return;
            }
        }else{
            //Sentence can't be recognized by this grammar
            cout << endl << "Fail" << endl;
            return;
        }
    }

    //Print new stack
    cout << "New ";
    PrintStack();

    ReadString(sentence); //Continue
}

void PassToStack(string toPass){
    int s = toPass.size();

    if(toPass == "e"){
        //e isn't passed into stack
        return;
    }

    for(int i=0; i<s; i++){
        //Push chars of new rule from last to first
        sStack.push(toPass[s-i-1]);
    }
}

void PrintStack(){
    int s = sStack.size();
    char toPrint[s];

    stack <char> tempStack;
    tempStack = sStack;

    //Pass stack to array
    for(int i=0; i<s; i++){
        toPrint[s-i-1] = tempStack.top(); //New array needs to be reversed
        tempStack.pop();
    }

    string newString;

    for(int i=0; i<s; i++){
        newString += toPrint[i]; //Create string to print on screen
    }

    cout << "Stack = " << newString << endl;
}

void ClearStack(){
    //Pop everything in stack
    int s = sStack.size();

    for(int i=0; i<s; i++){
        sStack.pop();
    }
}

void InitTable(){
    //Initialize syntax table

    table['S']['['] = "[A]";
    table['S'][']'] = "";
    table['S']['x'] = "";
    table['S']['y'] = "";
    table['S']['+'] = "";
    table['S'][':'] = "";
    table['S']['$'] = "";

    table['A']['['] = "BE";
    table['A'][']'] = "";
    table['A']['x'] = "BE";
    table['A']['y'] = "BE";
    table['A']['+'] = "";
    table['A'][':'] = "";
    table['A']['$'] = "";

    table['B']['['] = "S";
    table['B'][']'] = "";
    table['B']['x'] = "x";
    table['B']['y'] = "y";
    table['B']['+'] = "";
    table['B'][':'] = "";
    table['B']['$'] = "";

    table['E']['['] = "";
    table['E'][']'] = "e";
    table['E']['x'] = "";
    table['E']['y'] = "";
    table['E']['+'] = "+A";
    table['E'][':'] = ":A";
    table['E']['$'] = "";
}

int main(){
    sStack.push('$');
    sStack.push('S');

    InitTable();

    ReadString("[[y:x]+[x:y]]$"); //This should return successful


    //Let user test his own sentences, until he gets bored and enters 'z'
    string newSentence;
    cout << endl << endl << endl << "Enter your own string (enter z to exit): " << endl;
    cout << "(NOTE: Do not put '$' in your string)" << endl;
    cin >> newSentence;

    while(newSentence != "z"){
        ClearStack();
        sStack.push('$');
        sStack.push('S');

        newSentence += '$'; //Add '$' at the end of sentence
        ReadString(newSentence);

        cout << endl << endl << endl << "Enter your own string (enter z to exit): " << endl;
        cout << "(NOTE: Do not put '$' in your string)" << endl;
        cin >> newSentence;
    }


    cout << endl << "Finished" << endl;
    return 0;
}
