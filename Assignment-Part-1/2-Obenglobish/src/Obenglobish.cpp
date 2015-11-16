#include <iostream>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

// Function prototypes
bool isVowel(char c);
int getConsonant (string s);
string obenglobish (string word);


int main() {
    while(true){
        string word = getLine ("Enter a word: ");

        if(word == "") break;
        string translation = obenglobish(word);
        /*display result */
        cout << word << " -> " << translation << endl;
    }
    return 0;
}

/**
 * @brief isVowel
 * @param c The character from the entered word, which we check vowel or not
 * @return True if the specified character is vowel
 */
bool isVowel(char c){
    if(c == 'a' || c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o'){
        return true;
    }else{
        return false;
    }
}

/**
 * @brief getConsonant
 * @param s The string, where we search the index of the first consonant
 * @return The index of the first consonant in the specified string
 */
int getConsonant(string s){
    int i = 0;
    while(i < s.length ()){
        if(!isVowel(s[i])){
            return i;
        }
        i++;
    }
    return i;
}

/**
 * @brief obenglobish
 * @param word The entered string which we convert with indicate parameters
 * @return The new string with indicate changes
 */
string obenglobish(string word){

    word = toLowerCase (word);
    for(int i = 0; i < word.length (); i++){
        char currLetter = word[i];

        if(isVowel(currLetter)){
            /*devide the world by 2 part*/
            string begin = word.substr (0, i);
            string next = word.substr(i + 1);

            /*Find first consonant in the rest of the string */
            int indexConsonant = getConsonant(next);
            string vowels = next.substr (0, indexConsonant);

            /*and create the new string from this consonant to the end to check vowel */
            string end = next.substr (indexConsonant);

            if(i < word.length () - 1 || currLetter != 'e'){
                /* Add the "ob" before each vowel, if the previous character isn't vowel
                 * or this vowel is last character and isn't 'e'
                 */
                return begin + "ob" + currLetter + vowels + obenglobish (end);
            }
        }
    }
    return word;
}

