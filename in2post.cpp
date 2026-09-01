#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "stack.h"
using namespace std;
using namespace cop4530;

//funcion definitions
vector<string> step1(const vector<string>& infix);
vector<string> tokenize(string input);
int precedence(const string& op);
bool isOperator(const string& token);
bool isOperand(const string& token);
int evaluate(const vector<string>& postfix);
int applyOperator(const string& a, const string& b, const string& op);
void printVector(const vector<string>& str);

//main function
int main(){

    vector<string> inputs;
    string input;
    int index = 0;

    cout << "Enter infix expressions on a single line type exit to quit"<<endl;
    while(true){
        getline(cin,input);
        if(input=="exit") break;
        inputs.push_back(input);
    }

    for(const auto& input: inputs){
        vector<string> infix = tokenize(input);
        vector<string> postfix = step1(infix);

        cout<<endl;

    cout << "Postfix expression "<<index+1<<": ";
    printVector(postfix);

    int temp = 0;
    bool breakFlag = false;
    for(int i = 0;i<postfix.size();i++){
        for(int j = 0;j<postfix[i].length();j++){
            if(isalpha(postfix[i][j])){
                cout<<"Result of expression "<<index+1<<": ";
                printVector(postfix);
                temp++;
                breakFlag = true;
                break;
            }
        }
        if(breakFlag) break;
    }
    
    if(temp==0){
        int result = evaluate(postfix);
        cout <<"Result of expression "<<index+1<<": "<< result << endl;
    }
    index++;
}
}

vector<string> step1(const vector<string>& infix){

    Stack<string> s;
    vector<string> output;

    if(infix.empty()) return output;

    for(const auto& token: infix){
        if(isOperand(token)){
            output.push_back(token);
        }
        else if(isOperator(token)){
            while(!s.empty() && precedence(s.top())>=precedence(token)){
                output.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
        else if(token==")"){
            while(!s.empty() && s.top()!="("){
                output.push_back(s.top());
                s.pop();
            }
            if(!s.empty()) s.pop(); // pop '('
        }
        else if(token=="("){
            s.push(token);
        }
    }

    while(!s.empty()){
        output.push_back(s.top());
        s.pop();
    }

    return output;
}

vector<string> tokenize(string input){
    vector<string> temp;
    string token;

    for(int i = 0;i<input.length();i++){
        if(input[i]==' '){
            temp.push_back(token);
            token.clear();
        }
        else{
            token+=input[i];
        }
    }

    if(!token.empty()){
        temp.push_back(token);
    }

    return temp;
}

int precedence(const string& op){
    if(op=="+" || op=="-") return 1;
    if(op=="*" || op=="/") return 2;
    return 0;
}

bool isOperator(const string& token){
    return token=="+" || token=="-" || token=="*" || token=="/";
}

bool isOperand(const string& token){
    return !isOperator(token) && token!="(" && token!=")";
}

int evaluate(const vector<string>& postfix){
    Stack<string> s;

    for(const auto& token: postfix){
        if(isOperand(token)){
            s.push(token);
        }
        else if(isOperator(token)){
            string b = s.top(); s.pop();
            string a = s.top(); s.pop();
            int result = applyOperator(a, b, token);
            s.push(to_string(result));
        }
    }
    
    return stoi(s.top());
}

int applyOperator(const string& a, const string& b, const string& op){
    int x = stoi(a);
    int y = stoi(b);
    if(op=="+") return x+y;
    if(op=="-") return x-y;
    if(op=="*") return x*y;
    if(op=="/") return x/y;
    cout<<"Invalid operator: "<<op<<endl;
    throw invalid_argument("Invalid operator");
}

void printVector(const vector<string>& str){
    for(const auto& item: str){
        cout<<item<<" ";
    }
    cout<<endl;
}