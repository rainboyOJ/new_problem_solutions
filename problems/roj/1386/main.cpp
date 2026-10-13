/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-13 22:33
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 并查集竞赛精简版（不用 struct）：路径压缩 + 按大小合并
// 口诀：find 找根压到底，unite 小树挂大树
// 易错点：init 别只写 fa[i] = i，sz[i] 也要置 1；合并后 sz 只在新根上有效
// 和别的模板一起用时 maxn 只留一份

const int maxn = 1005;
int fa[maxn], sz[maxn];  // sz[x] 仅在根上有效

void init(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
}

// 查 x 的根，顺手把整条链压到根上
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool same(int x, int y) { return find(x) == find(y); }

// 小树挂大树，返回是否真的发生了合并
bool unite(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    if (sz[fx] < sz[fy]) swap(fx, fy);
    fa[fy] = fx;
    sz[fx] += sz[fy];
    return true;
}

ll n;
vector<int> bigger_neighbor[maxn]; // bigger_neighbor[i] 只存编号大于 i 的邻居，无向边只留一半

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
    init(n);

    // 倒序加点：第 i 轮结束后集合 {i, i+1, ..., n} 的连通块，
    // 恰好等于"打击掉 1..i-1 之后剩下的集团"。首次出现超过 n/2 的集团时，答案就是 i。
    for (ll i = n; i >= 1; i--) {
        ll neighbor_cnt = bigger_neighbor[i].size();
        for (ll k = 0; k < neighbor_cnt; k++) {
            unite(i, bigger_neighbor[i][k]);
        }
        // unite 按大小换根，必须合并后重新 find(i) 再读 sz[r]，不能沿用旧 root
        int r = find(i);
        if (sz[r] > n / 2) {
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
