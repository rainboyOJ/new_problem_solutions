/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:30
 * update_at: 2026-10-05 12:30
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100000 + 5;

int father[MAXN]; // father[x] = x 的父亲，根的父亲是自己
int cnt[MAXN];    // cnt[r] = 根 r 所在家族的人数

// 求 x 的根，并把路径上的点全部直接挂到根上（路径压缩）
int find_root(int x) {
    if (father[x] == x) return x;
    return father[x] = find_root(father[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        cnt[i] = 1;
    }

    for (int i = 0; i < m; ++i) {
        char op;
        cin >> op;
        if (op == 'M') {
            int a, b;
            cin >> a >> b;
            int ra = find_root(a);
            int rb = find_root(b);
            if (ra != rb) { // 按大小合并：小家族挂到大家族根下
                if (cnt[ra] < cnt[rb]) swap(ra, rb);
                father[rb] = ra;
                cnt[ra] += cnt[rb];
            }
        } else if (op == 'Q') {
            int a;
            cin >> a;
            cout << cnt[find_root(a)] << '\n';
        }
    }
    return 0;
}
