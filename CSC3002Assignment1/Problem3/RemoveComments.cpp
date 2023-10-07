// 最终是要在输出前检查是否读取的最后一个符号是end of file 即get() 会读取end of file
/*
 * File: RemoveComments.cpp
 * ------------------------
 * Prints out a file after removing comments.
 */
// header file for local test
#include <iostream>
#include <iomanip>
//#include "CSC3002OJActive/assignment1/RemoveComments.h" //for OJ
#include "RemoveComments.h" //for local test
using namespace std;


/*
 * Function: removeComments
 * Usage: removeComments(is, os);
 * ------------------------------
 * Copies characters from the input stream is to the output stream os,
 * removing any comments it finds.  This program eliminates both the
 * /* and // comment forms but does not check to see if those characters
 * are embedded within strings.
 */

void removeComments(istream & is, ostream & os) {
   //TODO
   while(!is.eof()){
        char c = is.get();
        if(c == '/'){
            char m = is.get();
            if(m == '/'){
                string d;
                char chars[1024];
                is.getline(chars, 1024);
                if(!is.eof()){
                os << '\n';}
            }else if(m == '*'){
                char mid = '0';
                while(mid != '/'){
                    while(mid != '*'){
                        mid = is.get();   
                    }
                    mid = is.get();
                }
            }else{
                os << c;
                if(!is.eof()){
                os << m;
                }
            }
        } else {
            if(!is.eof()){
                os << c;
            }
            
        }
   }
}


void TestRemoveComments(){
    removeComments(cin, cout);
}

// DO NOT modify the main() function
/*
 * sample output format:
 * input:  test file // this is a comment
           test file /* this is also a comment*/
/* output: test file
           test file
 */
int main(int argc, char* argv[]) {
    TestRemoveComments();
    return 0;
}

