/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:46
 * update_at: 2026-10-07 21:46
 */
// 1753 区间连通性
// 两个区间只要交集长度 > 0 就能互相走到（端点相切不算），所以"可达"就是普通的
// 无向连通：并查集维护连通块；同一连通块内所有区间的并集恰好是一段连续线段，
// 于是用一个按左端点排序的 map 维护"各连通块的线段"，插入新区间时把与之
// 正长度相交的线段全部并进来（每条线段只会被删一次）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

int n;
int fa[MAXN];    // 并查集父指针
int siz[MAXN];   // 并查集块大小

// 连通块线段：左端点 -> (右端点, 该连通块的并查集代表元)
map<ll, pair<ll, int> > seg;

// 找 x 所在连通块的代表元，顺路做路径减半。
int find_root(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

// 合并两个区间所在的连通块（按大小合并）。
void merge_block(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return;
    if (siz[a] < siz[b]) swap(a, b);
    fa[b] = a;
    siz[a] += siz[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }

    int cnt = 0;          // 已经加入的区间个数，也就是区间编号
    for (int i = 1; i <= n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            ll x, y;
            cin >> x >> y;
            cnt++;

            // 找第一个可能与 (x,y) 正长度相交的线段：
            // 左端点 <= x 的那条线段若右端点 > x，说明它跨过 x，从它开始；
            // 否则从第一条左端点 > x 的线段开始。
            map<ll, pair<ll, int> >::iterator it = seg.upper_bound(x);
            if (it != seg.begin()) {
                map<ll, pair<ll, int> >::iterator pre = prev(it);
                if (pre->second.first > x) it = pre;
            }

            // 线段两两不相交，所以从这里开始，凡左端点 < y 的线段都跨过 x，逐条吸收
            ll nl = x;
            ll nr = y;
            while (it != seg.end() && it->first < y) {
                nl = min(nl, it->first);
                nr = max(nr, it->second.first);
                merge_block(cnt, it->second.second);
                it = seg.erase(it);
            }
            seg[nl] = make_pair(nr, find_root(cnt));
        } else {
            int a, b;
            cin >> a >> b;
            cout << (find_root(a) == find_root(b) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
