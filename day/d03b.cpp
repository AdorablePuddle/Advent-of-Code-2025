#include <iostream>
#include <string>
#include <vector>
using namespace std;
const long long int INF = 1e12 + 7;

long long int exp10(long long int v, int m) {
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
    vector<vector<long long int>> dp;
    int digit_count = 12;
    long long int final_total = 0;
    while (cin >> input) {
        dp.assign(input.length() + 1, vector<long long int>(digit_count, -INF));
        for (int d = 0; d < digit_count; d++) {
            for (int i = input.length() - 1; i >= 0; i--) {
                long long int current_digit = exp10(input[i] - '0', d);
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