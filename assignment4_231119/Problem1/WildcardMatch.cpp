/* P1:
 * File: WildcardMatch.cpp
 * -----------------------
 * This program tests the wildcardMatch method, which
 * matches a filename against a pattern containing the wildcard
 * characters * and ?.
 */

#include <iostream>
#include <string>
// #include "CSC3002OJActive/assignment4/WildcardMatch.h" //for OJ test
#include "WildcardMatch.h" // for local test
using namespace std;

/*
 * Method: wildcardMatch
 * Usage: if (wildcardMatch(filename, pattern)) . . .
 * --------------------------------------------------
 * This method checks to see whether filename matches the pattern,
 * which consists of three types of characters:
 *
 * 1. The character ?, which matches any single character
 * 2. The character *, which matches any string of characters
 * 3. Any other character, which matches only that character
 */
bool wildcardMatch(string filename, string pattern) {
   //TODO
   // use pointers to set positions of the pattern and filename
   // consider situation of *?.*  
   // 考虑*可以匹配多个字符 那么就遍历匹配每个字符串 碰到*先不管 若是后续比对不同了再返回 然后用*替代一个 然后替代n个
   int cfn = 0;
   int cp = 0;
   bool ans = false;
   while(cp < pattern.size()){
      if(pattern[cp] != '*'){
         if(cfn >= filename.size()){
            return false;
         }else{
            if(pattern[cp] != '?' && pattern[cp] != filename[cfn]){
               return false;
            }else{
               cp++;
               cfn++;
            }
         }
      }else{
         // if it's *, try every possibility

         // case dw ??*
         if(cfn >= filename.size()){
            for(int x = cp; x < pattern.size(); x++){
               if(pattern[x] != '*'){
                  return false;
               }
            }
            return true;
         }
         bool cont = false;
         for(int i = cfn; i < filename.size(); i++){
            int j = cp + 1;
            // case dawjkldjkla ??* 直接return true
            if(j >= pattern.size()){
               return true;
            }
            int mid = i;
            while(j < pattern.size() && pattern[j] != '*'){
               
               if(pattern[j] != '?' && filename[mid] != pattern[j]){
                  break;
               }else{
                  if(mid >= filename.size() || j >= pattern.size()){
                     return false;
                  }
                  j++;
                  mid++;
                  
               }
               // 结束条件分两种 一种是这是最后一个*，即i和j都等于边界值；另一种是成功遇到下一个*号了，此时也可以继续
               if(mid == filename.size() && j == pattern.size()){
                  return true;
               }  
            }
            if(pattern[j] == '*'){
                  cont = true;
                  cp = j;
                  cfn = mid;
               }
            if(cont){
               break;
            }
         }
         // 如果都没有匹配 那么直接return false
         if(!cont){
            return false;
         }
      }

   }
   return cfn == filename.size() && cp == pattern.size();
}

/*
There are three kinds of characters. I should use the string as an array. 
1. If it's "*", then try to find ".".
2. If it's ".", then find the substring after the ".".
3. If it's "?", then check a single word, get the substring of the filename.
*/


/* DO NOT modify the main() part */

int main() {
   string in_pair, filename, pattern;
   bool matchResult;
   while(getline(cin,in_pair)){
      int sp = in_pair.find(' ');
      filename = in_pair.substr(0, sp);
      pattern = in_pair.substr(sp+1, in_pair.size());
      matchResult = wildcardMatch(filename, pattern);
      cout << boolalpha  << matchResult << endl;
    }
   return 0;
}

