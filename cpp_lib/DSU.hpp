#ifndef DSU_HPP
#define DSU_HPP
#include <vector>
using namespace std;

class DSU {
private:
    int n; // Number of units.
    vector<int> par;
    vector<int> union_size;
public:
    DSU(int n);
    int parent(int a);
    int isSameSet(int a, int b);
    int setSize(int a);
    void unify(int a, int b);
};

#endif // DSU_HPP