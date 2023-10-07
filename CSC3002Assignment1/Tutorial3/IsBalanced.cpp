// It can be reprogrammed as just push brackets and check whether pure brackets string is valid.

#include <iostream>
#include <stack>
using namespace std;

int judge(string s);

int main(){
    string s;
    cin >> s;
    if(judge(s)){
        cout << "It is valid." <<endl;
    }else{
        cout << "It is not valid." <<endl;
    }
}

int judge(string s){
    stack<char> stack;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ']'){
            while(!stack.empty() && stack.top() != '['){
                stack.pop();
            }
            if(stack.empty()){
                return 0;
            }else{
                stack.pop();
            }
        }else if(s[i] == ')'){
            while(!stack.empty() && stack.top() != '('){
                stack.pop();
            }
            if(stack.empty()){
                return 0;
            }else{
                stack.pop();
            }
        }else if(s[i] == '}'){
            while(!stack.empty() && stack.top() != '{'){
                stack.pop();
            }
            if(stack.empty()){
                return 0;
            }else{
                stack.pop();
            }
        }else{
            stack.push(s[i]);
        }
    }
    return 1;
}