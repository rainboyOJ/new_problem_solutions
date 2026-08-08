#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, m;
string s[MAXN];
int cost_w[MAXN], cost_b[MAXN], cost_r[MAXN];
int pre_w[MAXN], pre_b[MAXN], pre_r[MAXN];

int row_cost(int row, char target) {
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (s[row][i] != target) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        cost_w[i] = row_cost(i, 'W');
        cost_b[i] = row_cost(i, 'B');
        cost_r[i] = row_cost(i, 'R');
        pre_w[i] = pre_w[i - 1] + cost_w[i];
        pre_b[i] = pre_b[i - 1] + cost_b[i];
        pre_r[i] = pre_r[i - 1] + cost_r[i];
    }

    int ans = 0x3f3f3f3f;

    // 枚举白蓝分界和蓝红分界。
    for (int white_end = 1; white_end <= n - 2; white_end++) {
        for (int blue_end = white_end + 1; blue_end <= n - 1; blue_end++) {
            int white_cost = pre_w[white_end];
            int blue_cost = pre_b[blue_end] - pre_b[white_end];
            int red_cost = pre_r[n] - pre_r[blue_end];
            ans = min(ans, white_cost + blue_cost + red_cost);
        }
    }

    cout << ans << '\n';

    return 0;
}
