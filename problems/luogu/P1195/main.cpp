#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} edges[MAXM];

int n, m, k;
int fa[MAXN];

void init_dsu(int n) {
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
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    if (k > n) {
        cout << "No Answer\n";
        return 0;
    }

    sort(edges + 1, edges + m + 1);
    init_dsu(n);

    int blocks = n;
    long long answer = 0;

    for (int i = 1; i <= m; i++) {
        if (blocks == k) {
            break;
        }
        if (!unite(edges[i].u, edges[i].v)) {
            continue;
        }
        blocks--;
        answer += edges[i].w;
    }

    if (blocks != k) {
        cout << "No Answer\n";
    } else {
        cout << answer << '\n';
    }

    return 0;
}
