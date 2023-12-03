/*
 * File: priorityqueue.h
 * --------------
 * This file exports the PriorityQueue class, a collection in which values
 * are processed in priority order.
 */

#ifndef _priorityqueue_h
#define _priorityqueue_h

#include <vector>
#include <string>
/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a structure called a priority queue in which values
 * are processed in order of priority.  As in conventional English usage,
 * lower priority numbers correspond to higher effective priorities, so
 * that a priority 1 item takes precedence over a priority 2 item.
 */

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any heap storage associated with this priority queue.
 */

   virtual ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  Lower priority
 * numbers correspond to higher priorities, which means that all priority 1
 * elements are dequeued before any priority 2 elements.
 */

   void enqueue(ValueType value, double priority);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the highest priority value.  If multiple entries in
 * the queue have the same priority, those values are dequeued in the same
 * order in which they were enqueued.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the value of highest priority in the queue, without removing it.
 */

   ValueType peek() const;

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, without removing
 * it.
 */

   double peekPriority() const;

/*
 * Method: toString
 * Usage: string str = pq.toString();
 * ----------------------------------
 * Converts the queue to a printable string representation.
 */

   std::string toString();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The PriorityQueue class is implemented using a data structure called a
 * heap.
 */

private:

/* Type used for each heap entry */

   struct HeapEntry {
      ValueType value;
      double priority;
      long sequence;
   };

/* Instance variables */

   std::vector<HeapEntry> heap;
   long enqueueCount;
   int count;
   int capacity;

/* Private function prototypes */

   void enqueueHeap(ValueType & value, double priority); // OPTIONAL
   ValueType dequeueHeap(); // OPTIONAL
   bool takesPriority(int i1, int i2); // OPTIONAL
   void swapHeapEntries(int i1, int i2); // OPTIONAL

};

// extern void error(std::string msg);





#endif




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
