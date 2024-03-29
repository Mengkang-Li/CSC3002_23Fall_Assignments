/*
 * File: PriorityQueue.cpp
 * ---------------------------
 * This file contains a unit test of the PriorityQueue class.
 */

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// #include "CSC3002OJActive/assignment5/lib.h" // for OJ test
// #include "CSC3002OJActive/assignment5/priorityqueue.h" // for OJ test

// #include "lib.h" // for local test
// #include "pv2.h" // for local test

using namespace std;

int cnt;

void error(std::string msg) {
   std::cout << "ERROR: " << msg << std::endl;
}

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
   cnt = 0;
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class, so no work
 * is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

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
   heap.clear();
   count = 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   // TODO
   // We have count, as numbers of elements.

   HeapEntry hp;
   hp.value = value;
   hp.priority = priority;
   hp.sequence = cnt;
   heap.push_back(hp);
   cnt++;
   count++;
   // 添加操作
   int mid = count;
   while(mid > 1){
    if(heap[mid - 1].priority < heap[mid / 2 - 1].priority){
        HeapEntry he = heap[mid - 1];
        heap[mid - 1] = heap[mid / 2 - 1];
        heap[mid / 2 - 1] = he;
        mid = mid / 2;
    }else if(heap[mid - 1].priority == heap[mid / 2 - 1].priority && heap[mid - 1].sequence < heap[mid / 2 - 1].sequence){
        HeapEntry he = heap[mid - 1];
        heap[mid - 1] = heap[mid / 2 - 1];
        heap[mid / 2 - 1] = he;
        mid = mid / 2;
    }else{
      break;
    }
   }

}

/*
 * Implementation notes: dequeue, peek, peekPriority
 * -------------------------------------------------
 * These methods must check for an empty queue and report an error if there
 * is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   if (count == 0) error("dequeue: Attempting to dequeue an empty queue");
   //TODO
   ValueType ans = heap[0].value;
   HeapEntry hp = heap[count - 1];
   heap.pop_back();
   count--;
   if(count == 0){
      return ans;
   }
   heap[0] = hp;
   int mid = 1;
   // 先比右树
   while(mid <= count){
    if(mid * 2  + 1 <= count){
      HeapEntry left = heap[mid * 2 - 1];
      HeapEntry right = heap[mid * 2];
      if(left.priority < right.priority){
         if(heap[mid - 1].priority < left.priority){
            break;
         }else if(heap[mid - 1].priority == left.priority){
            if(heap[mid - 1].sequence < left.sequence){
               break;
            }else{
               heap[mid * 2 - 1] = heap[mid - 1];
               heap[mid - 1] = left;
               mid = mid * 2;
            }
         }
         else{
            heap[mid * 2 - 1] = heap[mid - 1];
            heap[mid - 1] = left;
            mid = mid * 2;
         }
      }else if(left.priority > right.priority){
         if(heap[mid - 1].priority < right.priority){
            break;
         }else if(heap[mid - 1].priority == right.priority){
            if(heap[mid - 1].sequence == right.sequence){
               heap[mid * 2] = heap[mid - 1];
               heap[mid - 1] = right;
               mid = mid * 2;
            }
         }
         else{
            heap[mid * 2] = heap[mid - 1];
            heap[mid - 1] = right;
            mid = mid * 2;
         }
      }else{
         if(heap[mid - 1].priority < left.priority){
            break;
         }else{
            if(left.sequence > right.sequence){
               heap[mid * 2] = heap[mid - 1];
               heap[mid - 1] = right;
               mid = mid * 2;
            }else{
               heap[mid * 2 - 1] = heap[mid - 1];
               heap[mid - 1] = left;
               mid = mid * 2;
            }
         }
      }
    }else if(mid * 2 <= count){
      HeapEntry left = heap[mid * 2 - 1];
      if(left.priority < heap[mid - 1].priority){
         heap[mid * 2 - 1] = heap[mid - 1];
         heap[mid - 1] = left;
         mid = mid * 2;
      }else if(left.priority == heap[mid - 1].priority && left.sequence < heap[mid - 1].sequence){
         heap[mid * 2 - 1] = heap[mid - 1];
         heap[mid - 1] = left;
         mid = mid * 2;
      }else{
         break;
      }
    }else{
      break;
    }
   }
   return ans;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   if (count == 0) error("peek: Attempting to peek at an empty queue");
   //TODO
   return heap[0].value;
}

template <typename ValueType>
double PriorityQueue<ValueType>::peekPriority() const {
   if (count == 0) error("peekPriority: Attempting to peek at an empty queue");
   //TODO
   return heap[0].priority;
}

template <typename ValueType>
void enqueueHeap(ValueType & value, double priority) {
   //TODO
}

template <typename ValueType>
ValueType dequeueHeap(){
   //TODO
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2) {
   /* Return true if i1 takes the priority */
   //TODO
   if(i1 > count || i2 > count){
      return false;
   }
   return heap[i1].priority > heap[i2].priority;
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
   /* Swap elements in the two positions */

   //TODO
}

template <typename ValueType>
std::string PriorityQueue<ValueType>::toString() {
   /* convert the PriorityQueue into a printable String */
   //TODO
   std::vector<HeapEntry> record = heap;
   int m = count;
   stringstream ss;
   ss << "{";
   while(!this->isEmpty()){
      ss << this->peekPriority() << ":\"" << this->dequeue() << "\"";
      if(count != 0){
         ss << ", ";
      }else{
         ss << "}";
      }
   }
   heap = record;
   count = m;
   return ss.str();
}

template <typename ValueType>
std::ostream & operator<<(std::ostream & os,
                          const PriorityQueue<ValueType> & pq) {
   /* give the output of all the elements in queue(not dequeue)
      i.e.: cout << pq gives the output of all the content in current queue without change pq */
   os << pq.toString();
   return os;
   //TODO
}

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
   cout<<"pq.toString() : "<<pq.toString()<<endl;
   int init_len = pq.size();
   for (int i = 0; i<init_len; i++) {
      cout<<"i="<<i<<": pq.peek() = "<<pq.peek()<<endl;
      cout<<"i="<<i<<": pq.dequeue() = "<<pq.dequeue()<<endl;
   }
   cout<<"pq.isEmpty(): "<<boolalpha<<pq.isEmpty()<<endl;
   return 0;
}
