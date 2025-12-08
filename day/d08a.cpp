#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "cpp_lib/DSU.hpp"
using namespace std;
typedef pair<double, pair<int, int>> edge;

struct Point3D {
    int x, y, z;
    Point3D(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

double distance(Point3D &a, Point3D &b) {
    double x = abs(a.x - b.x);
    double y = abs(a.y - b.y);
    double z = abs(a.z - b.z);
    return sqrt(x * x + y * y + z * z);
}

Point3D formatter(string &input) {
    vector<int> v;
    string s = "";
    for (char c : input) {
        if (c != ',') s = s + c;
        else {
            v.push_back(stoi(s));
            s = "";
        }
    }
    if (s != "") v.push_back(stoi(s));
    return Point3D(v[0], v[1], v[2]);
}

vector<pair<int, int>> circuit_rank(DSU circuit, int point_count) {
    bool temp[1000] = {};
    vector<pair<int, int>> output;
    for (int i = 0; i < point_count; i++) {
        if (!temp[circuit.parent(i)]) {
            temp[circuit.parent(i)] = true;
            output.push_back(pair<int, int>(circuit.setSize(i), circuit.parent(i)));
        }
    }
    return output;
}



int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;

    int n;
    vector<Point3D> point_list;
    vector<edge> edge_list;

    while (cin >> input) {
        point_list.push_back(formatter(input));
    }
    n = (int)point_list.size();
    // cout << point_list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distance(point_list[i], point_list[j]);
            edge_list.push_back(edge(dist, pair<int, int>(i, j)));
        }
    }
    sort(edge_list.begin(), edge_list.end());

    int connection_limit = 1000;
    DSU circuit(n);

    for (int i = 0; i < (int)edge_list.size() && connection_limit; i++) {
        circuit.unify(edge_list[i].second.first, edge_list[i].second.second);
        connection_limit--;
    }
    vector<pair<int, int>> ranking = circuit_rank(circuit, n);
    sort(ranking.begin(), ranking.end());
    reverse(ranking.begin(), ranking.end());
    cout << ranking[0].first * ranking[1].first * ranking[2].first;
}