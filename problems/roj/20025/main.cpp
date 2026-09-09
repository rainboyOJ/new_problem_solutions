/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:50
 * update_at: 2026-08-28 23:50
 */
// main.cpp：T5 好序列(GoodSeq) 最终解。
// 思路：正难则反 + 容斥（坏点 = 相邻相等的位置）-> 分段 DP（段内同值、段间不限）
//       -> 容斥系数只依赖段数奇偶，丢掉 j 维 -> 单调栈 + 前缀和优化 min 枚举，O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int MAXN = 1000005;

int n;
int a[MAXN]; // 输入序列

// f[i][0/1]：前 i 项分成 偶数段 / 奇数段（段内同值、段间取值不限）的方案总数。
//            即 f[i][p] = Σ_{j ≡ p (mod 2)} f_{i,j}，其中 f_{i,j} 是分成 j 段的总方案。
// g[i][0/1]：f 的按奇偶分别做前缀和，g[i][p] = Σ_{t=0..i} f[t][p]。
int f[MAXN][2], g[MAXN][2];

int stk[MAXN], top; // 单调栈：栈内 a 值严格递增（从栈底到栈顶），
                    // 栈中位置就是"后缀最小值"阶梯函数的所有拐点

// 快速读入一个整数（n 可达 1e6，关闭同步后仍建议快读）
int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

void read_input() {
    n = read_int();
    for (int i = 1; i <= n; i++) {
        a[i] = read_int();
    }
}

// 模意义下取正数：x 可能在 (-MOD, 2*MOD) 之间
ll M(ll x) { return (x % MOD + MOD) % MOD; }

void solve() {
    // 空序列分成 0 段：0 是偶数，算 1 种（空划分）
    f[0][0] = 1;
    g[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        // 弹出所有 a >= a[i] 的栈顶：它们不再能作为 (k..i) 的最小值拐点
        while (top && a[stk[top]] >= a[i]) top--;
        int cur = top ? stk[top] : 0; // 弹出后栈顶 cur：最后一个 a < a[i] 的拐点位置
        stk[++top] = i;               // 压入 i 作为新的拐点

        // 关键转移：f[i][p] = Σ_{k=1..i} f[k-1][1-p] * min(a[k..i])
        // 后缀最小值 min(a[k..i]) 是阶梯函数：
        //   k ∈ (stk[s-1], stk[s]] 时，min(a[k..i]) = a[stk[s]]
        // 因此总贡献 = f[cur][p]（沿用 cur 处已算好的前 top 层）
        //            + a[i] * (g[i-1][1-p] - g[cur-1][1-p])（新增的最后一段 (cur+1..i)）
        if (cur == 0) {
            // 栈空：阶梯只有最后一段 (1..i)，min = a[i]
            f[i][0] = M((ll)g[i - 1][1] * a[i]);
            f[i][1] = M((ll)g[i - 1][0] * a[i]);
        } else {
            f[i][0] = M(f[cur][0] + M((ll)M(g[i - 1][1] - g[cur - 1][1]) * a[i]));
            f[i][1] = M(f[cur][1] + M((ll)M(g[i - 1][0] - g[cur - 1][0]) * a[i]));
        }

        // 更新按奇偶分组的前缀和
        g[i][0] = M(g[i - 1][0] + f[i][0]);
        g[i][1] = M(g[i - 1][1] + f[i][1]);
    }

    // 答案 = Σ_j (-1)^{n-j} f_{n,j} = (-1)^n * (f[n][0] - f[n][1])
    ll ans;
    if (n & 1) ans = M(f[n][1] - f[n][0]);
    else ans = M(f[n][0] - f[n][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}