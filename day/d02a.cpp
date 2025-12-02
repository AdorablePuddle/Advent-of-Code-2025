#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Split input into segments.
vector<string> splitter(string input, char separator = ',') {
    vector<string> output = {};
    string part = "";
    for (char c : input) {
        if (c == separator) {
            output.push_back(part);
            part = "";
        } else {
            part = part + c;
        }
    }
    if (!part.empty()) output.push_back(part);
    return output;
}

// Preprocess the sequences of digits repeated twice.
long long int doubling(long long int v) {
    long long int ov = v;
    long long int tmp = v;
    while (v > 0) {
        tmp *= 10;
        v /= 10;
    }
    return tmp + ov;
}

vector<long long int> preprocessing(long long int limit = 1e12) {
    vector<long long int> output = {0};
    long long int i = 1;
    while (doubling(i) < limit) {
        output.push_back(doubling(i++));
    }
    return output;
}

// Process each segments
long long int total_double(string input, vector<long long int> list) {
    long long int s, t, total = 0;

    // Split each segment strings into start and end.
    string tmp = "";
    for (char c : input) {
        if (c == '-') {
            s = stoll(tmp);
            tmp = "";
        } else {
            tmp = tmp + c;
        }
    }
    if (!tmp.empty()) t = stoll(tmp);
    
    // Binary Search
    int p_start = lower_bound(list.begin(), list.end(), s) - list.begin();
    int p_end = lower_bound(list.begin(), list.end(), t) - list.begin();
    if (list[p_end] > t) p_end -= 1;
    for (int i = p_start; i <= p_end; i += 1) {
        total += list[i];
    }
    return total;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<long long int> doubleList = preprocessing();

    string input;
    cin >> input;
    long long int final_total = 0;
    vector<string> segments = splitter(input);
    for (string segment : segments) {
        final_total += total_double(segment, doubleList);
    }
    cout << final_total;
}