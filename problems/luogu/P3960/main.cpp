/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 02:05
 * update_at: 2026-11-11 02:05
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAXNODE = 12000005;
const int MAXN = 300005;

int n, m, q;
int lim; // 线段树维护的区间上限 max(n, m) + q

// 动态开点权值线段树
int ls[MAXNODE], rs[MAXNODE];
int del[MAXNODE];
int node_cnt = 0;

int root[MAXN];

// 后来追加到各行和最后一列末尾的人的真实编号
vector<ll> app[MAXN];

// 查询并删除线段树中第 k 个未删除的元素，返回其原始位置 pos
int query_and_del(int& u, int l, int r, int k) {
    if (!u) u = ++node_cnt;
    del[u]++;

    if (l == r) return l;

    int mid = l + (r - l) / 2;
    // 左子树总长度为 (mid - l + 1)，左子树已删除人数为 del[ls[u]]
    int left_alive = (mid - l + 1) - (ls[u] ? del[ls[u]] : 0);

    if (k <= left_alive) {
        return query_and_del(ls[u], l, mid, k);
    } else {
        return query_and_del(rs[u], mid + 1, r, k - left_alive);
    }
}

// 删除最后一列中的第 x 个人
ll pop_last_col(int x) {
    int pos = query_and_del(root[n + 1], 1, lim, x);
    ll ans;
    if (pos <= n) {
        ans = 1LL * pos * m;
    } else {
        ans = app[n + 1][pos - n - 1];
    }
    return ans;
}

// 删除第 x 行中的第 y 个人
ll pop_row(int x, int y) {
    int pos = query_and_del(root[x], 1, lim, y);
    ll ans;
    if (pos <= m - 1) {
        ans = 1LL * (x - 1) * m + pos;
    } else {
        ans = app[x][pos - m];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> q)) return 0;

    lim = max(n, m) + q;

    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;

        if (y == m) {
            // 离队的是最后一列的同学
            ll ans = pop_last_col(x);
            // 归队到最后一列的末尾
            app[n + 1].push_back(ans);
            cout << ans << "\n";
        } else {
            // 离队的是第 x 行前 m-1 个同学之一
            ll ans = pop_row(x, y);
            // 最后一列第 x 个同学移入第 x 行末尾
            ll last_col_val = pop_last_col(x);
            app[x].push_back(last_col_val);
            // 离队的同学填入最后一列末尾
            app[n + 1].push_back(ans);
            cout << ans << "\n";
        }
    }

    return 0;
}
