#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int dr[8] = { -1, -1, -1,  0,  0,  1,  1,  1};
const int dc[8] = { -1,  0,  1, -1,  1, -1,  0,  1};

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<string> paper_map;
    string input;
    int max_width = 0, max_height = 0;
    
    while (cin >> input) {
        max_width = max(max_width, (int)input.length());
        paper_map.push_back(input);
    }
    max_height = (int)paper_map.size();

    int result = 0;
    for (int r = 0; r < max_height; r++) {
        for (int c = 0; c < max_width; c++) {
            // Scan every square around this one if it is a toilet paper roll.
            if (paper_map[r][c] == '@') {
                int toilet_paper_counter = 0;
                for (int d = 0; d < 8; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= max_height) continue;
                    if (nc < 0 || nc >= max_width) continue;

                    toilet_paper_counter += (paper_map[nr][nc] == '@');
                }

                if (toilet_paper_counter < 4) result += 1;
            }
        }
    }
    cout << result;
}