#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long int int64;

vector<string> transpose(vector<string> input, int width, int height) {
    vector<string> output;
    for (int i = 0; i < width; i++) {
        output.push_back("");
        for (int j = 0; j < height; j++) {
            if (input[j][i] != ' ')
                output[i] = output[i] + input[j][i];
        }
    }
    return output;
}

vector<char> symbolize(string input) {
    vector<char> output;
    for (char c : input) {
        if (c != ' ') output.push_back(c);
    }
    return output;
}

vector<vector<int64>> test_split(vector<string> input) {
    vector<vector<int64>> test_cases;
    test_cases.push_back(vector<int64>());
    for (string line : input) {
        if (line != "") {
            test_cases[(int)test_cases.size() - 1].push_back(stoll(line));
        } else {
            test_cases.push_back(vector<int64>());
        }
    }
    return test_cases;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string temp;
    vector<string> input;
    vector<char> symbols;
    int width = 0, height = 0;
    while (getline(cin, temp)) {
        if (temp[0] != '*' && temp[0] != '+') {
            input.push_back(temp);
            height += 1;
        }
        else symbols = symbolize(temp);
        width = max(width, (int)temp.length());
    }
    input = transpose(input, width, height);
    vector<vector<int64>> test_cases = test_split(input);
    int64 ans = 0;
    for (int test_case = 0; test_case < (int)test_cases.size(); test_case++) {
        int64 current = 0;
        switch (symbols[test_case]) {
            case '+':
                for (int i = 0; i < (int)test_cases[test_case].size(); i++) {
                    current += test_cases[test_case][i];
                }
                break;
            case '*':
                current = 1;
                for (int i = 0; i < (int)test_cases[test_case].size(); i++) {
                    current *= test_cases[test_case][i];
                }
                break;
        }
        ans += current;
    }
    cout << ans;
}