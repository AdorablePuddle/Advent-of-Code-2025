#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long int int64;
int height = 0, width = 0;
vector<vector<int64>> dp;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    vector<string> input_map;
    string input;
    while (cin >> input) {
        input_map.push_back(input);
        height += 1;
        width = max(width, (int)input.length());
    }
    dp.assign(height + 1, vector<int64>(width + 1, 0));
    for (int i = 0; i < width; i++) {
        if (input_map[0][i] == 'S') {
            dp[0][i] = 1;
        }
    }
    int splitted = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (dp[i][j] > 0) {
                if (i + 1 < height && input_map[i + 1][j] == '^') {
                    dp[i + 1][j - 1] += dp[i][j];
                    dp[i + 1][j + 1] += dp[i][j];
                    splitted += 1;
                } else {
                    dp[i + 1][j] += dp[i][j];
                }
            }
        }
    }
    int64 total = 0;
    for (int i = 0; i < width; i++) {
        total += dp[height][i];
    }
    cout << splitted << "\n" << total;
}