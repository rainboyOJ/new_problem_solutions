#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int cnt[4];                 // cnt[j] 表示当前分到第 j 个部门的人数
vector<int> loss[4];        // loss[j]：从第 j 个部门挪走某个人造成的满意度损失

void clear_case() {
    for (int i = 1; i <= 3; i++) {
        cnt[i] = 0;
        loss[i].clear();
    }
}

void solve_case() {
    cin >> n;
    clear_case();

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int a[4];
        cin >> a[1] >> a[2] >> a[3];

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
        loss[best].push_back(a[best] - second_best);
    }

    int limit = n / 2;
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

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
