/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 10:24
 * update_at: 2026-11-01 10:24
 */
// brute.cpp：固定左端点，倒序枚举覆盖位置，维护合法右端点的最优值。
// 每次询问 O(n²)，只用于小规模验证。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 50005;
const ll NEG_INF = -(1LL << 60);
int n, q;
ll prefix_sum[MAXN], answer[MAXN];

void solve_query(int L, int R) {
    fill(answer + 1, answer + n + 1, NEG_INF);
    for (int left = 1; left + L - 1 <= n; left++) {
        int last = min(n, left + R - 1);
        ll best = NEG_INF;
        for (int i = last; i >= left; i--) {
            if (i - left + 1 >= L) {
                best = max(best, prefix_sum[i] - prefix_sum[left - 1]);
            }
            answer[i] = max(answer[i], best);
        }
    }
    ull result = 0;
    for (int i = 1; i <= n; i++) result ^= (ull)i * (ull)answer[i];
    cout << result << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll value;
        cin >> value;
        prefix_sum[i] = prefix_sum[i - 1] + value;
    }
    cin >> q;
    while (q--) {
        int L, R;
        cin >> L >> R;
        solve_query(L, R);
    }
    return 0;
}
