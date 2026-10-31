#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2000005;

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

    // 双指针预处理每个点一步向右最远可达点 nxt_pos 与向左最远可达点 pre_pos
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

    // O(1) 转移计算后缀唯一单调向右延展路径数 f[i]
    for (int i = n; i >= 1; i--) {
        f[i] = 1;
        if (pre_pos[nxt_pos[i]] == i) {
            f[i] += f[nxt_pos[i]];
        }
        // pre_pos[k] == i 的 k 取值范围为 [nxt_pos[i-1] + 1, nxt_pos[i]]
        int left_bound = (i > 1) ? (nxt_pos[i - 1] + 1) : 1;
        int right_bound = nxt_pos[i];
        int inter_l = max(i + 1, left_bound);
        int inter_r = min(nxt_pos[i] - 1, right_bound);
        if (inter_l <= inter_r) {
            f[i] += (inter_r - inter_l + 1);
        }
    }

    // O(1) 转移计算前缀唯一单调向左延展路径数 g[i]
    for (int i = 1; i <= n; i++) {
        g[i] = 1;
        if (nxt_pos[pre_pos[i]] == i) {
            g[i] += g[pre_pos[i]];
        }
        // nxt_pos[k] == i 的 k 取值范围为 [pre_pos[i], pre_pos[i+1] - 1]
        int left_bound = pre_pos[i];
        int right_bound = (i < n) ? (pre_pos[i + 1] - 1) : n;
        int inter_l = max(pre_pos[i] + 1, left_bound);
        int inter_r = min(i - 1, right_bound);
        if (inter_l <= inter_r) {
            g[i] += (inter_r - inter_l + 1);
        }
    }

    ll ans = 0;

    // 类别 1 & 2：两端均可延伸或仅右侧可延伸
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

    // 类别 3：仅左侧可延伸
    for (int i = 1; i <= n; i++) {
        int u = pre_pos[pre_pos[i]];
        if (pre_pos[i] == u) continue;
        if (nxt_pos[u] - 1 != pre_pos[i]) continue;
        if (nxt_pos[nxt_pos[u]] > i) {
            ans += g[u];
        }
    }

    // 类别 4：两端均不可延伸，O(1) 封闭形式区间求交
    for (int i = 1; i <= n; i++) {
        int x = nxt_pos[i];
        int k = x - 1;
        if (k >= 1 && pre_pos[k] < i) {
            int left_bound = (k > 1) ? (nxt_pos[k - 1] + 1) : 1;
            int right_bound = nxt_pos[k];
            int inter_l = max(x + 1, left_bound);
            int inter_r = min(nxt_pos[x] - 1, right_bound);
            if (inter_l <= inter_r) {
                ans += (inter_r - inter_l + 1);
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
