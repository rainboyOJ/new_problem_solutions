#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int MAXN = 205;
const int MAXK = 65;

struct Node {
    int pos;
    int kind;
};

int n, k;
Node a[MAXN];
int cnt[MAXK];

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

    sort(a + 1, a + tot + 1, cmp_node);

    int ans = INT_MAX;

    // brute.cpp：枚举排序后彩珠序列上的左右端点。
    // 只要这个区间已经覆盖了所有种类，就用坐标差更新答案。
    for (int l = 1; l <= tot; l++) {
        for (int i = 1; i <= k; i++) {
            cnt[i] = 0;
        }
        int covered = 0;

        for (int r = l; r <= tot; r++) {
            if (cnt[a[r].kind] == 0) {
                covered++;
            }
            cnt[a[r].kind]++;

            if (covered == k) {
                ans = min(ans, a[r].pos - a[l].pos);
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
