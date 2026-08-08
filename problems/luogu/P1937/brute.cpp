#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

struct Request {
    int l, r;
};

int n, m;
int cap[MAXN];
int remain_cap[MAXN];
Request req[MAXN];
int best_ans;

bool can_take(int idx) {
    for (int i = req[idx].l; i <= req[idx].r; i++) {
        if (remain_cap[i] == 0) {
            return false;
        }
    }
    return true;
}

void apply_req(int idx, int delta) {
    for (int i = req[idx].l; i <= req[idx].r; i++) {
        remain_cap[i] += delta;
    }
}

void dfs(int idx, int chosen) {
    if (idx > m) {
        best_ans = max(best_ans, chosen);
        return;
    }
    if (chosen + (m - idx + 1) <= best_ans) {
        return;
    }

    if (can_take(idx)) {
        apply_req(idx, -1);
        dfs(idx + 1, chosen + 1);
        apply_req(idx, 1);
    }

    dfs(idx + 1, chosen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 枚举每个请求接不接，并维护每个畜栏的剩余容量。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
        remain_cap[i] = cap[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> req[i].l >> req[i].r;
    }

    dfs(1, 0);
    cout << best_ans << '\n';
    return 0;
}
