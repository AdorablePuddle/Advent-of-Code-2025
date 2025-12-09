#include "DSU.hpp"
#include <vector>
using namespace std;

DSU::DSU(int n) {
    this->n = n;
    this->par.assign(n, 0);
    for (int i = 0; i < n; i++) {
        this->par[i] = i;
    }
    this->union_size.assign(n, 1);
}

int DSU::parent(int a) {
    return this->par[a] = (this->par[a] == a)? a : this->parent(this->par[a]);
}

int DSU::isSameSet(int a, int b) {
    return this->parent(a) == this->parent(b);
}

int DSU::setSize(int a) {
    return this->union_size[this->parent(a)];
}

void DSU::unify(int a, int b) {
    int pa = this->parent(a);
    int pb = this->parent(b);

    if (pa == pb) return;
    if (this->union_size[pa] > this->union_size[pb]) {
        this->par[pb] = pa;
        this->union_size[pa] += this->union_size[pb];
    } else {
        this->par[pa] = pb;
        this->union_size[pb] += this->union_size[pa];
    }
}