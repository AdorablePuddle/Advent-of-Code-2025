#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int INF = 1e9 + 7;

int exp10(int v, int m) {
    while (m > 0) {
        v *= 10;
        m -= 1;
    }
    return v;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;
    vector<vector<int>> dp;
    int digit_count = 2;
    int final_total = 0;
    while (cin >> input) {
        dp.assign(input.length() + 1, vector<int>(digit_count, -INF));
        for (int d = 0; d < digit_count; d++) {
            for (int i = input.length() - 1; i >= 0; i--) {
                int current_digit = exp10(input[i] - '0', d);
                if (d == 0) {
                    dp[i][d] = max(dp[i + 1][d], current_digit);
                } else {
                    dp[i][d] = max(dp[i + 1][d], current_digit + dp[i + 1][d - 1]);
                }
            }
        }
        final_total += dp[0][digit_count - 1];
    }
    cout << final_total;
}