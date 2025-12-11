#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
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
    return (int64)(llabs(a.first - b.first) + 1ll) * (int64)(llabs(a.second - b.second) + 1ll);
}

vector<int> compressor(vector<int> original) {
    sort(original.begin(), original.end());
    vector<int> compressed(original[(int)original.size() - 1] + 1, -1);
    int prev = -1;
    int counter = 1;
    for (int val : original) {
        if (prev != -1 && val - prev > 1) counter++;
        if (prev != -1 && val - prev == 0) counter--;
        compressed[val] = counter++;
        prev = val;
    }
    return compressed;
}

void draw_line(vector<vector<int>> &compressed_map, int start, int end, int unchange, bool change_x) {
    if (change_x) {
        for (int i = start; i <= end; i++) {
            compressed_map[i][unchange] = 0;
        }
    } else {
        for (int i = start; i <= end; i++) {
            compressed_map[unchange][i] = 0;
        }
    }
}

void draw_compressed_map(vector<vector<int>> &compressed_map, int bx, int by) {
    for (int y = 0; y < by; y++) {
        for (int x = 0; x < bx; x++) {
            switch(compressed_map[x][y]) {
                case -1:
                    cout << ' ';
                    break;
                case 0:
                    cout << '.';
                    break;
                default:
                    cout << '#';
                    break;
            }
        }
        cout << '\n';
    }
    cout << "\n------------------------------------------------------------------\n\n";
}

void flood_fill(vector<vector<int>> &compressed_map, int bx, int by, int sx, int sy, int color) {
    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1}; 

    queue<pii> q;
    q.push(pii(sx, sy));
    compressed_map[sx][sy] = color;

    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int d = 0; d < 8; d++) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (0 <= nx && nx < bx && 0 <= ny && ny < by) {
                if (compressed_map[nx][ny] == -1) {
                    compressed_map[nx][ny] = color;
                    q.push(pii(nx, ny));
                }
            }
        }
    }
}

void preprocessing(vector<pii> tile_list, vector<int> &cx, vector<int> &cy, vector<vector<int>> &compressed_map, vector<vector<int>> &prefix_map) {
    bool debug = false;
    vector<int> x, y; // cx, cy == compressed_x, compressed_y
    for (pii tile : tile_list) {
        x.push_back(tile.first);
        y.push_back(tile.second);
    }
    cx.clear();
    cy.clear();
    cx = compressor(x);
    cy = compressor(y);
    // cx[tile_x] ==> compressed x coordinate of that tile. Vice versa for y.

    int bound_x = cx[(int)cx.size() - 1] + 2;
    int bound_y = cy[(int)cy.size() - 1] + 2;
    compressed_map.assign(bound_x, vector<int>(bound_y, -1));
    prefix_map.assign(bound_x, vector<int>(bound_y, 0));
    compressed_map[cx[tile_list[0].first]][cy[tile_list[0].second]] = 1;

    int n = (int)tile_list.size();
    for (int tile = 1; tile <= n; tile++) {
        int cx_1 = cx[tile_list[(tile - 1) % n].first];
        int cy_1 = cy[tile_list[(tile - 1) % n].second];
        int cx_2 = cx[tile_list[tile % n].first];
        int cy_2 = cy[tile_list[tile % n].second];

        if (cy_1 == cy_2) {
            draw_line(compressed_map, min(cx_1, cx_2), max(cx_1, cx_2), cy_1, true);
        } else {
            draw_line(compressed_map, min(cy_1, cy_2), max(cy_1, cy_2), cx_1, false);
        }
    }

    flood_fill(compressed_map, bound_x, bound_y, 0, 0, 1);
    for (int x = 0; x < bound_x; x++) {
        for (int y = 0; y < bound_y; y++) {
            if (compressed_map[x][y] == -1) {
                flood_fill(compressed_map, bound_x, bound_y, x, y, 0);
            }
        }
    }
    if (debug) draw_compressed_map(compressed_map, bound_x, bound_y);

    // All of that preprocessing is to prepare for this moment

    for (int x = 1; x < bound_x; x++) {
        prefix_map[x][0] = compressed_map[x][0];
    }

    for (int y = 1; y < bound_y; y++) {
        prefix_map[0][y] = compressed_map[0][y];
    }

    for (int x = 1; x < bound_x; x++) {
        for (int y = 1; y < bound_y; y++) {
            prefix_map[x][y] = (prefix_map[x - 1][y] + prefix_map[x][y - 1] - prefix_map[x - 1][y - 1]) + compressed_map[x][y];
        }
    }
}

bool bounded(vector<vector<int>> &prefix_map, pii a, pii b) {
    // Get upper_left corner and lower_right corner:
    pii top_left     = pii(min(a.first, b.first), min(a.second, b.second));
    pii bottom_right = pii(max(a.first, b.first), max(a.second, b.second));
    int negative_area = 
          prefix_map[bottom_right.first][bottom_right.second]
        - prefix_map[bottom_right.first][top_left.second - 1]
        - prefix_map[top_left.first - 1][bottom_right.second]
        + prefix_map[top_left.first - 1][top_left.second - 1];
    
    return negative_area == 0;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // Solution Here:

    vector<pii> tile_list;
    vector<vector<int>> compressed_map;
    vector<vector<int>> prefix_map;
    vector<int> compressed_x, compressed_y;
    string input;
    while (cin >> input) {
        tile_list.push_back(input_formatter(input));
    }
    int n = (int)tile_list.size();

    // Preprocessing

    preprocessing(tile_list, compressed_x, compressed_y, compressed_map, prefix_map);

    // Solution

    int64 ans = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            pii comp_point_1 = pii(compressed_x[tile_list[i].first], compressed_y[tile_list[i].second]);
            pii comp_point_2 = pii(compressed_x[tile_list[j].first], compressed_y[tile_list[j].second]);
            if (bounded(prefix_map, 
                comp_point_1, 
                comp_point_2
            )) ans = max(ans, area(tile_list[i], tile_list[j]));
        }
    }
    cout << ans;
}