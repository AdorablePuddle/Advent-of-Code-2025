#include <chrono>
#include <iomanip>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
#include "cpp_lib/DSU.hpp"
using namespace std;
typedef long long int int64;
typedef pair<int64, pair<int, int>> edge;

struct Point3D {
    int64 x, y, z;
    Point3D(int64 x, int64 y, int64 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

int64 sdistance(Point3D &a, Point3D &b) {
    int64 x = llabs(a.x - b.x);
    int64 y = llabs(a.y - b.y);
    int64 z = llabs(a.z - b.z);
    return x * x + y * y + z * z;
}

Point3D point_formatter(string &input) {
    Point3D *output = new Point3D(0, 0, 0);
    int d = 0;
    string s = "";
    for (char c : input) {
        if (c != ',') s = s + c;
        else {
            switch (d) {
                case 0:
                    output->x = stoll(s);
                break;
                case 1:
                    output->y = stoll(s);
                break;
            }
            s = "";
            d += 1;
        }
    }
    output->z = stoll(s);
    return *output;
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;

    int n;
    vector<Point3D> point_list;
    priority_queue<edge, vector<edge>, greater<edge>> edge_list;

    while (cin >> input) {
        point_list.push_back(point_formatter(input));
    }
    n = (int)point_list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int64 dist = sdistance(point_list[i], point_list[j]);
            edge_list.push(edge(dist, pair<int, int>(i, j)));
        }
    }

    int connection_limit = n - 1;
    edge last_edge;
    DSU circuit(n);

    while (connection_limit && !edge_list.empty()) {
        edge current = edge_list.top();
        edge_list.pop();
        if (!circuit.isSameSet(current.second.first, current.second.second)) {
            circuit.unify(current.second.first, current.second.second);
            connection_limit--;
            last_edge = current;
        }
    }

    cout << point_list[last_edge.second.first].x * point_list[last_edge.second.second].x;
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cerr << "Solution time: " << fixed << setprecision(3) << (float)duration.count() / 1000 << "s\n";
}