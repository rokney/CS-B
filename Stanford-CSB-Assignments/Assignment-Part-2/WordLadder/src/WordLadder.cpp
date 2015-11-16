/*
 * File: WordLadder.cpp
 * --------------------
 * Name: aotyan
 * Section: asignment2
 * This file is the project for the word ladder problem
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

/* display the shortest word ladder */
void display(Vector<string> ladder){
    copy(ladder.begin (), ladder.end ()-1, ostream_iterator<string>(cout, " -> "));
    cout << ladder[ladder.size () - 1] << endl;
}


/*Check the entered words with specified parameters. Convert them to lower case */
void readWords(string & firstWord, string & secondWord, Lexicon & lexicon){
    string quit = "RETURN";
    firstWord = getLine("Enter start word (RETURN to exit): ");
    if(firstWord == "" || !lexicon.contains (firstWord)){
        cout << "You entered not valid word. Try again..." << endl;
    } else if (firstWord == quit){
        exit(0);
    }
    firstWord = toLowerCase (firstWord);
    secondWord = toLowerCase (getLine ("Enter destination word: "));
    if(secondWord == "" || !lexicon.contains (secondWord)){
        cout << "You entered not valid word. Try again..." << endl;
    } else if (secondWord.length () != firstWord.length ()){
        cout << "The length of both words must be the same. Try again...";
    }
}

/*Add the first input word as first ladder in our future list*/
void createFirstLadder (Queue<Vector<string>> & list, string & firstWord){
    Vector<string> word;
    word.add(firstWord);
    list.add(word);
}


/* Change the current word by one letter to create new true word.
 * Copy last ladder into new, and add new word to it.
 */
void createNextLadder(string &currentWord, Vector<string>& firstLadder, Lexicon& usedWords, Queue<Vector<string>>& result, Lexicon& english){
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
