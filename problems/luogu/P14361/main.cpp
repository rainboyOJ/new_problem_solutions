/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:53
 * update_at: 2026-10-01 22:53
 */
// main.cpp：满分做法，贪心 + 补偿：每人先分到满意度最高的部门，
// 若某部门超员，把"损失最小"的人挪到次优部门。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;
int cnt[4];              // cnt[j] 表示当前分到第 j 个部门的人数
vector<int> loss[4];     // loss[j]：从第 j 个部门挪走某个人造成的满意度损失

// 清空上一组数据的状态。
void clear_case() {
    for (int i = 1; i <= 3; i++) {
        cnt[i] = 0;
        loss[i].clear();
    }
}

void solve_case() {
    cin >> n;
    clear_case();

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        int a[4]; // a[j] = 第 i 个人对第 j 个部门的满意度（≤ 2*10^4，int 足够）
        cin >> a[1] >> a[2] >> a[3];

        // 找满意度最高的部门（best）和次高的满意度（second_best）。
        int best = 1;
        if (a[2] > a[best]) {
            best = 2;
        }
        if (a[3] > a[best]) {
            best = 3;
        }

        int second_best = 0;
        for (int j = 1; j <= 3; j++) {
            if (j == best) {
                continue;
            }
            second_best = max(second_best, a[j]);
        }

        ans += a[best];
        cnt[best]++;
        loss[best].push_back(a[best] - second_best); // 挪走这个人损失多少
    }

    // 检查是否有部门超员，若有则把损失最小的人挪走。
    int limit = (int)(n / 2);
    int over = 0;
    for (int j = 1; j <= 3; j++) {
        if (cnt[j] > limit) {
            over = j;
        }
    }

    if (over != 0) {
        int need_move = cnt[over] - limit;
        sort(loss[over].begin(), loss[over].end());
        for (int i = 0; i < need_move; i++) {
            ans -= loss[over][i];
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
