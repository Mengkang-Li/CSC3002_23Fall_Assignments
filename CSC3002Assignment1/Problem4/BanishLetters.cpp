/*
 * File: BanishLetters.cpp
 * -----------------------
 * This program removes all instances of a set of letters from
 * an input file.
 */

#include <iostream>
//#include "CSC3002OJActive/assignment1/lib.h"
using namespace std;
int ifBanish(string s, char c);

int banishLetters() {
   // TODO
   string banish;
   cin >> banish;
   cin.ignore(1); // 由于cin >> 不吸收换行符，所以需要加上
   while(!cin.eof()){
    char c = cin.get();
    if(!cin.eof() && !ifBanish(banish, c)){
        cout << c;
    }
   }
    return 0;
}

int ifBanish(string s, char c){
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 97){
            if(s[i] == c || s[i] - 32 == c){
                return 1;
            }
        }else{
            if(s[i] == c || s[i] + 32 == c){
                return 1;
            } 
        }
    }
    return 0;
}
/* DO NOT modify this main() part */
/*
 sample output:
 input: S
        this is a testing 1
        this is a testing 2
 output:
        thi i a teting 1
        thi i a teting 2
*/
int main(int argc, char* argv[]) {
    banishLetters();
    return 0;
}
