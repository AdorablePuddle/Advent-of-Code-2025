#include <iostream>
#include <string>
using namespace std;

int output = 0;
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
    while (cin >> input) {
        char mode = input[0];
        input.erase(input.begin(), input.begin() + 1);
        int amount = stoi(input);
        switch(mode) {
            case 'L':
                if (amount >= d) {
                    output += (d != 0) + ((amount - d) / 100);
                }
                d = sub(d, amount);
                break;
            case 'R':
                output += (d + amount) / 100;
                d = add(d, amount);
                break;
        }
    }
    cout << output;
}