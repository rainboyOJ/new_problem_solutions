/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:09
 * update_at: 2026-10-24 09:40
 */
// main.cpp：P4342 [IOI 1998] Polygon 正解。
// 破环成链 + 双状态区间 DP：对每条断边各跑一次区间 DP，取最高分，并把所有取到最高分的断边按编号升序输出。
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 105;

int n;
int v[maxn];      // v[i]：输入第 i 组给的顶点权值（顶点 i 在环上）
char op[maxn];    // op[i]：输入第 i 组给的运算符，'t' 表示 +，'x' 表示 *

int chain_v[2 * maxn];     // chain_v[p]：断点 break_id 展开成链后，第 p 个顶点的权值
char chain_op[2 * maxn];   // chain_op[p]：链上顶点 p 与 p+1 之间的运算符

ll f[2 * maxn][2 * maxn]; // f[i][j]：区间 [i,j] 合并成一个顶点时，权值的最大值
ll g[2 * maxn][2 * maxn]; // g[i][j]：区间 [i,j] 合并成一个顶点时，权值的最小值

// 把原环按断边 break_id 展开成链。
// 输入按「op[i] v[i]」成对给出，v[i] 是第 i 号顶点，op[i] 是第 i 号边。
// 断掉第 break_id 条边后：
//   链上第 p 个顶点 = 输入第 (break_id+p-2) mod n + 1 号顶点（依次 v[break_id], v[break_id+1], ...）；
//   链上第 p 条边   = 输入第 (break_id+p-1) mod n + 1 号边（依次 op[break_id+1], op[break_id+2], ...）。
// 注意顶点与边的下标错开一位：删掉的是边 break_id，所以顶点从 break_id 起、边从 break_id+1 起。
// 这套下标对应关系与题目样例（33 / 1 2）及 IOI'98 官方五组测试的答案完全一致。
void build_chain(int break_id) {
    for (int p = 1; p <= n; p++) {
        int vertex_id = ((break_id + p - 2 + n) % n) + 1;
        chain_v[p] = v[vertex_id];
        if (p < n) {
            int edge_id = ((break_id + p - 1) % n) + 1;   // 链上第 1 条边是 op[break_id+1]
            chain_op[p] = op[edge_id];
        }
    }
}

// 对当前链做双状态区间 DP，把整条链合并成一个顶点后的最大/最小权值写入 best_max / best_min
// f[i][j] 只保留最大值、g[i][j] 只保留最小值：乘法的极值一定来自两个子区间极值的组合
void solve_chain(ll &best_max, ll &best_min) {
    for (int i = 1; i <= n; i++) {
        f[i][i] = chain_v[i];
        g[i][i] = chain_v[i];
    }
    for (int len = 2; len <= n; len++) {        // 区间长度从小到大，保证子区间已算好
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            f[i][j] = LLONG_MIN;
            g[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {       // 最后一步：把 [i,k] 与 [k+1,j] 用第 k 条边合并
                ll left_max = f[i][k], left_min = g[i][k];
                ll right_max = f[k + 1][j], right_min = g[k + 1][j];
                ll val[4];
                int cnt = 0;
                if (chain_op[k] == 't') {       // 加法：极值来自两个子区间各自的极值
                    val[cnt++] = left_max + right_max;
                    val[cnt++] = left_min + right_min;
                } else {                        // 乘法：四种极值组合里必含真正的最大值与最小值
                    val[cnt++] = left_max * right_max;
                    val[cnt++] = left_max * right_min;
                    val[cnt++] = left_min * right_max;
                    val[cnt++] = left_min * right_min;
                }
                for (int t = 0; t < cnt; t++) {
                    if (val[t] > f[i][j]) f[i][j] = val[t];
                    if (val[t] < g[i][j]) g[i][j] = val[t];
                }
            }
        }
    }
    best_max = f[1][n];
    best_min = g[1][n];
}

void read_data(){
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op[i] >> v[i];    // 输入按「边 1 的运算符、顶点 1 的权值、边 2 的运算符、…」交错给出
    }
}

void solve(){
    ll answer = LLONG_MIN;
    ll best[maxn];              // best[break_id]：删掉第 break_id 条边后能得到的最高分
    for (int break_id = 1; break_id <= n; break_id++) {
        build_chain(break_id);
        ll cur_max = 0, cur_min = 0;
        solve_chain(cur_max, cur_min);
        best[break_id] = cur_max;
        if (cur_max > answer) answer = cur_max;
    }

    // 第二行：所有能取到最优分数的第一步删除边，按编号递增输出
    cout << answer << "\n";
    bool first = true;
    for (int break_id = 1; break_id <= n; break_id++) {
        if (best[break_id] == answer) {
            if (!first) cout << " ";
            cout << break_id;
            first = false;
        }
    }
    cout << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();
    solve();
    return 0;
}
