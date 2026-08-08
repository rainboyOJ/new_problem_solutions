#include <bits/stdc++.h>
using namespace std;

const int MAXR = 105;

struct State {
    int cnt;
    int time;
    State() : cnt(0), time(0) {}
    State(int c, int t) : cnt(c), time(t) {}
    bool better_than(const State& o) const {
        if (cnt != o.cnt) return cnt > o.cnt;
        return time < o.time;
    }
};

int n, m, r;
int rmb[105], rp[105], tmm[105];
// dp[a][b] 表示花 a 元 RMB、b 点 RP 时，能泡到的最多 MM 数及最少时间。
State dp[MAXR][MAXR];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> rmb[i] >> rp[i] >> tmm[i]; // 花费 RMB、RP，所需时间
    }
    cin >> m >> r;                         // 总 RMB 和总 RP

    // 0/1 背包：二维费用，倒序枚举两维。
    for (int i = 1; i <= n; i++) {
        for (int a = m; a >= rmb[i]; a--) {
            for (int b = r; b >= rp[i]; b--) {
                State nxt(dp[a - rmb[i]][b - rp[i]].cnt + 1,
                          dp[a - rmb[i]][b - rp[i]].time + tmm[i]);
                if (nxt.better_than(dp[a][b])) {
                    dp[a][b] = nxt;
                }
            }
        }
    }

    cout << dp[m][r].time << '\n';
    return 0;
}
