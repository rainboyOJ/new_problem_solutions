/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:54
 * update_at: 2026-10-05 06:54
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;
const int MAXM = 50005;

ll n;               // 焊点数
ll m;               // 导线数
int fa[MAXN];       // 并查集：fa[i] 表示焊点 i 的父亲
int deg[MAXN];      // deg[i] 表示焊点 i 上的导线端数（度数）
ll cntOdd[MAXN];    // 每个连通块内奇度焊点个数
ll cntFree[MAXN];   // 每个连通块内自由端个数
ll cntHigh[MAXN];   // 每个连通块内度数 > 2 的焊点个数
ll done[MAXN];      // done[i] 表示焊点 i 所在块是否已统计过答案
ll u[MAXM], v[MAXM]; // 每根导线两端的焊点标号，0 表示自由端

// 并查集查找（路径压缩）。
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
    }
}

void solve() {
    // 初始化并查集
    for (int i = 0; i <= n; i++) fa[i] = i;

    // 有公共焊点的导线合并进同一个连通块；端点 0 是自由端，不参与合并
    for (int i = 1; i <= m; i++) {
        if (u[i] && v[i]) {
            int ru = find(u[i]);
            int rv = find(v[i]);
            if (ru != rv) fa[ru] = rv;
        }
    }

    // 按块累计三个计数器
    for (int i = 1; i <= m; i++) {
        // 自由端计入所在块的 cntFree；两端都自由的导线自己单独成块（见下面答案统计）
        if (!u[i]) cntFree[find(v[i])]++;
        if (!v[i]) cntFree[find(u[i])]++;
    }
    for (int i = 1; i <= n; i++) {
        deg[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        if (u[i]) deg[u[i]]++;
        if (v[i]) deg[v[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 0) {
            if (deg[i] % 2 == 1) cntOdd[find(i)]++;
            if (deg[i] > 2) cntHigh[find(i)]++;
        }
    }

    // 每个连通块独立算代价再求和：
    // 奇端数 o 必须两两焊接，贡献 o/2 次焊接；度数 > 2 的焊点要烧熔拆开，贡献 high 次。
    // o == 0 说明这块本身已经闭合成环，要先烧开再焊回去，代价至少 2；
    // 若块内有 high 个高次点，烧熔时顺带打开，只需再多 1 次焊接，即 max(2, high+1)。
    // 两端都自由的导线（0-0）不属于任何焊点的块，o = 2，单独贡献 1 次焊接。
    ll ans = 0;
    ll loneWires = 0; // 两端都是自由端的导线数
    for (int i = 1; i <= m; i++) {
        if (!u[i] && !v[i]) loneWires++;
    }

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) continue; // 没接导线的焊点不用考虑
        int r = find(i);
        if (done[r]) continue;
        done[r] = 1;
        ll o = cntOdd[r] + cntFree[r];
        if (o > 0) {
            ans += cntHigh[r] + o / 2;
        } else {
            ans += max(2LL, cntHigh[r] + 1);
        }
    }
    ans += loneWires; // 每根 0-0 导线自成一块，o = 2，代价 1

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
