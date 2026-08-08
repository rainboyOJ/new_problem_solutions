#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 1000000 + 5;
const i64 MOD = 998244353LL;

int n;
int lc[MAXN], rc[MAXN];
int sz[MAXN];          // sz[u] 表示以 u 为根能到达的场景总数
i64 cat[MAXN];         // cat[i] 表示 i 个结点的本质不同二叉树数量（Catalan 数）
i64 pre_cat[MAXN];     // pre_cat[i] = cat[1] + ... + cat[i]
i64 rank_in_size[MAXN];// rank_in_size[u] 表示在“结点数相同”的所有本质不同 Galgame 中的排名（从 0 开始）
i64 inv[MAXN];

inline int read_int() {
    int x = 0;
    int f = 1;
    int ch = getchar();

    while (ch != '-' && (ch < '0' || ch > '9')) {
        ch = getchar();
    }
    if (ch == '-') {
        f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    n = read_int();
    for (int i = 1; i <= n; i++) {
        lc[i] = read_int();
        rc[i] = read_int();
    }

    // 预处理 Catalan 数。
    inv[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    cat[0] = 1;
    for (int i = 1; i <= n; i++) {
        cat[i] = cat[i - 1] * (4LL * i - 2) % MOD;
        cat[i] = cat[i] * inv[i + 1] % MOD;
        pre_cat[i] = (pre_cat[i - 1] + cat[i]) % MOD;
    }

    // 非递归后序遍历，避免深链爆栈。
    vector<int> order;
    order.reserve(n);
    vector<int> st;
    st.reserve(n);
    st.push_back(1);

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);

        if (lc[u] != 0) {
            st.push_back(lc[u]);
        }
        if (rc[u] != 0) {
            st.push_back(rc[u]);
        }
    }

    for (int i = (int) order.size() - 1; i >= 0; i--) {
        int u = order[i];
        sz[u] = sz[lc[u]] + sz[rc[u]] + 1;
    }

    for (int i = (int) order.size() - 1; i >= 0; i--) {
        int u = order[i];
        int left_size = sz[lc[u]];
        int right_size = sz[rc[u]];
        int total_size = sz[u];

        i64 ans = 0;

        // 第一段：
        // 左子树大小更小的所有情况。
        // 利用 Catalan 总和，只枚举更小的一边。
        if (left_size <= right_size) {
            for (int x = 0; x < left_size; x++) {
                ans += cat[x] * cat[total_size - 1 - x] % MOD;
                if (ans >= MOD) {
                    ans -= MOD;
                }
            }
        }
        else {
            ans = cat[total_size];
            for (int y = 0; y <= right_size; y++) {
                ans -= cat[total_size - 1 - y] * cat[y] % MOD;
                if (ans < 0) {
                    ans += MOD;
                }
            }
        }

        // 第二段：左子树大小相同，但左子树本身更不有趣。
        ans += rank_in_size[lc[u]] * cat[right_size] % MOD;
        ans %= MOD;

        // 第三段：左子树完全相同，再比较右子树。
        ans += rank_in_size[rc[u]];
        ans %= MOD;

        rank_in_size[u] = ans;
    }

    // 有趣度 = 所有结点数更少的本质不同 Galgame 数量
    //        + 在同样结点数下更不有趣的数量。
    i64 ans = pre_cat[sz[1] - 1] + rank_in_size[1];
    ans %= MOD;

    printf("%lld\n", ans);

    return 0;
}
