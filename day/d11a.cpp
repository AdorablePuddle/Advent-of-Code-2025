#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
const int N = 26 * 26 * 26 + 3;
const int INF = 1e9 + 7;

int n = 0;
unordered_map<string, int> h_map;
vector<string> r_map;
vector<pii> edge_list;
vector<vector<bool>> mp;
vector<int> in_deg;
vector<int> topological_array;
vector<int> dp;

void formatter(string line) {
    stringstream ss;
    ss << line;
    vector<string> tokenized;
    string tmp;
    while (ss >> tmp) {
        tokenized.push_back(tmp);
    }
    tokenized[0].erase(tokenized[0].length() - 1);
    // Insert stuff into hashmap if possible.

    for (string token : tokenized) {
        if (h_map.find(token) == h_map.end()) {
            h_map[token] = n++;
            r_map.push_back(token);
        }
    }

    for (int i = 1; i < (int)tokenized.size(); i++) {
        edge_list.push_back(pii(
            h_map[tokenized[0]],
            h_map[tokenized[i]]
        ));
    }
}

void debug() {
    for (int i = 0; i < n; i++) {
        cout << r_map[i] << " : " << h_map[r_map[i]] << "\n";
    }

    cout << "\n";
    for (pii edge : edge_list) {
        cout << edge.first << ", " << edge.second << "\n";
    }
}

void topological_sort() {
    vector<bool> vs(n, false);
    queue<int> current;
    for (int i = 0; i < n; i++) {
        if (in_deg[i] == 0) {
            current.push(i);
            vs[i] = true;
        }
    }
    while (!current.empty()) {
        int node = current.front();
        current.pop();
        topological_array.push_back(node);

        for (int i = 0; i < n; i++) {
            if (mp[node][i] && !vs[i]) {
                in_deg[i] -= 1;
                if (in_deg[i] == 0) {
                    vs[i] = true;
                    current.push(i);
                }
            }
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // Solution Here:
    // Assumption: No back-pointing edge. Otherwise the number of possible path can go to infinity.

    string line;
    while (getline(cin, line)) {
        formatter(line);
    }

    // debug();

    mp.assign(n, vector<bool>(n, false));
    in_deg.assign(n, 0);

    for (pii edge : edge_list) {
        mp[edge.first][edge.second] = true;
        in_deg[edge.second] += 1;
    }

    // DP

    topological_sort();
    dp.assign(n, 0);
    dp[h_map["you"]] = 1;

    for (int pos : topological_array) {
        for (int i = 0; i < n; i++) {
            if (mp[pos][i]) dp[i] += dp[pos];
        }
    }

    cout << dp[h_map["out"]];
}