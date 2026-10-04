/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:04
 * update_at: 2026-10-05 06:04
 */
#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 1005; // 挖煤点数：隧道数 N <= 500，最多引入 2*N = 1000 个点
const int MAXM = 2015; // 无向隧道拆成两条有向边，最多 2*N+2
const int MAXB = 505;  // 点双个数不会超过隧道数 N

typedef long long ll;

int head[MAXN];   // 邻接表表头
int from_e[MAXM]; // 有向边起点，弹点双时用来统计顶点
int to_e[MAXM];   // 有向边终点
int nxt_e[MAXM];  // 同一顶点上的下一条边
int edge_cnt;     // 有向边计数，从 2 开始成对加入：i 与 i^1 互为反向边

int dfn[MAXN];    // DFS 编号，0 表示未访问
int low[MAXN];    // 子树经回边能到达的最小 DFS 编号
int is_cut[MAXN]; // 顶点是否为割点
int dfn_clock;

int edge_stack[MAXM]; // 边栈：Tarjan 过程中当前 DFS 路径上的边
int stack_top;

int block_visit[MAXN]; // block_visit[v] == visit_stamp 表示 v 已计入当前点双
int visit_stamp;

vector<int> block[MAXB]; // block[i] 保存第 i 个点双去重后的顶点集合
int block_cnt;

ll need;                  // 最少救援出口数
unsigned long long ways;  // 方案总数，题面保证答案小于 2^64，用无符号 64 位承接

// 加入一条无向边，拆成编号相邻的一对反向边：2 与 3、4 与 5 ……
void add_edge(int u, int v) {
    edge_cnt++;
    from_e[edge_cnt] = u;
    to_e[edge_cnt] = v;
    nxt_e[edge_cnt] = head[u];
    head[u] = edge_cnt;

    edge_cnt++;
    from_e[edge_cnt] = v;
    to_e[edge_cnt] = u;
    nxt_e[edge_cnt] = head[v];
    head[v] = edge_cnt;
}

// 从边栈弹出直到 tree_edge 为止的边，它们构成一个点双；顶点去重后存入 block[]。
void pop_block(int tree_edge) {
    visit_stamp++;
    block_cnt++;
    while (true) {
        int e = edge_stack[stack_top];
        stack_top--;
        int a = from_e[e];
        int b = to_e[e];
        if (block_visit[a] != visit_stamp) {
            block_visit[a] = visit_stamp;
            block[block_cnt].push_back(a);
        }
        if (block_visit[b] != visit_stamp) {
            block_visit[b] = visit_stamp;
            block[block_cnt].push_back(b);
        }
        if (e == tree_edge) break;
    }
}

// Tarjan 求割点与点双连通分量：u 为当前顶点，parent_edge 为进入 u 的边（0 表示根）。
void tarjan(int u, int parent_edge) {
    dfn_clock++;
    dfn[u] = dfn_clock;
    low[u] = dfn_clock;
    int child_cnt = 0; // 根的孩子数，大于 1 时根才是割点

    for (int i = head[u]; i != 0; i = nxt_e[i]) {
        int v = to_e[i];
        if (i == (parent_edge ^ 1)) continue; // 父边的反向边，直接跳过
        if (dfn[v] == 0) {
            child_cnt++;
            stack_top++;
            edge_stack[stack_top] = i;
            tarjan(v, i);
            if (low[v] < low[u]) low[u] = low[v];
            if (low[v] >= dfn[u]) {
                pop_block(i); // u 下方闭合出一个点双
                if (parent_edge != 0) is_cut[u] = 1; // 非根：有孩子无法绕过 u 即为割点
            }
        } else if (dfn[v] < dfn[u]) {
            // 回边：只从 DFS 编号大的一端入栈，避免同一条边入栈两次
            stack_top++;
            edge_stack[stack_top] = i;
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }
    if (parent_edge == 0) is_cut[u] = (child_cnt > 1);
}

// 按每个点双含割点的个数三分类，累加最少出口数、累乘方案数。
void calc_answer() {
    for (int b = 1; b <= block_cnt; b++) {
        ll size = block[b].size();
        ll cut_cnt = 0;
        for (ll j = 0; j < size; j++) {
            if (is_cut[block[b][j]]) cut_cnt++;
        }
        if (cut_cnt == 0) {
            // 整个连通块就是一个点双：出口所在的点坍塌后块内再无出口，至少要 2 个
            need += 2;
            ways *= size * (size - 1) / 2;
        } else if (cut_cnt == 1) {
            // 叶子点双：唯一割点坍塌后与外界隔绝，必须建出口，且只能建在非割点上
            need += 1;
            ways *= size - 1;
        }
        // 含两个及以上割点的点双：总能从另一个存活割点绕出去，不必建出口
    }
    for (int b = 1; b <= block_cnt; b++) {
        block[b].clear();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll tunnel_cnt;
    ll ea[MAXN]; // 当前组每条隧道的两个端点原始编号
    ll eb[MAXN];
    map<ll, int> vertex_id; // 原始挖煤点编号 -> 0 基压缩下标
    int case_no = 0;

    while (cin >> tunnel_cnt && tunnel_cnt != 0) {
        for (ll i = 1; i <= tunnel_cnt; i++) {
            cin >> ea[i] >> eb[i];
        }

        // 顶点编号不连续，压缩成 0 基下标；边从编号 2 开始成对加入
        vertex_id.clear();
        edge_cnt = 1;
        dfn_clock = 0;
        stack_top = 0;
        block_cnt = 0;
        // visit_stamp 不重置：block_visit 靠时间戳去重，必须保持单调递增
        need = 0;
        ways = 1;
        for (int i = 0; i < MAXN; i++) {
            head[i] = 0; // 加边前先清空表头，压缩下标在 0..2N-1 内
        }
        for (ll i = 1; i <= tunnel_cnt; i++) {
            if (vertex_id.find(ea[i]) == vertex_id.end()) {
                int id = vertex_id.size();
                vertex_id[ea[i]] = id;
            }
            if (vertex_id.find(eb[i]) == vertex_id.end()) {
                int id = vertex_id.size();
                vertex_id[eb[i]] = id;
            }
            add_edge(vertex_id[ea[i]], vertex_id[eb[i]]);
        }

        int n = vertex_id.size();
        for (int i = 0; i < n; i++) {
            dfn[i] = 0;
            low[i] = 0;
            is_cut[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            if (dfn[i] == 0) tarjan(i, 0);
        }
        calc_answer();

        case_no++;
        cout << "Case " << case_no << ": " << need << " " << ways << "\n";
    }

    return 0;
}
