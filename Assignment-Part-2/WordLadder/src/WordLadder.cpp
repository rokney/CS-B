/*
 * File: WordLadder.cpp
 * --------------------
 * Name: aotyan
 * Section: asignment2
 * This file is the project for the word ladder problem
 * on Assignment #2.
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;


void display(Vector<string> ladder){
    /* display the shortest word ladder */
    copy(ladder.begin (), ladder.end ()-1, ostream_iterator<string>(cout, " -> "));
    cout << ladder[ladder.size () - 1] << endl;
}

void readWords(string & fword, string & sword, Lexicon & lexicon){
    /*Check the entered words with specified parameters. Convert them to lower case */
    string quit = "RETURN";
    fword = getLine("Enter start word (RETURN to exit): ");
    if(fword == "" || !lexicon.contains (fword)){
        cout << "You entered not valid word. Try again..." << endl;
    } else if (fword == quit){
        exit(0);
    }
    fword = toLowerCase (fword);
    sword = toLowerCase (getLine ("Enter destination word: "));
    if(sword == "" || !lexicon.contains (sword)){
        cout << "You entered not valid word. Try again..." << endl;
    } else if (sword.length () != fword.length ()){
        cout << "The length of both words must be the same. Try again...";
    }
}

void createFirstLadder (Queue<Vector<string>> & list, string & fword){
    Vector<string> word;
    word.add(fword);
    list.add(word);
}

void createNextLadder(string &currentWord, Vector<string>& firstLadder, Lexicon& usedWords, Queue<Vector<string>>& result, Lexicon& english){
    /* Change the current word by one letter to create new true word.
     * Copy last ladder into new, and add new word to it.
     */
    for(int i = 0; i < currentWord.length (); i++){
        for(char c = 'a'; c <= 'z'; c++){
            if(currentWord[i] != c){
                string newWord = currentWord;
                newWord[i] = c;
                if(english.contains (newWord) && !usedWords.contains (newWord)){
                    Vector<string> nextLadder = firstLadder;
                    nextLadder.add(newWord);
                    result.enqueue (nextLadder);
                }
            }
        }
    }
}

int main() {
    Lexicon english ("EnglishWords.dat");
    Lexicon usedWords; // need to check the unique word
    Queue<Vector<string>> result;
    string firstWord, secondWord;
    while(true){
        readWords (firstWord, secondWord, english);
        createFirstLadder(result, firstWord);
        usedWords.add(firstWord);
        while(!result.isEmpty ()){
            Vector<string> firstLadder = result.dequeue ();
            if(firstLadder.get (firstLadder.size () - 1) == secondWord){
                display(firstLadder);
                result.clear();
                usedWords.clear ();
                break;
            }
            string currentWord = firstLadder.get(firstLadder.size ()-1);
            usedWords.add(currentWord);
            createNextLadder(currentWord, firstLadder, usedWords, result, english);
        }
        /* If the ladder of the two entered words is impossible */
        if(!usedWords.isEmpty ()){
            cout << "Sorry, this ladder is impossible..." << endl;
        }
    }
    return 0;
}
