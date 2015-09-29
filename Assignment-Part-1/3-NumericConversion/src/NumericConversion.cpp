#include <iostream>
#include <string>
#include "console.h"
using namespace std;

// Function prototypes
string intToString(int n);
int stringToInt(string str);
char convertIntToChar(int n);
int convertCharToInt(char c);


int main() {
    cout << "Release function intToString: " << endl;

    /*The array of integer numbers for test intToString function */
    int numbers [5]  = {12345, 54321, 0, -999999, 4687234};
    for(int i = 0; i < 5; i++){
        string str = intToString (numbers[i]);
        cout << numbers[i] << " -> " << "\"" <<str << "\";" << endl;
    }

    cout << endl;

    cout << "Release function stringToInt: " << endl;

    /*The array of strings of numbers for test stringToInt function */
    string nums [5] = {"12345", "54321", "0", "-99999", "4687234"};
    for(int i = 0; i < 5; i++){
        int n = stringToInt (nums[i]);
        cout << "\"" << nums[i] << "\" -> " << n << ";" << endl;
    }
    return 0;
}

/**
 * @brief intToString
 * @param n The number need to convert into string
 * @return The string with numbers which we convert
 */
string intToString (int n){
    if(n == 0) {
        return "0";
    }
    if(n < 0 ){
        return "-" + intToString (abs(n));
    }
    if(n < 10){
        /*If it is ultimate character of the number, return it */
        return string() + convertIntToChar (n);
    }else{
        /*Put the last character of the number to the font of the string, then convert the rest of integer*/
        return intToString (n/10) + (string() + convertIntToChar (n%10));
    }
}

/**
 * @brief convertIntToChar
 * @param n The integer need convert to char
 * @return The char contains entered integer
 */
char convertIntToChar(int n){
    return (char)(n + '0');
}

/**
 * @brief stringToInt
 * @param srt The srting of numbers need to convert into integer
 * @return The integer with numbers from the entered string
 */
int stringToInt (string srt){
    int size = srt.length ();
    if(size == 1){
        return convertCharToInt(srt[0]);
    } else if(size > 1 && srt[0] == '-'){
        return (-1)*stringToInt (srt.substr (1));
    } else{
        /*Put each last character from the string and convert it into integer */
        return 10*stringToInt (srt.substr (0,size - 1)) + convertCharToInt(srt[size - 1]);
    }
}

/**
 * @brief convertCharToInt
 * @param c The char need to convert to integer
 * @return  The integer coontains the entered char with number
 */
int convertCharToInt(char c){
    return (int)(c - '0');
}


