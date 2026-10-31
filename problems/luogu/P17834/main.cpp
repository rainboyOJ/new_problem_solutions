#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
vector<int> G[MAXN];
int tim[MAXN], deg[MAXN], q_arr[MAXN], f[MAXN], a[MAXN], b[MAXN], c[MAXN], h[MAXN];
bool mid[MAXN];

bool check(int r, int n, int k) {
    int len = deg[r + 1] - k;
    if (len <= 0) return true;
    if (len > 2 * r) return false;
    for (int i = 1; i <= n; i++) {
        mid[i] = (h[i] > r && c[i] <= r);
    }
    for (int i = 1; i <= n; i++) {
        if (!mid[i] || (mid[a[i]] && mid[b[i]])) continue;
        int u = i, v = mid[a[i]] ? b[i] : a[i], cur = 0, j = 0;
        f[0] = 0;
        while (mid[u]) {
            mid[u] = 0;
            j++;
            f[j] = 0;
            int d = r - c[u];
            int l = max(0, j + d - len);
            int p = j - d;
            if (l < p) {
                f[l]++;
                f[p]--;
            }
            if (j >= len) {
                cur += f[j - len];
                if (!cur) return true;
            }
            int nxt = a[u] ^ b[u] ^ v;
            v = u;
            u = nxt;
        }
    }
    return false;
}

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        deg[i] = G[i].size();
        tim[i] = 0;
        if (deg[i] <= 1) {
            tim[i] = 1;
            q_arr[r++] = i;
        }
    }
    while (l < r) {
        int u = q_arr[l++];
        for (auto v : G[u]) {
            deg[v]--;
            if (deg[v] == 1) {
                tim[v] = tim[u] + 1;
                q_arr[r++] = v;
            }
        }
    }
    fill(deg, deg + n + 2, 0);
    for (int i = 1; i <= n; i++) {
        deg[tim[i]]++;
        a[i] = b[i] = c[i] = 0;
        for (auto v : G[i]) {
            if (tim[v] > tim[a[i]]) swap(v, a[i]);
            if (tim[v] > tim[b[i]]) swap(v, b[i]);
            c[i] = max(c[i], tim[v]);
        }
        h[i] = tim[b[i]];
    }
    for (int i = n; i >= 0; i--) {
        deg[i] += deg[i + 1];
    }
    l = 0;
    r = n;
    while (l < r) {
        int mid_val = (l + r) >> 1;
        if (check(mid_val, n, k)) r = mid_val;
        else l = mid_val + 1;
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int id, T;
    if (!(cin >> id >> T)) return 0;
    while (T--) {
        solve();
    }
    return 0;
}
