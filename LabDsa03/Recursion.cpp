#include<iostream>
using namespace std;
int power(int x, int p);
int multi(int a, int b);

int main() {
    int x, y;
    cout << "Enter the number to calculate its power: ";
    cin >> x;
    cout << "Enter the power of the number: ";
    cin >> y;
    cout << "Result: " << power(x, y) << endl;
    cout << "Enter 1st number for multiplication: ";
    cin >> x;
    cout << "Enter 2nd number for multiplication: ";
    cin >> y;
    cout << "Product = " << multi(x, y) << endl;
}

//Power 
int power(int x, int p) {
    if (p == 0) {
        return 1;
    }
    else
        return x * power(x, p - 1);
}
//Multiplication
int multi(int a, int b) {
    return(b == 1 ? a : multi(a, b - 1) + a);
}