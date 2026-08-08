#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000;

int n, k;
int perm[15];
int used[15];
int ans;

int count_inv() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (perm[i] > perm[j]) {
                ret++;
            }
        }
    }
    return ret;
}

void dfs(int pos) {
    if (pos > n) {
        if (count_inv() == k) {
            ans++;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
        return;
    }

    for (int x = 1; x <= n; x++) {
        if (used[x]) {
            continue;
        }
        used[x] = 1;
        perm[pos] = x;
        dfs(pos + 1);
        used[x] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举所有排列，直接统计逆序对数。
    cin >> n >> k;
    memset(used, 0, sizeof(used));
    ans = 0;
    dfs(1);
    cout << ans << '\n';
    return 0;
}
