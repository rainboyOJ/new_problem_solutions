#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXS = 70;

int T;
int n, m;
long long a[MAXN][MAXN];      // 棋盘权值
int st[MAXS], state_cnt;      // 所有合法行状态
long long row_sum[MAXN][MAXS];
long long f[MAXN][MAXS];      // f[i][j]：处理到第 i 行，且第 i 行选状态 j 的最大和

bool valid_state(int s) {
    return (s & (s << 1)) == 0;
}

bool compatible(int a, int b) {
    if (a & b) {
        return false;
    }
    if ((a << 1) & b) {
        return false;
    }
    if ((a >> 1) & b) {
        return false;
    }
    return true;
}

void build_states() {
    state_cnt = 0;
    for (int s = 0; s < (1 << m); s++) {
        if (valid_state(s)) {
            st[++state_cnt] = s;
        }
    }
}

void calc_row_sum() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= state_cnt; j++) {
            row_sum[i][j] = 0;
            int mask = st[j];
            for (int k = 0; k < m; k++) {
                if (mask & (1 << k)) {
                    row_sum[i][j] += a[i][k + 1];
                }
            }
        }
    }
}

long long solve_one_case() {
    build_states();
    calc_row_sum();

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= state_cnt; j++) {
            f[i][j] = -1;
        }
    }

    for (int j = 1; j <= state_cnt; j++) {
        f[1][j] = row_sum[1][j];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= state_cnt; j++) {
            for (int k = 1; k <= state_cnt; k++) {
                if (f[i - 1][k] == -1) {
                    continue;
                }
                if (!compatible(st[j], st[k])) {
                    continue;
                }
                f[i][j] = max(f[i][j], f[i - 1][k] + row_sum[i][j]);
            }
        }
    }

    long long ans = 0;
    for (int j = 1; j <= state_cnt; j++) {
        ans = max(ans, f[n][j]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        cout << solve_one_case() << '\n';
    }

    return 0;
}
