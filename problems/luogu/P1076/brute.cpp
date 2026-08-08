#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 105;
const int MOD = 20123;

int n, m;
int has_stair[MAXN][MAXM];
int val[MAXN][MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> has_stair[i][j] >> val[i][j];
        }
    }

    int now;
    cin >> now;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + val[i][now]) % MOD;

        int need = val[i][now];
        int pos = now;

        // 朴素做法：真的沿着一圈一圈地数第 need 个有楼梯的房间。
        while (true) {
            if (has_stair[i][pos]) {
                need--;
                if (need == 0) {
                    now = pos;
                    break;
                }
            }
            pos++;
            if (pos == m) {
                pos = 0;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
