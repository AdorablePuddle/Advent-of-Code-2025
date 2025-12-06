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
vector<int64> id_check;

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

    int64 check_input;
    while (cin >> check_input) {
        id_check.push_back(check_input);
        // cout << check_input << "\n";
    }

    sort(fresh_id.begin(), fresh_id.end());
    sort(id_check.begin(), id_check.end());

    /*
        Iterate over every fresh tag. While iterating, have a second pointer points at the list of id needed to be checked.
        The second pointer will check every number currently smaller than the fresh tag. If a fresh tag range is active, the checked id is fresh.
    */

    int value = 0;
    
    int active_tag = 0;
    int id_tag = 0;
    for (int i = 0; i < (int)fresh_id.size(); i++) {
        // If it is less, check if a range is already active beforehand.
        while (id_tag < (int)id_check.size() && id_check[id_tag] < fresh_id[i].first) {
            value += (active_tag > 0);
            id_tag++;
        }

        // If it is equal, whether or not the tag ends here does not matter. Add 1 until id tag is no longer equal.
        while (id_tag < (int)id_check.size() && id_check[id_tag] == fresh_id[i].first) {
            value += 1;
            id_tag++;
        }

        if (fresh_id[i].second == 1) {
            active_tag = max(active_tag - 1, 0);
        } else {
            active_tag++;
        }
    }

    cout << value;
}