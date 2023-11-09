/* P1:
 * File: p1PriorityQueue.cpp
 * -------------------------------
 * This file implements a simple test of the PriorityQueue class.
 */

#include <cassert>
#include <iostream>
#include <string>
// #include "CSC3002OJActive/assignment4/lib.h"
// #include "CSC3002OJActive/assignment4/PriorityQueue.h"
// #include "lib.h"
#include "PriorityQueue.h"
using namespace std;

/*
 * Implementation section
 * ----------------------
 * C++ requires that the implementation for a template class be available
 * to the compiler whenever that type is used.  The effect of this
 * restriction is that header files must include the implementation.
 * Clients should not need to look at any of the code beyond this point.
 */

/*
 * Implementation notes: PriorityQueue constructor
 * -----------------------------------------------
 * The constructor creates an empty linked list and sets the count to 0.
 */

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   head = NULL;
   count = 0;
}

/*
 * Implementation notes: PriorityQueue destructor
 * ----------------------------------------------
 * The destructor frees any heap memory allocated by the queue.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   clear();
}

/*
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These methods use the count variable and therefore run in constant time.
 */

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   while (count > 0) {
      dequeue();
   }
}

/*
 * Implementation notes: enqueue
 * -----------------------------
 * This method allocates a new list cell and chains it into the list at
 * the appropriate position.  In this implementation, that position is
 * determined using linear search and therefore runs in O(N) time.
 * Chapter 19 introduces an alternate implementation of PriorityQueue
 * that runs in O(log N) time.
 */

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   //TODO
   /*
   1. count 的值改变
   2. 当比head小的时候，加到head前
   */
   count++;
   PriorityQueue::Cell *mid = head;
   if(mid == NULL){
      head = new PriorityQueue::Cell;
      head->data = value;
      head->priority = priority;
      head->link = NULL;
      return;
   }
   if(head->priority > priority){
      PriorityQueue::Cell *next = head;
      head = new PriorityQueue::Cell;
      head->data = value;
      head->link = next;
      head->priority = priority;
      return; 
   }
   if(mid->link == NULL){
      mid->link = new PriorityQueue::Cell;
      mid->link->data = value;
      mid->link->priority = priority;
      mid->link-> link = NULL;
      return;
   }
   while(mid->link != NULL){
      PriorityQueue::Cell *next = mid->link;
      if(mid->priority <= priority && next->priority > priority){
         mid->link = new PriorityQueue::Cell;
         mid->link->data = value;
         mid->link->priority = priority;
         mid->link->link = next;
         return;
      }else if(next->link == NULL){
         next->link = new PriorityQueue::Cell;
         next->link->data = value;
         next->link->priority = priority;
         next->link->link = NULL;
         return;
      }
      mid = mid->link;

   }
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods checks for an empty queue and reports an error if
 * there is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   if (isEmpty()) error("dequeue: Attempting to dequeue an empty queue");
   //TODO
   ValueType ans = head->data;
   head = head->link;
   count--;
   return ans;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   if (isEmpty()) error("peek: Attempting to peek at an empty queue");
   //TODO
   return head->data;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods follow the standard template, leaving the work to deepCopy.
 */

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue(const PriorityQueue<ValueType> & src) {
   deepCopy(src);
}

template <typename ValueType>
PriorityQueue<ValueType> & PriorityQueue<ValueType>::operator=(const PriorityQueue<ValueType> & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This function copies the data from the src parameter into the current
 * object.  This implementation copies the list into a new list of cells.
 */

template <typename ValueType>
void PriorityQueue<ValueType>::deepCopy(const PriorityQueue<ValueType> & src) {
   head = NULL;
   Cell **target = &head;
   for (Cell *scp = src.head; scp != NULL; scp = scp->link) {
      Cell *cp = new Cell;
      cp->data = scp->data;
      cp->priority = scp->priority;
      *target = cp;
      target = &cp->link;
   }
   *target = NULL;
   count = src.count;
}

/* DO NOT modify the main() function*/
int main() {
   PriorityQueue<string> pq;
   string value;
   double priority;

   string in_pair;
   while(getline(cin,in_pair)){
      int sp = in_pair.find(' ');
      value = in_pair.substr(0, sp);
      priority = stod(in_pair.substr(sp+1, in_pair.size()));
      pq.enqueue(value, priority);
   }
   cout<<"pq.size() = "<<pq.size()<<endl;
   int init_len = pq.size();
   for (int i = 0; i<init_len; i++) {
      cout<<"i="<<i<<": pq.peek() = "<<pq.peek()<<endl;
      cout<<"i="<<i<<": pq.dequeue() = "<<pq.dequeue()<<endl;
   }
   cout<<"pq.isEmpty(): "<<boolalpha<<pq.isEmpty()<<endl;
   return 0;
}
