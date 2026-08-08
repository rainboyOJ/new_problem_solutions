#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 ans;
int a[25];
bool used[25];
i64 mod;

void dfs(int pos) {
    if (pos > 2 * n) {
        ans++;
        return;
    }

    for (int x = 1; x <= 2 * n; x++) {
        if (used[x]) {
            continue;
        }

        // 奇数位置要满足奇数位递增。
        if (pos >= 3 && (pos & 1) && a[pos - 2] >= x) {
            continue;
        }

        // 偶数位置要满足偶数位递增。
        if (pos >= 4 && !(pos & 1) && a[pos - 2] >= x) {
            continue;
        }

        // 每一对还要满足 a[2i-1] < a[2i]。
        if (!(pos & 1) && a[pos - 1] >= x) {
            continue;
        }

        a[pos] = x;
        used[x] = true;
        dfs(pos + 1);
        used[x] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> mod;

    dfs(1);
    cout << ans % mod << '\n';

    return 0;
}
