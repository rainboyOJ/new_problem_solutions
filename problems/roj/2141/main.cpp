/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:52
 * update_at: 2026-10-08 07:52
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

typedef long long ll;

ll n;
int boss[MAXN];          // boss[i]：员工 i 的直接上司，根 1 的上司记为 0
vector<int> child[MAXN]; // 邻接表：child[u] 存 u 的所有直接下属
int sz[MAXN];            // sz[u]：以 u 为根的子树节点数（含 u 本人），最大 n 用 int 足够
int order[MAXN];         // BFS 序：父亲一定排在孩子之前，可避免递归爆栈

void read_input() {
    cin >> n;
    for (ll i = 2; i <= n; i++) {
        cin >> boss[i];
        child[boss[i]].push_back(i); // 建边：上司 -> 直接下属
    }
}

void solve() {
    // 从总经理 1 出发做 BFS，得到「父先于子」的访问序
    int head = 0, tail = 0;
    order[tail++] = 1;
    while (head < tail) {
        int u = order[head++];
        for (ll i = 0; i < (ll)child[u].size(); i++) {
            order[tail++] = child[u][i];
        }
    }

    // 初始化每个节点子树大小为 1（只有自己）
    for (ll i = 1; i <= n; i++) {
        sz[i] = 1;
    }

    // 逆着 BFS 序处理：孩子先算完，再把自己的整棵子树报给父亲
    for (int i = tail - 1; i >= 0; i--) {
        int u = order[i];
        if (u != 1) {
            sz[boss[u]] += sz[u];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    // 员工 i 的下属人数 = 子树大小 - 1
    for (ll i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << sz[i] - 1;
    }
    cout << '\n';

    return 0;
}
