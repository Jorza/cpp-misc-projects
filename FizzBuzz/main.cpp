#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    //Setup
    int vsize=2;    //Set number of conditions for replacement
    int vals[vsize]={3,5};      //Set the numbers whose multiples will be replaced
    string words[vsize]={"Fizz","Buzz"};    //Set the words to appear when the corresponding number is replaced


    //Program
    for(int i=1;i<=100;i++){    //Iterates through all numbers from 1 to 100
        stringstream sstream;
        string output = "";
        bool skip=0;

        for(int j=0;j<vsize;j++){
            if(i%vals[j]==0){           //if the current number being tested is a multiple of an entry in 'vals'...
                sstream << words[j];    //The corresponding entry in 'words' is saved to sstream
                skip++;     //This prevents the number also being printed
            }
        }

        if(!(skip)) sstream << i;   //If the number is not replaced, will save the number to be printed

        sstream >> output;
        cout << output << endl; //Prints the number or word that has been saved
    }
}
