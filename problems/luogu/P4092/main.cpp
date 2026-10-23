/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 19:57
 * update_at: 2026-10-23 19:57
 */
// main.cpp：离线时光倒流 + 并查集维护树上连通块与最近标记祖先。
// 复杂度 O((n + q) * alpha(n))，空间 O(n)。
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

// parent_node[u] 记录树上节点 u 的父亲节点
int parent_node[MAXN];
// dsu_fa[u] 并查集父节点指针，代表当前连通块中最靠上的已标记节点
int dsu_fa[MAXN];
// mark_cnt[u] 统计节点 u 被标记的总次数
int mark_cnt[MAXN];

// 并查集带路径压缩查询代表元
int find_root(int x) {
    if (dsu_fa[x] == x)
        return x;
    return dsu_fa[x] = find_root(dsu_fa[x]);
}

// 记录操作以便离线处理
struct Operation {
    char type; // 'C' 或 'Q'
    int u;     // 操作节点编号
    int ans;   // 询问操作的答案
};

Operation ops[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q))
        return 0;

    // 读入 n - 1 条有向边 u -> v，表示 u 是 v 的父亲
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        parent_node[v] = u;
    }

    // 节点 1 初始已标记，计数值置为 1（且永不降为 0）
    mark_cnt[1] = 1;

    for (int i = 0; i < q; i++) {
        cin >> ops[i].type >> ops[i].u;
        if (ops[i].type == 'C') {
            mark_cnt[ops[i].u]++;
        }
    }

    // 初始化操作结束时的并查集森林：
    // 若点 i 最终被标记（mark_cnt[i] > 0），它自身就是集合的代表元；
    // 若点 i 未被标记，直接将其父指针指向 parent_node[i]。
    for (int i = 1; i <= n; i++) {
        if (mark_cnt[i] > 0) {
            dsu_fa[i] = i;
        } else {
            dsu_fa[i] = parent_node[i];
        }
    }

    // 倒序时光倒流：加标记变成删标记
    for (int i = q - 1; i >= 0; i--) {
        if (ops[i].type == 'Q') {
            ops[i].ans = find_root(ops[i].u);
        } else {
            mark_cnt[ops[i].u]--;
            // 当标记次数归零时，说明在当前操作发生之前，点 ops[i].u 是没有标记的，
            // 它所属集合的代表元 ops[i].u 向父亲所在的集合合并。
            if (mark_cnt[ops[i].u] == 0) {
                dsu_fa[ops[i].u] = parent_node[ops[i].u];
            }
        }
    }

    // 按顺序输出所有询问的答案
    for (int i = 0; i < q; i++) {
        if (ops[i].type == 'Q') {
            cout << ops[i].ans << "\n";
        }
    }

    return 0;
}
