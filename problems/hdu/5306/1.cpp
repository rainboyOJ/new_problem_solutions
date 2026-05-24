#include <bits/stdc++.h>
using namespace std;

typedef long ll;
const int maxn = 1e6+5;

struct Node {
    ll sum;
    ll ma; // 区间最大值
    ll se; // 严格区间次最大值
    ll num; // 区间最大值的数量
};

Node tree[maxn*4];

ll ls(int rt) { return rt << 1;}
ll rs(int rt) { return (rt << 1) | 1;}


void pushup(int p)
}
n

int main (int argc, char *argv[]) {
    
    return 0;
}
