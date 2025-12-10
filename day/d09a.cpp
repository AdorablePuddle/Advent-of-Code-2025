#include <chrono>
#include <iomanip>

#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef long long int int64;

pii input_formatter(string input) {
    string a = "";
    string b = "";

    bool mode = 0;
    for (char c : input) {
        if (c == ',') {
            mode = !mode;
            continue;
        }
        if (!mode) {
            a = a + c;
        } else {
            b = b + c;
        }
    }
    return pii(stoi(a), stoi(b));
}

int64 area(pii a, pii b) {
    return (llabs(a.first - b.first) + 1) * (llabs(a.second - b.second) + 1);
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // Solution Here:
    vector<pii> tile_list;
    string input;
    while (cin >> input) {
        tile_list.push_back(input_formatter(input));
    }
    int n = (int)tile_list.size();

    int64 ans = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = max(ans, area(tile_list[i], tile_list[j]));
        }
    }
    cout << ans;

    // End of solution.
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cerr << "Solution time: " << fixed << setprecision(3) << (float)duration.count() / 1000 << "s\n";
}