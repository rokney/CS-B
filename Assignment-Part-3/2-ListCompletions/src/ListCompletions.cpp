/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the cell phone mind-reading problem
 * from Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "vector.h"

using namespace std;

/* Function prototypes */

void listCompletions(string digits, Lexicon & lex);
void createPrefexes(string  digits, Vector<string> & prefixes, string pref = "");
void createWords(string pref, Lexicon & lexicon);
string digitToPrefixe (char ch);

/* Main program */

int main() {
    Lexicon english("EnglishWords.dat");
    cout << "Cell phone mind-reading problem" << endl;
    while (true) {
        cout << "Enter a set of digits: ";
        string digits = getLine();
        if (digits == "" || digits == "quit") break;
        cout << "The words beginning with those digits are:" << endl;
        listCompletions(digits, english);
    }
    return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lexicon);
 * ----------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon & lexicon) {
    Vector<string> prefixes;
    createPrefexes(digits, prefixes);
    for(int i = 0; i < prefixes.size ();i++){
        string pref = prefixes[i];
        if(lexicon.containsPrefix (pref)){
            createWords(pref, lexicon);
        }
    }
}

void createPrefexes(string  digits, Vector<string> & prefixes, string pref){
    if(digits.length () == 0){
        prefixes.add(pref);
    }else{
        /*Temporary string to save the several letters, which mapped on current digit */
        string temp = digitToPrefixe (digits[0]);
        for(int i = 0; i <temp.length (); i++){
            /*Create all possibilities from current letters */
            createPrefexes(digits.substr (1), prefixes, pref + temp[i]);
        }
    }
}

/*
 * Convert all entered digit to string with letters, as they are mapped on the phone keypad
 */
string digitToPrefixe (char ch){
    switch (ch) {
    case '0': return ("0");
    case '1': return ("1");
    case '2': return ("abc");
    case '3': return ("def");
    case '4': return ("ghi");
    case '5': return ("jkl");
    case '6': return ("mno");
    case '7': return ("qprs");
    case '8': return ("tuv");
    case '9': return ("wxyz");
    default: cout << "Wrong digital" << endl;
    }
    return ("0");
}

void createWords(string pref, Lexicon &lexicon){
    if(lexicon.contains (pref)){
        cout << pref << endl;
    }
    /*Add each letter from alphabet to find new word */
    for(char c = 'a'; c <= 'z'; c++){
        if(lexicon.containsPrefix (pref + c)){
            createWords (pref + c, lexicon);
        }
    }
}
