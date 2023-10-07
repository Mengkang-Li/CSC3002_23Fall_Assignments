/* P2
 * File: MorseCode.cpp
 * -------------------
 * This program translates to and from Morse Code using maps to
 * assist in the translation.
 */

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <queue>
//#include "CSC3002OJActive/assignment2/lib.h" // For OJ test
//#include "CSC3002OJActive/assignment2/MorseCode.h" // For OJ test
#include "lib.h"
#include "MorseCode.h" // For local test
using namespace std;

queue<string> split(string line){
   istringstream iss(line);
   string mid;
   queue<string> q;
   while(getline(iss, mid, ' ')){
      q.push(mid);
   }
   return q;
}

/*
 * TODO function
 * Function: translateLettersToMorse
 * Usage: string morse = translateLettersToMorse(line);
 * ----------------------------------------------------
 * Translates a string of letters into Morse Code characters separated
 * by spaces.  Characters that don't appear in the table are simply ignored.
 */

string translateLettersToMorse(string line) {
   // TODO
   queue<string> q;
   ostringstream oss;
   map<string, string> m = createMorseCodeMap();
   for(int i = 0; i < line.size(); i++){
      // char mid[1]; // 使用这种方法转换会导致内存泄漏
      q.push(string(1, line[i]));
   }
   while(!q.empty()){
      string str = q.front();
      q.pop();
      oss << m[str];
      if(q.size() != 0){
         oss << " ";
      }
   }
   string ans = oss.str();
   return ans;
}

/*
 * TODO function
 * Function: translateMorseToLetters
 * Usage: string letters = translateLettersToMorse(line);
 * ------------------------------------------------------
 * Translates a string in Morse Code into English letters.
 * Because word breaks are not represented in Morse code, the
 * letters in the output will be run together.  The characters
 * of the Morse Code input must be separated by a single space.
 * Any other character in the input is simply ignored.  If there
 * is no English equivalent for the Morse Code character, this
 * function indicates that fact by inserting a question mark (?).
 *
 * Implementation note: To eliminate the special case of the last
 * character in the line, this function begins by adding a space
 * to the end of the input string.
 */

string translateMorseToLetters(string line) {
   // TODO
   map<string, string> m = invertMap(createMorseCodeMap());
   queue<string> q = split(line);
   ostringstream oss;
   while(!q.empty()){
      string mid = q.front();
      q.pop();
      oss << m[mid];
   }
   return oss.str();
}

/*
 * Function: createMorseCodeMap
 * Usage: map<string> map = createMorseCodeMap();
 * ----------------------------------------------
 * Returns a map in which each uppercase letter is mapped into its
 * Morse code equivalent.
 */

map<string,string> createMorseCodeMap() {
   map<string,string> map;
   map["A"] = ".-";
   map["B"] = "-...";
   map["C"] = "-.-.";
   map["D"] = "-..";
   map["E"] = ".";
   map["F"] = "..-.";
   map["G"] = "--.";
   map["H"] = "....";
   map["I"] = "..";
   map["J"] = ".---";
   map["K"] = "-.-";
   map["L"] = ".-..";
   map["M"] = "--";
   map["N"] = "-.";
   map["O"] = "---";
   map["P"] = ".--.";
   map["Q"] = "--.-";
   map["R"] = ".-.";
   map["S"] = "...";
   map["T"] = "-";
   map["U"] = "..-";
   map["V"] = "...-";
   map["W"] = ".--";
   map["X"] = "-..-";
   map["Y"] = "-.--";
   map["Z"] = "--..";
   return map;
}

/*
 * TODO function
 * Function: invertMap
 * Usage: map<string> inverse = invertMap(map);
 * --------------------------------------------
 * Creates an inverted copy of the specified map in which the values
 * in the original become the keys of the new map and refer back to
 * their associated keys.  Thus, if "abc" is bound to "xyz" in the
 * original map, the inverted map will bind "xyz" to "abc".  If two
 * keys in the original map have the same value, this function will
 * signal an error condition.
 */

map<string,string> invertMap(const map<string,string> & m) {
   // TODO
   map<string, string> ans;
   for(auto it = m.begin(); it != m.end(); it++){
      string key = it -> second;
      string val = it -> first;
      ans.emplace(key, val);
   }
   return ans;
}

int main() {
    /* A sample translator:
     *                     > SOS
     *                     ... --- ...
     *                     > ... --- ...
     *                     SOS
     */
    string line;
    
    while (getline(cin, line) && line.length() > 0) {
       line = toUpperCase(line);
       if (line[0] == '.' || line[0] == '-') {
           cout << translateMorseToLetters(line) << endl;
       } else {
           cout << translateLettersToMorse(line) << endl;
       }
    }
    return 0;
   
}

