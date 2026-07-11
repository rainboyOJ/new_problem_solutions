/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:21
 * update_at: 2026-07-11 16:23
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int T;
int n;
long long h[MAXN];
long long a[MAXN];
int target_rank[MAXN];
int pos_by_rank[MAXN]; // pos_by_rank[r] 表示目标排名为 r 的植物编号

long long ceil_div(long long x, long long y) {
    return (x + y - 1) / y;
}

bool check_days(long long days) {
    for (int r = 0; r + 1 < n; r++) {
        int big = pos_by_rank[r];
        int small = pos_by_rank[r + 1];

        long long big_height = h[big] + a[big] * days;
        long long small_height = h[small] + a[small] * days;
        if (big_height <= small_height) {
            return false;
        }
    }
    return true;
}

long long solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> target_rank[i];
        pos_by_rank[target_rank[i]] = i;
    }

    long long days = 0;

    for (int r = 0; r + 1 < n; r++) {
        int big = pos_by_rank[r];
        int small = pos_by_rank[r + 1];

        if (h[big] > h[small]) continue;

        long long grow_diff = a[big] - a[small];
        if (grow_diff <= 0) {
            return -1;
        }

        long long need = h[small] - h[big] + 1;
        days = max(days, ceil_div(need, grow_diff));
    }

    if (!check_days(days)) {
        return -1;
    }

    return days;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cout << solve_one() << '\n';
    }

    return 0;
}
