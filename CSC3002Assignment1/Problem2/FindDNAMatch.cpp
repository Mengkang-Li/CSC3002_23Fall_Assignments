/* Q2: 
 * File: FindDNAMatch.cpp
 * ----------------------
 * This file solves the DNA matching exercise from the text.
 */
// header file for OJ system
// #include <iostream>
// #include <string>

// using namespace std;

#include <iostream>
#include <string>
//#include "CSC3002OJActive/assignment1/FindDNAMatch.h" //for OJ
#include "FindDNAMatch.h" //for local test
using namespace std;


/*
 * Function: findDNAMatch
 * Usage: int pos = findDNAMatch(s1, s2);
 *        int pos = findDNAMatch(s1, s2, start);
 * ---------------------------------------------
 * Returns the first index position at which strand s1 would bind to
 * the strand s2, or -1 if no such position exists.  If the start
 * parameter is supplied, the search begins at that index position.
 */

int findDNAMatch(string s1, string s2, int start) {
   // TODO
   s1 = matchingStrand(s1);
   for(int i = start; i < s2.size(); i++){
      if(s2[i] == s1[0]){
         int cnt = 0;
         while(cnt != s1.size() && s2[i + cnt] == s1[cnt]){
            cnt++;
         }
         if(cnt == s1.size()){
            return i;
         }
      }
   }
   return -1;
}

/*
 * Function: matchingStrand
 * Usage: string match = matchingStrand(strand);
 * ---------------------------------------------
 * Returns a string in which each base has been replaced by its
 * counterpart base (C <-> G and A <-> T).  Any other characters
 * are replaced by an X.
 */

string matchingStrand(string strand) {
   // TODO
   for(int i = 0; i < strand.size(); i++){
      switch (strand[i]){
         case 'C': strand[i] = 'G';break;
         case 'G': strand[i] = 'C';break;
         case 'A': strand[i] = 'T';break;
         case 'T': strand[i] = 'A';break;
         default: strand[i] = 'X';break;
      }
   }
   return strand;
}

/*
 * Function: findAllMatches
 * Usage: findAllMatches(s1, s2);
 * ------------------------------
 * Finds all positions at which s1 can bind to s2.
 */

void findAllMatches(string s1, string s2) {
   // TODO
   int cnt = 0;
   int record = 0;
   while(cnt < s2.size() && cnt != -1){
      int ans = findDNAMatch(s1, s2, cnt);
      if(ans != -1){
         cout << s1 << " matches " << s2 << " at position " << ans << endl;
         cnt = ans + 1;
         record = 1;
      }else{
         cnt = -1;
      }
   }
   if(record == 0){
      cout << s1 << " has no matches in " << s2 << endl;
   }
}

// DO NOT modify the main() function
/*
 * sample output:
 * input:  TTGCC TAACGGTACGTC
 * output: TTGCC matches TAACGGTACGTC at position 1
*/
int main(int argc, char* argv[]) {
    string s1, s2;
    cin >> s1 >> s2; 
    findAllMatches(s1, s2);
    return 0;
}
