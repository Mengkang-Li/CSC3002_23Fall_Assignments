/*
This is an unfinished algorithm. How can I ensure FIFO in priority queue using heap?
*/

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

#include "lib.h" // for local test
#include "p2.h" // for local test

using namespace std;

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

void error(std::string msg) {
   std::cout << "ERROR: " << msg << std::endl;
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
   count++;
   // 使用vector添加的时候要使用push_back 而且注意这个时候push进去的是第0个开始
   HeapEntry hp;

   hp.priority = priority;
   hp.value = value;
   hp.sequence = count; // 声明sequence 用来记录加入的时间 如果优先级相同 那么比较时间来保证先进先出
   heap.push_back(hp);
   int now = count;
   while(now > 1 && heap[now / 2 - 1].priority > heap[now - 1].priority){
      HeapEntry mid = heap[now - 1];
      heap[now - 1] = heap[now / 2 - 1];
      heap[now / 2 - 1] = mid;
      now = now / 2;
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
   // 想一个迭代的解决方法
   if (count == 0) error("dequeue: Attempting to dequeue an empty queue");
   //TODO
   HeapEntry ans = heap[0];
   heap[0] = heap[count - 1];
   // 最后一个元素移上去之后 要移除最后一个，防止push时出错
   heap.pop_back();
   count--;
   int mid = 1;
   while(count >= mid * 2){
      // 先跟左树比较 如果大于 那么就换 如果等于 那么就比较sequence  大于就换 小于就不换 
      if(count >= mid * 2 + 1 && heap[mid * 2].priority <= heap[mid - 1].priority && heap[mid * 2].sequence < heap[mid - 1].sequence){
         HeapEntry he = heap[mid - 1];
         heap[mid - 1] = heap[mid * 2];
         heap[mid * 2] = he;
         mid = mid * 2 + 1;
      }
      else if(heap[mid * 2 - 1].priority <= heap[mid - 1].priority && heap[mid * 2 - 1].sequence < heap[mid - 1].sequence){
         HeapEntry he = heap[mid - 1];
         heap[mid - 1] = heap[mid * 2 - 1];
         heap[mid * 2 - 1] = he;
         mid = mid * 2;
      }else if(mid - 2 >= 0 && heap[mid - 1].priority <= heap[mid - 2].priority && heap[mid - 1].sequence < heap[mid - 2].sequence){
         // 同层防止顺序不同
         // 但是无法保证换上去的顺序可以 貌似先跟右边比就可以断绝一切问题 最后从右往左来 从右往左来会导致最后在上面的优先级比下面的低 
         // 难道是遍历所有的 找到priority最高但小于等于目标 然后sequence最大的？
         // 仍然从左往右来 然后对每一个交换之后的都平级交换一下？
         // 或者是如果都行的话选择它本来的方向？
         // 或者最后使用数组实现......

         HeapEntry he = heap[mid - 1];
         heap[mid - 1] = heap[mid];
         heap[mid] = he;
         mid++;
      }else{
         break;
      }
      // 矫正左树和右树 可能还需要矫正他们的孩子树
   }
   
   return ans.value;
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
   stringstream ss;
   ss << "{";
   for(int i = 0; i < count; i++){
      ss << heap[i].priority << ":\"" << heap[i].value << "\"";
      if(i != count - 1){
         ss << ", ";
      }else{
         ss << "}";
      }
   }
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
