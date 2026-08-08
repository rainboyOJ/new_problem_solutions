#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n, m;
int x[MAXN];          // 第 i 个物品的魔法值
long long cnt[MAXN];  // cnt[v] 表示魔法值等于 v 的物品个数

long long ans_a[MAXN]; // ans_a[v]：魔法值为 v 的物品，作为 A 出现的次数
long long ans_b[MAXN]; // ans_b[v]：魔法值为 v 的物品，作为 B 出现的次数
long long ans_c[MAXN]; // ans_c[v]：魔法值为 v 的物品，作为 C 出现的次数
long long ans_d[MAXN]; // ans_d[v]：魔法值为 v 的物品，作为 D 出现的次数

long long suffix_pair[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
        cnt[x[i]]++;
    }

    // 设 q = Xd - Xc，则 Xb - Xa = 2q。
    // 因为 Xb - Xa < (Xc - Xb) / 3，
    // 代入 Xb = Xa + 2q 后可化成：Xc - Xa > 8q。
    // 由于都是整数，所以等价为：Xc >= Xa + 8q + 1。
    //
    // 于是一个合法魔法阵的值一定长成：
    // Xa = a, Xb = a + 2q, Xc = c, Xd = c + q，且 c >= a + 8q + 1。
    //
    // 对固定 q：
    // 1. 先统计所有 (c, c + q) 这类 C-D 值对，做成后缀和；
    // 2. 再从左到右维护所有满足 a <= c - 8q - 1 的 A-B 值对前缀和。
    int max_q = (n - 1) / 9;
    for (int q = 1; q <= max_q; q++) {
        int max_c = n - q;

        // suffix_pair[c] = sum_{i >= c} cnt[i] * cnt[i + q]
        suffix_pair[max_c + 1] = 0;
        for (int c = max_c; c >= 1; c--) {
            suffix_pair[c] = suffix_pair[c + 1] + cnt[c] * cnt[c + q];
        }

        long long prefix_pair = 0; // 当前已经加入的所有 cnt[a] * cnt[a + 2q] 之和
        int next_a = 1;

        for (int c = 1; c <= max_c; c++) {
            int limit_a = c - 8 * q - 1;

            // 把所有满足 a <= c - 8q - 1 的 A-B 值对加入前缀。
            while (next_a <= limit_a && next_a + 2 * q <= n) {
                prefix_pair += cnt[next_a] * cnt[next_a + 2 * q];
                next_a++;
            }

            long long right_pair = cnt[c] * cnt[c + q];
            if (right_pair != 0 && prefix_pair != 0) {
                // 当前值 c 作为 C，值 c + q 作为 D。
                ans_c[c] += cnt[c + q] * prefix_pair;
                ans_d[c + q] += cnt[c] * prefix_pair;
            }

            // 反过来，统计值 c 作为 A、值 c + 2q 作为 B 时，右侧能配多少组 C-D。
            if (c + 2 * q <= n) {
                int first_c = c + 8 * q + 1;
                if (first_c <= max_c) {
                    long long right_sum = suffix_pair[first_c];
                    if (right_sum != 0) {
                        ans_a[c] += cnt[c + 2 * q] * right_sum;
                        ans_b[c + 2 * q] += cnt[c] * right_sum;
                    }
                }
            }
        }
    }

    // 题目要求按物品输出。由于公式只依赖物品的魔法值，
    // 所以同魔法值的物品答案完全相同，直接按 x[i] 取即可。
    for (int i = 1; i <= m; i++) {
        int v = x[i];
        cout << ans_a[v] << ' ' << ans_b[v] << ' ' << ans_c[v] << ' ' << ans_d[v] << '\n';
    }

    return 0;
}
