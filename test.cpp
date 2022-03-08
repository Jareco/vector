#include <iostream>
#include "vector.h"
using namespace std;

int main(){
    cout << "Test program for vector" << endl;

    cout << "Test 1 " << endl;
    Vector<double> v1(25);
    cout << v1.capacity() << endl;
    v1.push_back(43.4);
    cout << v1 << endl;
    v1.shrink_to_fit();
    cout << v1.capacity() << endl;
    cout << v1 << endl;
    v1.push_back(23);
    cout << v1 << endl;
    v1.pop_back();
    cout << v1 << endl;

    cout << "Test 2 " << endl;
    Vector<double> v2;
    v2.push_back(5.3);
    cout << v2 << endl;

    cout << "Test 3" << endl;
    Vector<double> v3;
    v3.push_back(2.32);
    v3.push_back(233);
    v3.push_back(32.3);

    for (const auto el: v3)
        cout << el << endl;
    return 0;
}