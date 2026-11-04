/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 19:01
 * update_at: 2026-11-04 19:01
 */
/*
 * 思路(与 main.py 一致)：
 *   答案小于 2^9，从高位到低位一位一位尝试：这一位能变成 0 吗？
 *
 * 关键优化：
 *   每一行 a[i] 选择哪个 b[j] 是相互独立的，
 *   判断 "整体 OR 能否被 attempt 覆盖" 时，
 *   只需对每个 a[i] 判断是否存在某个 b[j] 使 (a[i]&b[j]) 是 attempt 的子集，
 *   不需要枚举 m^n 种组合。复杂度 O(10 * n * m)。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int b[maxn];

void read_data(){
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];
}

// 是否存在一种选择，使整体 OR 的每一位都落在 attempt 里(即 OR 是 attempt 的子集)
bool test(int attempt) {
    for (int i = 0; i < n; i++) {
        bool ok = false;
        for (int j = 0; j < m; j++) {
            // (a[i] & b[j]) 必须 ⊆ attempt，即 (a[i]&b[j]) & ~attempt == 0
            if (((a[i] & b[j]) & ~attempt) == 0) {
                ok = true;
                break;
            }
        }
        if (!ok) return false; // 这一行怎么选都超出 attempt
    }
    return true;
}

void sol(){
    int ans = (1 << 10) - 1; // 全 1 一定可行(上界)

    for (int i = 9; i >= 0; i--) {
        int attempt = ans ^ (1 << i); // 试着把第 i 位变成 0
        if (test(attempt)) {
            ans = attempt;
        }
    }

    cout << ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();
    sol();
    return 0;
}
