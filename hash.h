#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] {0,0,0,0,0};
        //sub divide k into 5 strings kind of
        unsigned long long a[6]={0,0,0,0,0,0};
        int aTracker = 5;
        int wTracker = 4;
        for(int i = (int)k.size()-1; i >=0;  i--){
          //std::cout << i << std::endl;
            a[aTracker] = letterDigitToNumber(k[i]);
            if(aTracker == 0){
                //do conversion of a to add to w;
                w[wTracker]= ((((((a[0])*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]);
                wTracker--;
                aTracker = 5;
                //wipe a clean for the next substring of 6
                for(int j = 0; j < 6; j++){
                    a[j]=0;
                }
            }else{
                aTracker--;
            }
            
        }
        if(aTracker !=5){
            //do the final w input i think;
            w[wTracker]= ((((((a[0])*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]);
            wTracker--;
        }
        HASH_INDEX_T hashNumber= 0;
        for(int i = 0; i < 5; i++){
            hashNumber += (rValues[i]*w[i]);
        }
        return hashNumber;
        //will test this later or tomorrow, remember to do in codio
        //because i didn't want to bother with testing, since its not in github
        //ALSO remember to add a conversion to lowercase for uppercae letters
        //although i think that might be possible to avoid using 
        //letter >= 'A' && letter <= 'Z', but conversion might be easier
        

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //just in case, may want to switch from casting from int to hash_index_t, may not be necessary though
        //for now assuming a letter is lowercase
        if(letter >= 'a' && letter <= 'z'){
            //ascii value for a = 97
            return (int)letter - 97;
        }else if(letter >= '0' && letter <= '9'){
            //ascii value for 0 = 48
            return 26 + (int)letter-48;
        }else{
            //ascii value for A = 65
            return (int)letter - 65;
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
