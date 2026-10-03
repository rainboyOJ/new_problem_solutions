/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 12:04
 * update_at: 2026-10-03 12:04
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;

int n;
ll t[maxn]; // 题目给出的 t 数列
ll b[maxn]; // 目标数列

// 记 mirror(i) = n + 1 - i。
// 设第 k 个版本的 t 为 T^k（T^0 = t，每做一次操作一变成 fold(T^k)），
// 并且 x_k 表示用 T^k 做了几次操作二，则
//     a_i = x_0 * t_i + H * (t_i + t_mirror(i)),  H = sum_{k>=1} x_k * 2^(k-1) >= 0
// 其中 x_0 >= 0 与 H 都是可以任意取的非负整数。
// 于是答案就是：是否存在非负整数 x_0, H 使所有等式同时成立。
bool check() {
    // 情形 1：存在 i 使 t_i != t_mirror(i)。
    // 用 i 与 mirror(i) 两条等式相减，可以直接反解出 x_0。
    int pos = -1;
    for (int i = 1; i <= n; i++) {
        if (t[i] != t[n + 1 - i]) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        int j = n + 1 - pos;
        ll num = b[pos] - b[j];    // = x_0 * (t_pos - t_j)
        ll den = t[pos] - t[j];    // 由 t_pos != t_j 保证 den != 0
        if (num % den != 0) return false;
        ll x0 = num / den;
        if (x0 < 0) return false;

        // 用 i = 1 的等式反解 H
        ll rest = b[1] - x0 * t[1];
        ll coef = t[1] + t[n];
        if (rest % coef != 0) return false;
        ll H = rest / coef;
        if (H < 0) return false;

        // 逐条验证
        for (int i = 1; i <= n; i++) {
            if (b[i] != x0 * t[i] + (t[i] + t[n + 1 - i]) * H) return false;
        }
        return true;
    }

    // 情形 2：t 完全对称，即所有 t_i == t_mirror(i)。
    // 此时等式退化为 b_i = t_i * (x_0 + 2H)，只要所有 b_i / t_i 是同一个整数即可
    // （取 x_0 等于这个整数、H = 0 就能实现）。
    if (b[1] % t[1] != 0) return false;
    ll K = b[1] / t[1];
    for (int i = 1; i <= n; i++) {
        if (b[i] != K * t[i]) return false;
    }
    return true;
}

void read_data() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> t[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        if (check()) cout << "Yes\n";
        else cout << "No\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    read_data();

    return 0;
}
