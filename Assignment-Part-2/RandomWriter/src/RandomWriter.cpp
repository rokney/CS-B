/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: aotian
 * Section: CS-B
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* Constant defines the number of sumbols to display */
const int COUNT_CHARS = 2000;

/*All seeds with list of next characters */
Map<string, Vector<char>> mapTextChars;

/*All seeds to count the most common */
Vector<string> allSeeds;

/*Get random character from the list of characters */
char getRandomChar(Vector<char> ch){
    int size = ch.size();
    if(size != 0){
        int rand = randomInteger (0, size - 1);
        return ch[rand];
    }
    return 0;
}

/*We have the most common seed and we can create the random text */
void createRandomText(string & popularSeed){
    /*At first, display the most common seed */
    string result = popularSeed;
    for(int i = 0; i < COUNT_CHARS; i++){
        Vector<char> ch;
        if(mapTextChars.containsKey (popularSeed)){
            ch = mapTextChars.get (popularSeed);
        }else{
            break;
        }
        /*get random character from the vector of next characters */
        char c = getRandomChar(ch);
        result += c;
        /*Delete first character fom seed and add next to create new seed */
        popularSeed.erase (0,1);
        popularSeed += c;
    }
    cout<<result<<endl;
}

/*Find the most popular common seed */
string getMaxPopularSeed(Map<string, int> & mapCounterSeed){
    int max = 0;
    string maxPopSeed;
    for(string str : mapCounterSeed){
        if(mapCounterSeed[str] > max){
            max = mapCounterSeed[str];
            maxPopSeed = str;
        }
    }
    return maxPopSeed;
}

/*Count all common seeds */
string counterSeed(){
    Map<string, int> mapCounterSeed;
    int count = 0;
    for(int i = 0; i < allSeeds.size (); i++){
        if(mapCounterSeed.containsKey (allSeeds[i])){
            count = mapCounterSeed.get(allSeeds[i]);
            count++;
            mapCounterSeed.add(allSeeds[i], count);
        }else{
            mapCounterSeed.add(allSeeds[i], 1);
        }
    }
    return getMaxPopularSeed(mapCounterSeed);
}

/*Create the map of seeds and vector with next characters */
void createMapTextChars(string & text, int & rank){
    for(int i = 0; i < text.length () - rank; i++){
        string seed = text.substr(i, rank);
        allSeeds.add(seed);
        if((i + rank) < text.length ()){
            Vector<char> nextChar;
            /*find next char after the seed */
            char c = text[i + rank];
            /*check for seed */
            if(mapTextChars.containsKey (seed)){
                nextChar = mapTextChars.get (seed);
                nextChar.add(c);
                mapTextChars.add(seed, nextChar);
            }else{
                nextChar.add(c);
                mapTextChars.add(seed, nextChar);
            }
        }
    }
}

/*Reed file and save each character to string */
void parseText(ifstream & file, int & rank){
    char c;
    string text;
    while(file.get (c)){
        text += c;
    }
    createMapTextChars(text, rank);
}

int main() {
    while(true){
        string nameFile  = getLine("Enter the file name: ");
        ifstream file(nameFile);
        if(file.fail()){
            cout << "You entered not valid file name. Try again." << endl;
        }else{
            int rank = getInteger ("Enter Makarov index: ");
            parseText(file, rank);
            string popularSeed = counterSeed();
            createRandomText(popularSeed);

            /*Clear all containers */
            mapTextChars.clear ();
            allSeeds.clear ();
            file.close ();
        }
    }
    return 0;
}
