/* P3:
 * File: p3beffer.cpp
 * -------------------
 * This file implements EditorBuffer
 */
#include <iostream>
#include <sstream>
// #include "CSC3002OJActive/assignment4/buffer.h"
// #include "CSC3002OJActive/assignment4/SimpleTextEditor.h"
#include "buffer.h"
#include "SimpleTextEditor.h"

using namespace std;

/*
 * Implementation notes: EditorBuffer constructor
 * ----------------------------------------------
 * This function initializes an empty editor buffer, represented
 * as a doubly linked list.  In this implementation, the ends of
 * the linked list are joined to form a ring, with the dummy cell
 * at both the beginning and the end.  This representation makes
 * it possible to implement the moveCursorToEnd method in constant
 * time, and reduces the number of special cases in the code.
 */

EditorBuffer::EditorBuffer() {
   start = cursor = new Cell;
   start->next = start;
   start->prev = start;
}

/* TODO PART:
 * Implementation notes: EditorBuffer destructor
 * ---------------------------------------------
 * The destructor must delete every cell in the buffer.  Note
 * that the loop structure is not exactly the standard idiom for
 * processing every cell within a linked list, because it is not
 * legal to delete a cell and later look at its next field.
 */

EditorBuffer::~EditorBuffer() {
   // TODO
   EditorBuffer::Cell *mid = start->next;
   cursor = start;
   while(cursor->next != start){
      deleteCharacter();
   }
   delete start;
}

/* TODO PART:
 * Implementation notes: cursor movement
 * -------------------------------------
 * In a doubly linked list, each of these operations runs in
 * constant time.
 */

void EditorBuffer::moveCursorForward() {
   // TODO
   if(cursor->next != start){
      cursor = cursor->next;
   }
}

void EditorBuffer::moveCursorBackward() {
   // TODO
   if(cursor != start){
   cursor = cursor->prev;
   }

}

void EditorBuffer::moveCursorToStart() {
   // TODO
   cursor = start;
}

void EditorBuffer::moveCursorToEnd() {
   // TODO
   cursor = start->prev;
}

/* TODO PART:
 * Implementation notes: insertCharacter, deleteCharacter
 * ------------------------------------------------------
 * This code is much like that used for the traditional linked
 * list except that more pointers need to be updated.
 */

void EditorBuffer::insertCharacter(char ch) {
   // TODO
   EditorBuffer::Cell *mid = cursor->next;
   cursor -> next = new Cell;
   cursor->next->ch = ch;
   cursor->next->prev = cursor;
   cursor->next->next = mid;
   mid->prev = cursor->next;
   cursor = cursor->next;
   // cout << "Inserting" << endl;
}

void EditorBuffer::deleteCharacter() {
   // TODO
   
   if(cursor != start->prev){
      EditorBuffer::Cell *midNext = cursor->next;
      EditorBuffer::Cell *mid = midNext->next;
      cursor->next = mid;
      mid->prev = cursor;
      delete midNext;
   }
   //cout << "Deleting" <<endl;
}

/* TODO PART:
 * Implementation notes: getText and getCursor
 * -------------------------------------------
 * The getText method uses the standard linked-list pattern to loop
 * through the cells in the linked list.  The getCursor method counts
 * the characters in the list until it reaches the cursor.
 */

string EditorBuffer::getText() const {
   // TODO
   stringstream ss;
   EditorBuffer::Cell *mid = start->next;

   while(mid != start){
      ss << mid->ch;
      mid = mid->next;   
   }
   
   // cout << "Getting text" <<endl;
   return ss.str();
}

int EditorBuffer::getCursor() const {
   // TODO
   // ch of start is null, so start should never be delete and the cursor
   int ans = 0;
   EditorBuffer::Cell *mid = start;
   while(mid != cursor){
      ans++;
      mid = mid->next;
   }
   // cout << "getting cursor" << endl;
   return ans;
}

/* DO NOT modify the main() part */
int main(){
    string cmd;
    EditorBuffer buffer;
    while(getline(cin,cmd)){
        executeCommand(buffer, cmd);
    }        
    return 0;
}