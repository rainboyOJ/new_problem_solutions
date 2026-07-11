/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:58
 * update_at: 2026-07-11 18:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;
ll h[MAXN]; // h[i] 表示第 i 头牛当前的饥饿度

ll work_one_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    if (n == 1) {
        return 0;
    }

    ll ans = 0;

    for (int round = 1; round <= 2; round++) {
        for (int i = 2; i <= n - 1; i++) {
            if (h[i] > h[i - 1]) {
                ll diff = h[i] - h[i - 1];
                // 只能通过操作 (i, i+1) 把 h[i] 降到 h[i-1]。
                h[i] -= diff;
                h[i + 1] -= diff;
                ans += diff * 2;
            }
        }

        if (h[n] > h[n - 1]) {
            return -1;
        }

        // 第一遍处理左边更小的情况，反转后再处理右边更小的情况。
        for (int l = 1, r = n; l < r; l++, r--) {
            swap(h[l], h[r]);
        }
    }

    for (int i = 2; i <= n; i++) {
        if (h[i] != h[1]) {
            return -1;
        }
    }

    if (h[1] < 0) {
        return -1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << work_one_case() << '\n';
    }

    return 0;
}
