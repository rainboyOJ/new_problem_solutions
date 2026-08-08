// brute.cpp：枚举所有边子集，直接找恰好 K 个连通块的最小代价。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const int MAXM = 30;
const long long INF = (1LL << 60);

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m, k;
int fa[MAXN];
long long best_answer = INF;

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }
    fa[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    if (k > n) {
        cout << "No Answer\n";
        return 0;
    }

    int all_mask = 1 << m;
    for (int mask = 0; mask < all_mask; mask++) {
        init_dsu();
        int blocks = n;
        long long sum = 0;
        bool ok = true;

        for (int i = 0; i < m; i++) {
            if (((mask >> i) & 1) == 0) {
                continue;
            }
            if (!unite(edges[i].u, edges[i].v)) {
                ok = false;
                break;
            }
            blocks--;
            sum += edges[i].w;
        }

        if (!ok) {
            continue;
        }
        if (blocks == k) {
            best_answer = min(best_answer, sum);
        }
    }

    if (best_answer == INF) {
        cout << "No Answer\n";
    } else {
        cout << best_answer << '\n';
    }

    return 0;
}
