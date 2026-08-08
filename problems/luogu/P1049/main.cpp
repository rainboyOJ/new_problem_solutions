#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
const int MAXV = 20005;

int capacity;          // 箱子容量
int n;                 // 物品数量
int a[MAXN];           // 每个物品的体积
int dp[MAXV];          // dp[j] = 容量不超过 j 时，最多能装下多少体积

void read_input() {
    cin >> capacity;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        // 倒序枚举容量，保证每个物品最多只用一次。
        for (int j = capacity; j >= a[i]; j--) {
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
        }
    }

    cout << capacity - dp[capacity] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
