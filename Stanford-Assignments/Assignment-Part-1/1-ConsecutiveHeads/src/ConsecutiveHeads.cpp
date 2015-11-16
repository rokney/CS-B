#include <iostream>
#include <string>
#include "console.h"
#include "random.h"

using namespace std;

//Function prototypes
bool isHeads();
void getFlips( int & countFlips, int count = 0);


int main() {
    //set start number of flips = 0
    int countFlips = 0;

    getFlips(countFlips);

    /*display result */
    cout << "It took " << countFlips << " flips to get 3 consecutive heads" << endl;
    return 0;
}

/**
 * @brief isHeads
 * @return True if heads are tossed in current flip
 */
bool isHeads(){
    if(randomBool()){
        cout << "Heads" << endl;
        return true;
    }else{
        cout << "Tails" << endl;
        return false;
    }
}

/**
 * @brief getFlips
 * @param count This counter is a coin toss when it has three consecutive heads
 * @param flips The counter of total coin toss
 * @return The number of flips needed to get three consecutive heads toss
 */
void getFlips(int & countFlips, int count ){
    if(count < 3){
        count = (isHeads()) ? ++count : 0;
        countFlips++;
        getFlips(countFlips, count);
    }
}
