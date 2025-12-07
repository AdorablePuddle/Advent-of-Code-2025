#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long int int64;

vector<string> splitter(string input) {
    vector <string> output;
    string split = "";
    for (char c : input) {
        if (c != ' ') {
            split = split + c;
        } else {
            if (split != "") {
                output.push_back(split);
            }
            split = "";
        }
    }
    if (split != "") output.push_back(split);
    return output;
}

int64 calculate(vector<string> input) {
    // With the last character being the symbol.
    int n = (int)input.size();
    int64 output = 0;
    if (input[n - 1] == "+") {
        for (int i = 0; i < n - 1; i++) {
            output += stoll(input[i]);
        }
    }
    if (input[n - 1] == "*") {
        output = 1;
        for (int i = 0; i < n - 1; i++) {
            output *= stoll(input[i]);
        }
    }
    return output;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<vector<string>> matrix;
    string input;
    int H = 0, W = 0;
    while (getline(cin, input)) {
        matrix.push_back(splitter(input));
        H += 1;
        W = max(W, (int)matrix[H - 1].size());
    }
    vector<string> temp;
    int64 final_output = 0;
    for (int i = 0; i < W; i++) {
        temp.clear();
        for (int j = 0; j < H; j++) {
            // cout << matrix[j][i];
            temp.push_back(matrix[j][i]);
        }
        final_output += calculate(temp);
    }
    cout << final_output;
}