#include <iostream>
#include "simpio.h"
#include "console.h"
#include <fstream>
#include "tokenscanner.h"
#include "vector.h"
#include "string.h"
using namespace std;

/*Function prototypes */
bool isVowel(char c);
int syllablesInWords (string & word);
void wordsInSentences (string & word);
void readFile(Vector<string> & fileContent);
double calculateGradeLevel ();
void displayInfo (double grade);

bool displayDebug = false;
int wordCount = 0;
int syllableCount = 0;
int sentencesCount = 0;


int main() {
    displayDebug = getYesOrNo ("Display debug information?: ");
    Vector<string> fileContent;
    readFile(fileContent);

    for(int i=0; i < fileContent.size (); i++){
        wordsInSentences (fileContent[i]);
    }

    displayInfo(calculateGradeLevel());

    return 0;
}

/**
 * @brief readFile Ask the user for name of the input file,
 * put the tokens from it with indicate parameters and add it as string into the list(vector)
 * @return The list with strings from the input file
 */
void readFile(Vector<string> & list){

    while(true){
        string nameFile = getLine("Enter the file name: ");
        ifstream file(nameFile);
        if(file.fail()){
            cout << "Try again..." << endl;
        }else{
            TokenScanner scanner;
            scanner.setInput (file);
            scanner.ignoreWhitespace ();
            /*Check for apostrophe in the word */
            scanner.addWordCharacters ("'");
            while(scanner.hasMoreTokens ()){
                string token = scanner.nextToken ();
                list.add(toLowerCase(token));
            }
            break;
        }
    }
}

/**
 * @brief isVowel
 * @param c The character of the word to check vowel or not
 * @return True if the character is vowel
 */
bool isVowel(char c){
    if(c == 'a' || c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o'){
        return true;
    }else{
        return false;
    }
}

/**
 * @brief syllablesInWords Count the number of syllables in spacified word
 * @param word The word from the input file
 * @return The number of the syllables in specified word
 */
int syllablesInWords(string & word){
    int count = 0;
    char lastLetter = word[word.length() - 1];

    /*Count syllables with indicate parameters */
    for(int i = 0; i < word.length() - 1; i++){
        char currLetter = word[i];
        char nextLetter = word[i+1];
        if(isVowel(currLetter) && !isVowel (nextLetter)){
            count++;
        }
    }
    if(isVowel(lastLetter) && lastLetter != 'e'){
        count++;
    }else if(lastLetter == 'e'){
        if(isVowel(word[word.length ()-2]) ||
                (word[word.length ()-2]) == 'l' && (word[word.length () - 3] != 'l') && !isVowel(word[word.length ()-3])){
            count++;
        }
    }
    if(count == 0){
        /*Every word has at least one syllable */
        count = 1;
    }
    return count;
}

/**
 * @brief wordsInSentences Check the each token from the input file for word or punctuation mark.
 * Count all words, syllable in current word, and punctuation marks, which mean the end of the sentences.
 * @param word The token string from the input file.
 */
void wordsInSentences(string & word){
    char firstLetter = word[0];
    if(isalpha(firstLetter) || (firstLetter == '\'' && isalpha(word[1]))){
        wordCount++;
        /*Count syllables in current word */
        syllableCount += syllablesInWords (word);
        if(displayDebug){
            cout << "Token: " << "[" << word << "]" << " -> (word, syllable " << syllablesInWords (word)<< ");" << endl;
        }
    }else if(firstLetter == '.' || firstLetter == '!' || firstLetter == '?'){
        /*Count the sentences with specified punctuation marks */
        sentencesCount++;
        if(displayDebug){
            cout << "Token: " << "[" << word << "]" << " -> (sentence);" << endl;
        }
    }else{
        if(displayDebug){
            cout <<  "Token: " << "[" << word << "]" << endl;
        }
    }
}

/**
 * @brief calculateGradeLevel Calculate the grade level with spacified formula
 * @return The value of the grade level
 */
double calculateGradeLevel (){
    double c0 = -15.59;
    double c1 = 0.39;
    double c2 = 11.8;
    return c0 + c1*wordCount/sentencesCount + c2*syllableCount/wordCount;
}

/**
 * @brief displayInfo Display the result of program
 * @param grade The value of the calculated grade level
 */
void displayInfo(double grade){
    cout <<"Words: " << wordCount << endl;
    cout <<"Syllable: " << syllableCount << endl;
    cout <<"Sentences: " << sentencesCount << endl;
    cout <<"GradeLevel: " << grade << endl;
}

