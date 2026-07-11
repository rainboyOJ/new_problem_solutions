/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:05
 * update_at: 2026-07-11 21:06
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 300005;
const long long INF = (1LL << 60);

long long n;
int m, k;
long long change_val[MAXM][2]; // 第 i 轮猜 0/1 时，Elsie 在最坏情况下的弹珠变化。
long long need[MAXM];          // need[i] 表示第 i 轮开始前，弹珠数必须严格大于它。
int answer[MAXM];

void solve_one() {
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        change_val[i][0] = INF;
        change_val[i][1] = INF;

        for (int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            int parity = x & 1;

            // 猜对时，Bessie 会让 Elsie 赢得尽量少。
            if (change_val[i][parity] > x) {
                change_val[i][parity] = x;
            }
            // 猜错时，Bessie 会让 Elsie 输得尽量多。
            if (change_val[i][parity ^ 1] > -x) {
                change_val[i][parity ^ 1] = -x;
            }
        }
    }

    need[m] = 0;
    for (int i = m - 1; i >= 0; i--) {
        long long best_change = max(change_val[i][0], change_val[i][1]);
        need[i] = need[i + 1] - best_change;
        if (need[i] < 0) need[i] = 0;
    }

    if (n <= need[0]) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 0; i < m; i++) {
        // Even 字典序更小，能保证后续安全就优先选 Even。
        if (n + change_val[i][0] > need[i + 1]) {
            answer[i] = 0;
            n += change_val[i][0];
        } else {
            answer[i] = 1;
            n += change_val[i][1];
        }
    }

    for (int i = 0; i < m; i++) {
        if (i) cout << ' ';
        if (answer[i] == 0) {
            cout << "Even";
        } else {
            cout << "Odd";
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
