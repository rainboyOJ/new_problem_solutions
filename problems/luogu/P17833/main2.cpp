#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 5005;

ll a[MAXN];
int nxt_pos[MAXN];
int pre_pos[MAXN];
ll f[MAXN];
ll g[MAXN];

void solve() {
    int n;
    ll d;
    if (scanf("%d%lld", &n, &d) != 2) return;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 双指针预处理每个点一步向右和向左能到达的最远点
    int j = 1;
    for (int i = 1; i <= n; i++) {
        while (j + 1 <= n && a[j + 1] - a[i] <= d) {
            j++;
        }
        nxt_pos[i] = j;
    }

    j = n;
    for (int i = n; i >= 1; i--) {
        while (j - 1 >= 1 && a[i] - a[j - 1] <= d) {
            j--;
        }
        pre_pos[i] = j;
    }

    // O(N^2) 朴素递推单调唯一可达路径数量
    for (int i = n; i >= 1; i--) {
        f[i] = 1;
        if (pre_pos[nxt_pos[i]] == i) {
            f[i] += f[nxt_pos[i]];
        }
        for (int k = i + 1; k < nxt_pos[i]; k++) {
            if (pre_pos[k] == i) {
                f[i]++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        g[i] = 1;
        if (nxt_pos[pre_pos[i]] == i) {
            g[i] += g[pre_pos[i]];
        }
        for (int k = pre_pos[i] + 1; k < i; k++) {
            if (nxt_pos[k] == i) {
                g[i]++;
            }
        }
    }

    ll ans = 0;

    // 类别 1 & 2：枚举分叉左端点 u，右端点直接由极右极值跳步确定 v = nxt[nxt[u]]
    for (int i = 1; i <= n; i++) {
        int v = nxt_pos[nxt_pos[i]];
        if (nxt_pos[i] == v) continue;
        if (pre_pos[v] != nxt_pos[i] - 1) continue;
        if (pre_pos[pre_pos[v]] == i) {
            ans += f[v] * g[i];
        } else if (pre_pos[pre_pos[v]] < i) {
            ans += f[v];
        }
    }

    // 类别 3：枚举分叉右端点 v，左端点直接由极左极值跳步确定 u = pre[pre[v]]
    for (int i = 1; i <= n; i++) {
        int u = pre_pos[pre_pos[i]];
        if (pre_pos[i] == u) continue;
        if (nxt_pos[u] - 1 != pre_pos[i]) continue;
        if (nxt_pos[nxt_pos[u]] > i) {
            ans += g[u];
        }
    }

    // 类别 4：暴力枚举未完全跳满极值的右端点
    for (int i = 1; i <= n; i++) {
        int x = nxt_pos[i];
        for (int v = x + 1; v < nxt_pos[x]; v++) {
            if (pre_pos[v] == x - 1 && pre_pos[pre_pos[v]] < i) {
                ans++;
            }
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int c, t;
    if (scanf("%d%d", &c, &t) == 2) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
