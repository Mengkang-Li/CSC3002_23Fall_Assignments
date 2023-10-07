
/* P1:
 * File: reversequeue.cpp
 * ----------------------
 * This file tests the ReverseQueue function.
 */

#include <iostream>
//#include "CSC3002OJActive/assignment2/reversequeue.h" // For OJ test
//#include "reversequeue.h" // For local test
#include <stack>
#include <queue>
using namespace std;

/* TODO PART:
 * Function: reverseQueue
 * Usage: reverseQueue(queue);
 * ---------------------------
 * Reverses the order of the elements in a queue.  This
 * implementation does so by using a stack to hold the
 * values as they are being reversed.
 */

void reverseQueue(queue<string> & queue) {
   // TODO
   stack<string> s;
   while(!queue.empty()){
    s.push(queue.front());
    queue.pop();
   }
   while(!s.empty()){
    queue.push(s.top());
    s.pop();
   }
}

/* TODO PART:
 * Function: listQueue
 * Usage: listQueue(queue);
 * ------------------------
 * Lists the contents of the queue on the standard output stream.
 */

void listQueue(queue<string> & queue) {
   // TODO
   cout << "The queue contains: ";
   int len = queue.size();
   for(int i = 0; i < len - 1; i++){
    cout << queue.front() << " ";
    queue.push(queue.front());
    queue.pop();
   }
   cout << queue.front() << endl;
   queue.push(queue.front());
   queue.pop();
}

/* DO NOT modify this main() part*/

int main() {
    string str;
    queue<string> line;

    while(cin>>str){
        line.push(str);
    }
    listQueue(line);
    reverseQueue(line);
    listQueue(line);
    return 0;
}
