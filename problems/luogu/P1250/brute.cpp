// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

struct Request {
    int l;
    int r;
    int need;
};

int n, h;
Request req[MAXN];

bool check_mask(int mask) {
    for (int i = 1; i <= h; i++) {
        int cnt = 0;
        for (int pos = req[i].l; pos <= req[i].r; pos++) {
            if (mask & (1 << (pos - 1))) {
                cnt++;
            }
        }
        if (cnt < req[i].need) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> h;
    for (int i = 1; i <= h; i++) {
        cin >> req[i].l >> req[i].r >> req[i].need;
    }

    int ans = n + 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (check_mask(mask)) {
            ans = min(ans, __builtin_popcount((unsigned)mask));
        }
    }

    cout << ans << '\n';
    return 0;
}
