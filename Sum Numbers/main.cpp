#include <iostream>
#include <string>
using namespace std;

//functiom declarations:
int sumValues(int arr[], int count);
void saveValues(int arr[], int count);
int dumbSum(int count);
string flag(int i);


int main() {
    int size=0;
    char save;
    cout << "How many numbers will you be adding?"<< endl;
    cin >> size;
    cout << "Would you like to save the values? (Y/N)" <<endl;

    while(1) {
    cin >> save;

    if(save=='y' || save=='Y') {
        int values[size];
        saveValues(values, size);
        cout << "Sum of all values is:\n" <<sumValues(values, size) << endl;
        break;
    }

    if(save=='n' || save=='N') {
        cout << "Sum of all values is:\n" << dumbSum(size) << endl;
        break;
    }

    else {
        cout << "Please enter Y or N only" << endl;
    }
    }
    return 0;
}

//function definitions:
//first save (amd print) all values...
void saveValues(int arr[], int count) {
    int current=0;
    for(int i=0; i<count; i++) {
        cout << "Enter "<< i+1 << flag(i+1) <<" value:"<<endl;
        cin >> current;
        arr[i]=current;     //part that saves values
    }
    cout << "Values saved. Values are:" <<endl;
    for(int i=0;i<count-1; i++) {     //part that prints values
        cout << arr[i] << ", ";
    }
    cout << arr[count-1] << "." << endl;
}

//then sum all numbers.
int sumValues(int arr[], int count) {
    int sum=0;
    for(int i=0; i<count; i++) {
        sum+=arr[i];
    }
    return sum;
}

//this one mimics the other two functions, but does not save the imdividual values.
int dumbSum(int count) {
    int sum=0;
    int current=0;
    for(int i=0; i<count; i++) {
        cout << "Enter "<< i+1 << flag(i+1) <<" value:"<<endl;
        cin >> current;
        sum += current;
    }
    return sum;
}

//this one gives the correct suffix for the entry number.
string flag(int i) {
    if(i%10==1 && (i<11 || i>13)) return "st";
    if(i%10==2 && (i<11 || i>13)) return "nd";
    if(i%10==3 && (i<11 || i>13)) return "rd";
    else return "th";
}
