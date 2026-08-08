#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000 + 5;
const int MAXM = 100 + 5;
const int MOD = 20123;

int n, m;
int has_stair[MAXN][MAXM];
int val[MAXN][MAXM];
vector<int> stair_pos[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        stair_pos[i].clear();
        for (int j = 0; j < m; j++) {
            cin >> has_stair[i][j] >> val[i][j];
            if (has_stair[i][j]) {
                stair_pos[i].push_back(j);
            }
        }
    }

    int now;
    cin >> now;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + val[i][now]) % MOD;

        int cnt = (int) stair_pos[i].size();
        int step = (val[i][now] - 1) % cnt;

        // 找到从当前房间开始，逆时针方向遇到的第一个有楼梯房间。
        vector<int>::iterator it = lower_bound(stair_pos[i].begin(), stair_pos[i].end(), now);
        int pos = 0;
        if (it == stair_pos[i].end()) {
            pos = 0;
        }
        else {
            pos = (int) (it - stair_pos[i].begin());
        }

        now = stair_pos[i][(pos + step) % cnt];
    }

    cout << ans << '\n';
    return 0;
}
