#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int int64;

pair<int64, int64> splitter(string input) {
    int chr = 0;
    string num1 = "", num2 = "";
    while (input[chr] != '-' && chr < input.length()) {
        num1 = num1 + input[chr++];
    }
    chr++;
    while (input[chr] != '-' && chr < input.length()) {
        num2 = num2 + input[chr++];
    }
    return pair<int64, int64>(stoll(num1), stoll(num2));
}

vector<pair<int64, int>> fresh_id;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string input;

    while (getline(cin, input)) {
        if (input == "") break;
        pair<int64, int64> input_number = splitter(input);
        // fresh_id containing a marker for every number in the range, with 0 being range start, and 1 being range end.
        fresh_id.push_back(pair<int64, int>(input_number.first, 0));
        fresh_id.push_back(pair<int64, int>(input_number.second, 1));
        // cout << input_number.first << " " << input_number.second << "\n";
    }

    sort(fresh_id.begin(), fresh_id.end());

    /*
        For the second problem, the fresh_id is irrelevant.
        When the active tag goes from 0 to >0, we know that at least one tag is active. In which case, the moment it switches from 0 to 1, range_start is set to the current fresh_id.
        When the active tag finally goes back to 0, which we know will inevitably happen, the distance between the current fresh_id[i] to the range_start is the value needed to be add to final solution.
    */

    int64 value = 0;
    
    int active_tag = 0;
    int64 range_start = -1;
    for (int i = 0; i < (int)fresh_id.size(); i++) {
        if (fresh_id[i].second == 1) {
            active_tag = max(active_tag - 1, 0);
            if (active_tag == 0) {
                value += (fresh_id[i].first - range_start) + 1;
                range_start = fresh_id[i].first;
            }
        } else {
            if (active_tag == 0) {
                range_start = fresh_id[i].first;
            }
            active_tag++;
        }
    }

    cout << value;
}