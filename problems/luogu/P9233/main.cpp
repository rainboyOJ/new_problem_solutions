/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:07
 */
// main.cpp：P9233 颜色平衡树。
// 判断每个结点的子树是否“每种颜色的点数都相同”，用 DSU on Tree（树上启发式合并）做到 O(n log n)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200005;

int n;
int col[MAXN];              // col[i]：结点 i 的颜色
int fa[MAXN];               // fa[i]：结点 i 的父亲，fa[1] = 0
vector<int> son_list[MAXN]; // son_list[i]：结点 i 的孩子列表

int siz[MAXN];        // siz[u]：子树大小
int heavy[MAXN];      // heavy[u]：u 的重儿子编号，0 表示没有重儿子
bool keep_flag[MAXN]; // keep_flag[u]：算完子树 u 后是否保留统计信息（u 是父亲的重儿子时保留）
int dfn[MAXN];        // dfn[u]：u 的 dfs 序
int euler[MAXN];      // euler[k]：dfs 序为 k 的结点编号
int timer;            // dfs 序计数器
int stk[MAXN];        // 求 dfs 序时用的手写栈
int work_stk[MAXN];   // 模拟 dfs_sack 时用的手写栈
int stage[MAXN];      // stage[u]：结点 u 当前处在 dfs_sack 的哪一步

// 当前统计范围内（一段连续结点）的颜色信息
int cnt[MAXN]; // cnt[c]：颜色 c 出现的次数
int occ[MAXN]; // occ[k]：恰好出现 k 次的颜色种数
int kind;      // 当前统计范围内出现过的颜色种数

ll ans; // 颜色平衡的子树个数

// 把结点 u 的颜色计数加上 delta（delta = +1 或 -1），同时维护 occ 和 kind。
void add_point(int u, int delta) {
    int c = col[u];
    if (cnt[c] > 0) {
        occ[cnt[c]]--; // 颜色 c 的旧次数不再计数
    } else {
        kind++; // 颜色 c 第一次出现
    }
    cnt[c] += delta;
    if (cnt[c] > 0) {
        occ[cnt[c]]++; // 颜色 c 的新次数开始计数
    } else {
        kind--; // 颜色 c 的点全部被移走
    }
}

// 把整棵子树 u 的结点全部加入 / 移出统计范围。
// 子树在 dfs 序上是一段连续的区间，所以这里是一次简单的区间循环。
void add_subtree(int u, int delta) {
    int l = dfn[u];
    int r = dfn[u] + siz[u] - 1;
    for (int i = l; i <= r; i++) {
        add_point(euler[i], delta);
    }
}

// 求子树大小和重儿子。题目保证 fa[i] < i，倒着扫一遍就能把孩子的大小汇总给父亲。
void build_size() {
    for (int i = 1; i <= n; i++) {
        siz[i] = 1;
        heavy[i] = 0;
        keep_flag[i] = false;
    }
    for (int i = n; i >= 2; i--) {
        int f = fa[i];
        siz[f] += siz[i];
        if (siz[i] > siz[heavy[f]]) { // siz[0] 始终为 0，所以 heavy[f] == 0 时也能直接比较
            heavy[f] = i;
        }
    }
    // 重儿子算完后要保留信息给父亲复用，也就是递归版里参数 keep = true 的那些结点。
    keep_flag[1] = true;
    for (int i = 2; i <= n; i++) {
        keep_flag[i] = (heavy[fa[i]] == i);
    }
}

// 手写栈求 dfs 序。把一个点弹出时立刻给它编 dfs 序，再把它的全部孩子压栈。
// 因为栈是后进先出，弹出 u 之后压入的孩子会排在 u 的兄弟之上，
// 所以子树里的点会在 u 之后被连续弹出，每个点的后代恰好构成一段连续区间。
void build_euler() {
    int top = 0;
    stk[++top] = 1;
    timer = 0;
    while (top > 0) {
        int u = stk[top];
        top--;
        timer++;
        dfn[u] = timer;
        euler[timer] = u;
        for (int i = 0; i < (int)son_list[u].size(); i++) {
            stk[++top] = son_list[u][i];
        }
    }
}

// DSU on Tree 主体。
// 递归版每个结点要处理三件事：① 先算所有轻儿子并清空；② 再算重儿子并保留；
// ③ 补上轻儿子和自己，判断答案，最后决定是否清空。
// 这里用 work_stk 模拟这个过程：stage[u] = 0 / 1 / 2 分别表示“还没开始”“轻儿子刚算完”
// “重儿子刚算完”，以便同一个结点被访问三次时做不同的事。
// 用迭代而不用递归，是为了防止链状数据（深度可达 2e5）把递归栈压爆。
void run_sack() {
    int top = 0;
    work_stk[++top] = 1;
    stage[1] = 0;

    while (top > 0) {
        int u = work_stk[top];

        if (stage[u] == 0) {
            // 第一次访问 u：把所有轻儿子压栈，让它们各自单独算并清空。
            stage[u] = 1;
            for (int i = (int)son_list[u].size() - 1; i >= 0; i--) {
                int v = son_list[u][i];
                if (v != heavy[u]) {
                    top++;
                    work_stk[top] = v;
                    stage[v] = 0;
                }
            }
            continue;
        }

        if (stage[u] == 1) {
            // 第二次访问 u：轻儿子都算完并清空了，再算重儿子，作为 u 的“底子”。
            stage[u] = 2;
            if (heavy[u] != 0) {
                top++;
                work_stk[top] = heavy[u];
                stage[heavy[u]] = 0;
            }
            continue;
        }

        // 第三次访问 u：此时统计范围正好是子树重儿子，补上轻儿子子树和 u 自己，
        // 得到的就恰好是整棵子树 u。
        for (int i = 0; i < (int)son_list[u].size(); i++) {
            int v = son_list[u][i];
            if (v != heavy[u]) {
                add_subtree(v, 1);
            }
        }
        add_point(u, 1);

        // 判断子树 u 是否颜色平衡。
        // 设子树大小为 S、出现过的颜色数为 kind。
        // 每种颜色点数都相同 <=> 每种颜色都出现 S / kind 次 <=> kind 整除 S 且 occ[S / kind] == kind。
        if (siz[u] % kind == 0 && occ[siz[u] / kind] == kind) {
            ans++;
        }

        // 轻儿子要把信息清掉；重儿子（含 u 的整棵子树）留给父亲复用。
        if (!keep_flag[u]) {
            add_subtree(u, -1);
        }
        top--;
    }
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> col[i] >> fa[i];
    }
}

void solve() {
    for (int i = 2; i <= n; i++) {
        son_list[fa[i]].push_back(i);
    }
    build_size();
    build_euler();
    run_sack();
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
