#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXK = 65;

struct Node {
    int pos;   // 彩珠所在位置
    int kind;  // 彩珠的种类编号
};

int n, k;
Node a[MAXN];
int cnt[MAXK]; // 当前窗口里每一种彩珠出现了多少次

bool cmp_node(const Node &x, const Node &y) {
    if (x.pos != y.pos) {
        return x.pos < y.pos;
    }
    return x.kind < y.kind;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    int tot = 0;

    for (int i = 1; i <= k; i++) {
        int t;
        cin >> t;
        for (int j = 1; j <= t; j++) {
            ++tot;
            cin >> a[tot].pos;
            a[tot].kind = i;
        }
    }

    // 先把所有彩珠按坐标排成一条线，问题就变成：
    // 找到一个最短的连续彩珠段，使它覆盖全部 k 种颜色。
    sort(a + 1, a + tot + 1, cmp_node);

    int covered = 0; // 当前窗口里已经覆盖了多少种彩珠
    int l = 1;
    int ans = INT_MAX;

    for (int r = 1; r <= tot; r++) {
        if (cnt[a[r].kind] == 0) {
            covered++;
        }
        cnt[a[r].kind]++;

        while (covered == k) {
            // 当前窗口已经合法，尽量用它更新最短长度。
            ans = min(ans, a[r].pos - a[l].pos);

            // 左端点右移，尝试继续缩短区间。
            cnt[a[l].kind]--;
            if (cnt[a[l].kind] == 0) {
                covered--;
            }
            l++;
        }
    }

    cout << ans << '\n';
    return 0;
}
