/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:36
 * update_at: 2026-07-11 17:37
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN];

bool can_split(int target_sum) {
    int cur_sum = 0;
    for (int i = 1; i <= n; i++) {
        cur_sum += a[i];
        if (cur_sum > target_sum) {
            return false;
        }
        if (cur_sum == target_sum) {
            cur_sum = 0;
        }
    }
    return cur_sum == 0;
}

void solve_case() {
    cin >> n;
    int total_sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_sum += a[i];
    }

    // r 表示最终保留的段数，越大需要合并的次数越少。
    for (int r = n; r >= 1; r--) {
        if (total_sum % r != 0) {
            continue;
        }
        int target_sum = total_sum / r;
        if (can_split(target_sum)) {
            cout << n - r << '\n';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
