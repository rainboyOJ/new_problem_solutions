// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 25;

struct Edge {
    int u;
    int v;
    int w;
};

int n, m;
Edge edges[MAXM];
int fa[MAXN];

int find_set(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_set(fa[x]);
    return fa[x];
}

bool check_mask(int mask, long long &sum) {
    int cnt = 0;
    sum = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    for (int i = 0; i < m; i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        cnt++;
        sum += edges[i + 1].w;
        int fu = find_set(edges[i + 1].u);
        int fv = find_set(edges[i + 1].v);
        if (fu == fv) {
            return false;
        }
        fa[fu] = fv;
    }

    if (cnt != n - 1) {
        return false;
    }

    int root = find_set(1);
    for (int i = 2; i <= n; i++) {
        if (find_set(i) != root) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    long long ans = -1;
    for (int mask = 0; mask < (1 << m); mask++) {
        long long sum;
        if (check_mask(mask, sum)) {
            if (ans == -1 || sum < ans) {
                ans = sum;
            }
        }
    }

    if (ans == -1) {
        cout << "orz\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
