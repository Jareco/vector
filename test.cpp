#include <iostream>
#include "vector.h"
using namespace std;

int main(){
    cout << "Test program for vector" << endl;

    Vector<double> v1{1,2,3,4.45,54.42,4,43,344.43};
    for(double el: v1){
        cout << el << endl;
    }
    return 0;
}