#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int n;
int a[MAXN];
int pre_one[MAXN];
int pre_two[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre_one[i] = pre_one[i - 1] + (a[i] == 1);
        pre_two[i] = pre_two[i - 1] + (a[i] == 2);
    }

    int ans = n;

    // 枚举分界点 cut：
    // [1..cut] 最终都应该是 1，
    // [cut+1..n] 最终都应该是 2。
    for (int cut = 0; cut <= n; cut++) {
        int change_left = pre_two[cut];
        int change_right = pre_one[n] - pre_one[cut];
        ans = min(ans, change_left + change_right);
    }

    cout << ans << '\n';
    return 0;
}
