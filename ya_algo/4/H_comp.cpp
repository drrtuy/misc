#include <iostream>
#include <string>
#include <unordered_map>
 
int main() {
 
   std::string first_word, second_word;
   std::unordered_map<char, char> dict;
   std::unordered_map<char, char> dict2;
 
   std::cin >> first_word >> second_word;
 
   if (first_word.size() != second_word.size()) {
      std::cout << "NO";
      return 0;
   }
 
   for (size_t i = 0; i < first_word.size(); ++i) {
 
      if (dict.count(first_word[i]) != 0 && dict[first_word[i]] != second_word[i]) {
         std::cout << "NO";
         return 0;
      } else if (dict2.count(second_word[i]) != 0 && dict2[second_word[i]] != first_word[i]) {
         std::cout << "NO";
         return 0;
      } else
        {
            dict[first_word[i]] = second_word[i];
            dict2[second_word[i]] = first_word[i];
        }
 
   }
 
   std::cout << "YES";
 
   return 0;
}
