#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//function declarations
void boundCorrect(int* x, int* a, int* b);
void generateRandom(int arr[], int x, int a, int b);
void generateRandomV2(int arr[],int x, int a, int b);
void generateRandomV3(int arr[],int x, int a, int b);
void repeatRandom(int arr[],int x, int a, int b);
void printRandom(int arr[], int x, int a, int b);
bool checkUnique(int arr[], int x);


int main()
{
    int x=4,a=1,b=4;

    /*cout << "Enter the number of unique random values required:\n> ";
    cin >> x;
    cout << "Enter the lower bound:\n> ";
    cin >> a;
    cout << "Enter the upper bound:     (must be greater than or equal to "<<x+a-1<<")\n> ";
    cin >> b;*/

    boundCorrect(&x,&a,&b); //fixes bounds if given in wrong order, or if x is too small

    int values[x]={};

    generateRandomV2(values,x,a,b); //saves randomly-generated numbers to an array. No two entries will be alike.
    printRandom(values,x,a,b); //prints all random numbers to cout

    cout << "Order is Jory, James, Akash, Sailosi"<<endl;

    return 0;
}

//function definitions

void boundCorrect(int* x, int* a, int* b){
    if (*a>*b) {
        int c=*a;
        *a=*b;
        *b=c;
        cout << "\nYou have given the upper and lower bounds in the wrong order.\nThe bounds have been re-assigned.\n";
        cout << "New Lower bound: "<<*a<<"       New upper bound: "<<*b<<endl;
    }   //fixes bounds if given in wrong order
    if(*x>*b-*a+1){
        cout << "\nThe given upper bound is too low to generate "<<*x<<" values, with a lower bound of "<<*a<<".\n;";
        cout << "The upper bound has been reset to the minimum value of "<<*x+*a-1<<".\n";
        *b=*x+*a-1;
    }   //fixes upper bound if it is too low
}
void generateRandomV3(int arr[],int x, int a, int b){
    srand(time(NULL));
    int index;
    /*int listsize=b-a+1;*/
    int posvals[b-a+1];
    for(int i=0; i<(b-a+1); i++){
        posvals[i]=a+i;        //creates an array of all possible values within given bounds, listed in numerical order.
    }
    /*cout << "Value list created. Possible values are: ";      //This code is used to print the current list of possible values
    for(int i=0; i<listsize; i++) {cout <<posvals[i]<<",";}     //Used for diagnostics
    cout<<endl;*/
    for(int i=0; i<x; i++){
        cout << "\nGenerating random index from 0 to "<<b-a<<endl;
        index=rand()%(b-a+1);           //takes a random entry from the array of possible values
        cout << "Assigning "<<index+1<<"th value in value list\n";
        arr[i]=posvals[index];          //assigns value to the list of random numbers to be the output
        cout << "Assigning value "<<arr[i]<<endl;
        for(index; index<b-a && i<x-1; index++){
            posvals[index]=posvals[index+1];    //The random array entry is overwritten by the one behind it. All array entries
        }                                       //'move up' a spot.
        posvals[b-a]=0;                         //The last entry is rewritten as 0, since there is nothing behind it.
        /*cout << "\nValue list updated. Possible values are: ";
        for(int j=0; j<listsize; j++) {cout <<posvals[j]<<",";}
        cout<<endl;*/
        b--;    //This effectively truncates the last value of the array, by reducing the maximum possible index
    }           //that will be generated.
}

void generateRandomV2(int arr[],int x, int a, int b){
    srand(time(NULL));
    bool history[b-a+1]={}; //contains a bool variable for every possible value of each random number. All initially set to 0.
    for(int i=0;i<x;i++){
        cout << "\nValue assignment " << i+1 <<endl;
        while(true){
            arr[i]=rand()%(b-a+1)+a;    //generates a value for each random number
            cout << "Trying Value " << arr[i] <<endl;
            if(history[arr[i]-a]==false) {  //check state of bool variable for the value generated.
                history[arr[i]-a]=true;     //If false, value can be used. Then sets state to true, and exits loop.
                break;                      //If true, value has already been used. Will cause while loop to repeat, will generate a new value to try.
            }
        }
    }
}
/*This method is far quicker than V1, as each value only requires one check to confirm whether the value has been
previously used. However, the program always generates new values randomly, so if only a few available values are left,
it can take a while to randomly generate one of the those values.*/

void generateRandom(int arr[], int x, int a, int b) {
    srand(time(NULL));
    bool repeatVal=false;
    for(int i=0; i<x; i++) {
        arr[i]=rand()%(b-a+1)+a;
        cout << "\nValue assignment " << i+1 << endl; //generates a value for each entry in the array
        do {
            repeatVal=false;
            for(int j=0; j<i; j++) {                 //checks each new value against every previous one
                cout << "checking against value " << j+1 << endl;
                if(arr[i]==arr[j]) {
                    arr[i]=rand()%(b-a+1)+a;     //where a new value matches a previous value, new value is reassigned
                    repeatVal=true;                   //this causes loop to repeat, and then check the (reassigned) new value against previous values
                    cout<< "Repeated Value.\nFinding alternate value" << endl;
                    break; //breaks 'for' loop once a value has matched, so (reassigned) new value can be checked again.
                }
            }
        }while(repeatVal==true); //if repeatVal==false here, then no matches were found for the new value. Program keeps the new value, and moves to next entry in array
    }
}
/*This method takes a long time to run.
It relies on a large number of checks to confirm that any new value has not been previously used.
This increases the run time, especially when x is large.*/

void repeatRandom(int arr[], int x, int a, int b){
    srand(time(NULL));
    for(int i=0;i<x;i++){
        arr[i]=rand()%(b-a+1)+a;       //fills array with random numbers. Does not check for repeated values.
    }
}

void printRandom(int arr[], int x, int a, int b) {
    cout << "\nYou have requested a list of "<< x << " random numbers from "<< a <<" to "<< b <<".\n\nThe numbers are:" << endl;
    for(int i=0; i<x; i++) {
        cout << arr[i] << endl;     //prints all values; one line per value.
    }
    cout << "\nHope you like them :)\n\n\n";
}

bool checkUnique(int arr[], int x){
    int ul=0,ll=0;
    for(int i=0;i<x;i++){
        if(arr[i]>ul) ul=arr[i];
        if(arr[i]<ll) ll=arr[i];
    }       //finds the upper and lower limits (ul and ll respectively) for the values in the array

    bool history[ul-ll+1]={}; //contains a bool variable for every possible value of each random number. All initially set to 0.
    for(int i=0;i<x;i++){
        cout << "Checking value " << i+1 <<endl;
        if(history[arr[i]-ll]==true) {
            cout << "\nThe value "<<arr[i]<<" is repeated.\n\n";
            return false;   //Will run if a value has been used before. Will return false.
        }
        if(history[arr[i]-ll]==false) history[arr[i]-ll]=true;     //Will run if a value has not been used before
    }
    cout << "\nAll values are unique.\n\n";
    return true;    //Will return true if no value has been repeated
}
