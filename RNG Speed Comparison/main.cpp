#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void generateRandomV2(int arr[],int x, int a, int b);
void generateRandomV3(int arr[],int x, int a, int b);
double recordV2(int x,int a,int b);
double recordV3(int x,int a,int b);

int main()
{
    ofstream DataV2 ("RNG_Speedtest_Data_V2.txt",ios::trunc);
    ofstream DataV3 ("RNG_Speedtest_Data_V3.txt",ios::trunc);

    if(!(DataV2.is_open()) || !(DataV3.is_open())){
        cout << "Error: A file could not be opened." <<endl;
        return 1;
    }

    int lim=4000, inc=10;

    DataV2 << "x values printed across horizontal axis, b values printed down vertical axis"<<endl;
    DataV3 << "x values printed across horizontal axis, b values printed down vertical axis"<<endl;
    DataV2 << "b,x\t1\t";
    DataV3 << "b,x\t1\t";
    for(int i=inc;i<lim;i+=inc){
        DataV2 <<i<<"\t";
        DataV3 <<i<<"\t";
    }
    DataV2 << lim <<endl;
    DataV3 << lim <<endl;

    int x=1,a=1,b=1;

    cout << "Currently testing x="<<x<<" b="<<b<<endl;
    DataV2 <<b<<"\t"<< recordV2(x,a,b)<<"\n";
    DataV3 <<b<<"\t"<< recordV3(x,a,b)<<"\n";
    for(b=inc;b<=lim;b+=inc){
        x=1;
        cout << "Currently testing x="<<x<<" b="<<b<<endl;
        DataV2 <<b<<"\t"<< recordV2(x,a,b)<<"\t";
        DataV3 <<b<<"\t"<< recordV3(x,a,b)<<"\t";
        for(x=inc;x<=lim && x<=b-a+1;x+=inc){
            //cout << "Currently testing x="<<x<<" b="<<b<<endl;
            DataV2 << recordV2(x,a,b);
            DataV3 << recordV3(x,a,b);
            if(x<b-a+1){
                DataV2 << "\t";
                DataV3 << "\t";
            }
            else if(x=b-a+1){
                DataV2 << endl;
                DataV3 << endl;
            }
        }
    }

    DataV2.close();
    DataV3.close();
    return 0;
}

double recordV2(int x,int a,int b){
    double tstart;
    double telapsed;
    int values[x];
    tstart=clock();
    for(int i=0;i<1000;i++){
        generateRandomV2(values,x,a,b);
    }
    telapsed=(clock()-tstart)/CLOCKS_PER_SEC;
    return telapsed;
}

double recordV3(int x,int a,int b){
    double tstart;
    double telapsed;
    int values[x];
    tstart=clock();
    for(int i=0;i<1000;i++){
        generateRandomV3(values,x,a,b);
    }
    telapsed=(clock()-tstart)/CLOCKS_PER_SEC;
    return telapsed;
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
        //cout << "\nGenerating random index from 0 to "<<b-a<<endl;
        index=rand()%(b-a+1);           //takes a random entry from the array of possible values
        //cout << "Assigning "<<index+1<<"th value in value list\n";
        arr[i]=posvals[index];          //assigns value to the list of random numbers to be the output
        //cout << "Assigning value "<<arr[i]<<endl;
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
        //cout << "\nValue assignment " << i+1 <<endl;
        while(true){
            arr[i]=rand()%(b-a+1)+a;    //generates a value for each random number
            //cout << "Trying Value " << arr[i] <<endl;
            if(history[arr[i]-a]==false) {  //check state of bool variable for the value generated.
                history[arr[i]-a]=true;     //If false, value can be used. Then sets state to true, and exits loop.
                break;                      //If true, value has already been used. Will cause while loop to repeat, will generate a new value to try.
            }
        }
    }
}
