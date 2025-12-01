#include <iostream>
#include <string>
using namespace std;

int d = 50;

int add(int a, int b, int m = 100) {
    return (a % m + b % m) % m;
}

int sub(int a, int b, int m = 100) {
    return ((a % m) + m - b % m) % m;
}

int main(){
    freopen("input.txt", "r", stdin);
    string input;
    int output = 0;
    while (cin >> input) {
        char mode = input[0];
        input.erase(input.begin(), input.begin() + 1);
        int amount = stoi(input);
        switch(mode) {
            case 'L':
                d = sub(d, amount);
                break;
            case 'R':
                d = add(d, amount);
                break;
        }
        output += (d)? 0 : 1;
    }
    cout << output;
}