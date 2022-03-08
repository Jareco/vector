#include <iostream>
#include "vector.h"
using namespace std;

int main(){
    cout << "Test program for vector" << endl;

    cout << "Test 1 " << endl;
    Vector<double> v1({});
    v1.push_back(43.4);
    for(double el: v1){
        cout << el << endl;
    }

    cout << "Test 2 " << endl;
    Vector<double> v2;
    v2.push_back(5.3);
    cout << v2[0] << endl;
    return 0;
}