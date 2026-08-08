#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXK = 55;
const int MAXS = 5005;

int n;                  // 学生人数
int need_cnt;           // 必须选出的人数：n / 2
int total_score;        // 全班总分
int limit_score;        // 允许的最大总分：floor(total / 2)
int a[MAXN];            // 每个学生的分数
bool dp[MAXK][MAXS];    // dp[j][s] = 是否能恰好选 j 人，总分恰好为 s

void read_input() {
    cin >> n;
    need_cnt = n / 2;
    total_score = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_score += a[i];
    }
    limit_score = total_score / 2;
}

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        // 人数和分数都要倒序，保证每个学生只被使用一次。
        for (int j = need_cnt; j >= 1; j--) {
            for (int s = limit_score; s >= a[i]; s--) {
                if (dp[j - 1][s - a[i]]) {
                    dp[j][s] = true;
                }
            }
        }
    }

    for (int s = limit_score; s >= 0; s--) {
        if (dp[need_cnt][s]) {
            cout << s << '\n';
            return;
        }
    }

    cout << 0 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
