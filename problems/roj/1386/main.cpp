/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

typedef long long ll;

ll n;
vector<int> bigger_neighbor[MAXN]; // bigger_neighbor[i] 只存编号大于 i 的邻居，无向边只留一半

int parent_arr[MAXN];  // 并查集：parent_arr[i] == i 表示 i 是所在集团的代表
int group_size[MAXN];  // 只对代表有效：该集团内的团伙数

// 返回 x 所在集团的代表，顺路做路径压缩。
int find_root(int x) {
    while (parent_arr[x] != x) {
        parent_arr[x] = parent_arr[parent_arr[x]];
        x = parent_arr[x];
    }
    return x;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll cnt;
        cin >> cnt;
        for (ll t = 1; t <= cnt; t++) {
            ll j;
            cin >> j;
            if (j > i) {
                bigger_neighbor[i].push_back(j); // 小邻居会在处理小编号点时读到，这里丢掉
            }
        }
    }
}

void solve() {
    for (ll i = 1; i <= n; i++) {
        parent_arr[i] = i;
        group_size[i] = 1;
    }

    // 倒序加点：第 i 轮结束后集合 {i, i+1, ..., n} 的连通块，
    // 恰好等于"打击掉 1..i-1 之后剩下的集团"。首次出现超过 n/2 的集团时，答案就是 i。
    for (ll i = n; i >= 1; i--) {
        int root = find_root(i);
        ll neighbor_cnt = bigger_neighbor[i].size();
        for (ll k = 0; k < neighbor_cnt; k++) {
            int other = find_root(bigger_neighbor[i][k]);
            if (other != root) {
                // 统一朝 root 挂，保证轮末读 group_size[root] 是累计值；同时挡住重边重复累加
                parent_arr[other] = root;
                group_size[root] += group_size[other];
            }
        }
        if (group_size[root] > n / 2) {
            cout << i << "\n";
            return;
        }
    }

    cout << n << "\n"; // 整图连通时上面必然已返回，这里兜住非连通输入
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
