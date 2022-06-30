#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


map<string,vector<string> > rules;
vector<string> N; //Non-terminals
vector<string> T; //Terminals

string NewSentence(string curr);
string SentenceGeneration(string curr);

void Init();


string NewSentence(string curr){
    vector<string> temp;
    vector<int> posList1;
    vector<int> posList2;

    int pos1 = 0;
    int pos2 = 0;

    //Iteration through curr
    for(int i=0; i<curr.size(); i++){
        if(curr[i] == '<'){
            pos1 = i;
        }else if(curr[i] == '>'){
            pos2 = i;
            //Non-terminals are between '<' and '>'. So, [pos1,pos2] is a non-terminal, which we add to temp
            temp.push_back(curr.substr(pos1,pos2-pos1+1));
            posList1.push_back(pos1); //We store pos1
            posList2.push_back(pos2); //We store pos2
        }
    }

    int r = rand()%temp.size(); //A random number between 0 and temp.size()
    string toReplace = temp[r]; //We randomly select a non-terminal (in temp) to replace
    pos1 = posList1[r]; //The position of the '<' of our selected non-terminal
    pos2 = posList2[r]; //The position of the '>' of our selected non-terminal

    r = rand()%rules[toReplace].size();
    string rule = rules[toReplace][r]; //We randomly select a rule to replace our selected non-terminal, from its list (vector) of rules

    string leftPart = curr.substr(0,pos1); //The part on the left of toReplace
    string rightPart = curr.substr(pos2+1,curr.size()-pos2-1); //The part on the right of toReplace

    string newCurrent = leftPart + rule + rightPart; //Create new sentence, replacing toReplace with rule

    return newCurrent;
}

string SentenceGeneration(string curr){
    if(curr.find('<') == string::npos){
        return curr; //Curr contains no non-terminals. Thus, sentence generation came to an end.
    }

    string newCurr = NewSentence(curr); //Generate new sentence by replacing one non-terminal

    cout << newCurr << endl;

    SentenceGeneration(newCurr); //Continue recursively

    return "Finished";
}

void Init(){
    srand(time(NULL)); //Initialize random number generator

    //Non-terminals initialization
    N.push_back("<expression>");
    N.push_back("<term>");
    N.push_back("<factor>");

    //Terminals initialization
    T.push_back("a");
    T.push_back("b");
    T.push_back("c");

    //Rules initialization
    rules["<expression>"].push_back("<term>");
    rules["<expression>"].push_back("<expression> + <term>");

    rules["<term>"].push_back("<factor>");
    rules["<term>"].push_back("<term> * <factor>");

    rules["<factor>"].push_back("a");
    rules["<factor>"].push_back("b");
    rules["<factor>"].push_back("c");
}

int main(){
    Init();

    char x;

    do{
        cout << endl << endl << "<expression>" << endl;
        string sentence = SentenceGeneration("<expression>"); //Begin recursive generation
        cout << endl << sentence << endl << endl;


        cout << endl << "Enter x to exit, enter anything else to see another example" << endl;
        cin >> x;
    }while(x != 'x');

    return 0;
}
