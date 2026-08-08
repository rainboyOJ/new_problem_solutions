#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据回溯枚举每根木棍放到哪条加工链中，求最少链数。

const int MAXN = 18;

struct Stick {
    int l, w;
};

int n;
Stick a[MAXN];
Stick tail[MAXN]; // 每条当前加工链最后一根木棍
int chain_cnt;
int ans;

bool can_follow(const Stick &last, const Stick &cur) {
    return last.l >= cur.l && last.w >= cur.w;
}

bool cmp_stick(const Stick &x, const Stick &y) {
    if (x.l != y.l) {
        return x.l > y.l;
    }
    return x.w > y.w;
}

void dfs(int idx) {
    if (chain_cnt >= ans) {
        return;
    }
    if (idx > n) {
        ans = min(ans, chain_cnt);
        return;
    }

    Stick cur = a[idx];

    for (int i = 1; i <= chain_cnt; i++) {
        if (can_follow(tail[i], cur)) {
            Stick old = tail[i];
            tail[i] = cur;
            dfs(idx + 1);
            tail[i] = old;
        }
    }

    chain_cnt++;
    tail[chain_cnt] = cur;
    dfs(idx + 1);
    chain_cnt--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].w;
    }

    // 先排序，把“任意重排后分链”的问题转成固定顺序下的最小链覆盖。
    sort(a + 1, a + n + 1, cmp_stick);

    ans = n;
    chain_cnt = 0;
    dfs(1);

    cout << ans << '\n';
    return 0;
}
