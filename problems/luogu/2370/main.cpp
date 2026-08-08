#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXS = 1005;

int n;
ll p;
int S;
int w[MAXS];
int v[MAXS];
// dp[j] 是 check() 函数内的局部 DP 数组，表示用容量 j 能获得的最大价值。
ll dp[MAXS];

// 判断在文件大小不超过 L 的情况下，能否装下价值 ≥ p 的文件。
bool check(int L) {
    fill(dp, dp + S + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (w[i] > L) continue;
        for (int j = S; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    for (int j = 0; j <= S; j++) {
        if (dp[j] >= p) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p >> S;

    int max_w = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        max_w = max(max_w, w[i]);
    }

    // 二分答案：找最小的文件大小限制 L 使得可以装下 ≥ p 的价值。
    int l = 1, r = max_w, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (ans == -1) {
        cout << "No Solution!" << '\n';
    } else {
        cout << ans << '\n';
    }
    return 0;
}
