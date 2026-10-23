/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:34
 * update_at: 2026-10-23 15:05
 */
// main.cpp：线段树优化建图 + Tarjan 缩点 + DAG 上传递可达区间。
// 关于栈：图中存在一条 n = 5e5 长的炸弹引爆链，实测递归 Tarjan 的最大递归深度达 750017 层，
// 用 roj-local-judge-lite --stack 实测要 60MB 栈才不崩（--stack 8/16/32/48/56 全部 RE signal 11），
// 紧贴判题器 64MB 默认栈、没有任何余量，因此本题的 Tarjan 必须用显式栈迭代实现。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 500005;   // 炸弹个数上限
const int MAXM = 1 << 20;  // 线段树节点编号上界（n = 5e5 时 m = 2^19 = 524288）
const ll MOD = 1000000007;

int n;                   // 炸弹个数
int m;                   // 不小于 n 的最小 2 的幂，炸弹 i 的叶子编号为 m + i - 1
ll x[MAXN];              // x[i]：第 i 个炸弹的坐标（严格递增）
ll r[MAXN];              // r[i]：第 i 个炸弹的爆炸半径
int lo[MAXN], hi[MAXN];  // [lo[i], hi[i]]：第 i 个炸弹直接引爆的炸弹下标区间
int node_cnt;            // 图中节点总数 = m + n - 1

// 图用 CSR（压缩稀疏行）存储：节点 u 的出边是 adj_to[adj_start[u] .. adj_start[u+1])。
// 本题边数接近 1e7，链式前向星要 3 个 int 数组约 120MB，CSR 只要 2 个数组且遍历更快。
vector<int> adj_start;
vector<int> adj_to;
int edge_cnt;  // 已写入 adj_to 的边数

// 炸弹 i 在图中对应的叶子节点编号
int leaf_of(int bomb) {
    return m + bomb - 1;
}

// 输入最多 1e6 个 64 位整数（约 20MB 文本），一次性读入再按下标解析，比 scanf 快一倍以上
vector<char> input_buf;
size_t input_pos;

void load_input() {
    size_t len = 0;
    input_buf.resize(1 << 20);
    while (true) {
        if (len == input_buf.size()) input_buf.resize(input_buf.size() * 2);
        size_t got = fread(input_buf.data() + len, 1, input_buf.size() - len, stdin);
        if (got == 0) break;
        len += got;
    }
    input_buf.resize(len + 1);
    input_buf[len] = '\0';  // 哨兵，保证解析最后一个数时读不到越界字符
    input_pos = 0;
}

// 跳过空白等分隔符并吃掉负号，返回这个数是否为负
bool read_sign() {
    while (input_buf[input_pos] != '-' && (input_buf[input_pos] < '0' || input_buf[input_pos] > '9')) {
        input_pos++;
    }
    if (input_buf[input_pos] == '-') {
        input_pos++;
        return true;
    }
    return false;
}

ll read_long() {
    bool negative = read_sign();
    ll value = 0;
    while (input_buf[input_pos] >= '0' && input_buf[input_pos] <= '9') {
        value = value * 10 + (input_buf[input_pos] - '0');
        input_pos++;
    }
    return negative ? -value : value;
}

int read_small() {
    bool negative = read_sign();
    int value = 0;
    while (input_buf[input_pos] >= '0' && input_buf[input_pos] <= '9') {
        value = value * 10 + (input_buf[input_pos] - '0');
        input_pos++;
    }
    return negative ? -value : value;
}

// 在 x[1..n] 中找第一个 >= value 的下标；找不到返回 n + 1
int first_not_less(ll value) {
    int left = 1, right = n + 1;  // 答案区间是半开区间 [1, n+1]
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (x[mid] >= value) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// 在 x[1..n] 中找最后一个 <= value 的下标；找不到返回 0
int last_not_greater(ll value) {
    int left = 0, right = n;  // 答案区间是半开区间 [0, n]
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (x[mid] <= value) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

// 读入炸弹坐标与半径，并二分出每个炸弹「直接引爆」的下标区间
void read_input() {
    load_input();
    n = read_small();
    for (int i = 1; i <= n; i++) {
        x[i] = read_long();
        r[i] = read_long();
    }
    for (int i = 1; i <= n; i++) {
        lo[i] = first_not_less(x[i] - r[i]);
        hi[i] = last_not_greater(x[i] + r[i]);
    }
    input_buf.clear();
    input_buf.shrink_to_fit();  // 后面的图结构要占几十 MB，先把输入缓冲还回去
}

// 追加一条出边（CSR 靠 push_back 顺序填充，adj_start 记录每条边段的起点）
void add_edge(int v) {
    adj_to.push_back(v);
    edge_cnt++;
}

// 建图：
//   1. 线段树的内部节点 u 向左右儿子连边，使「走到这个节点」等于「走到它覆盖的全部叶子」；
//   2. 炸弹叶子向「它直接引爆的下标区间」在线段树上的 O(log n) 个规范节点连边。
// 节点按编号升序处理，正好是「先内部节点、后叶子（即炸弹顺序）」，所以一趟就能填好 CSR。
void build_graph() {
    m = 1;
    while (m < n) m <<= 1;
    node_cnt = m + n - 1;

    adj_start.assign(node_cnt + 2, 0);
    adj_to.clear();
    adj_to.reserve(2 * (m - 1) + 20 * n + 8);
    edge_cnt = 0;

    for (int u = 1; u <= node_cnt; u++) {
        adj_start[u] = edge_cnt;
        if (u < m) {
            // 线段树内部节点：连向左右儿子，编号超过实际叶子范围的儿子不存在
            for (int child = 2 * u; child <= 2 * u + 1; child++) {
                if (child <= node_cnt) add_edge(child);
            }
        } else {
            // 叶子 u 就是炸弹 i，向 [lo[i], hi[i]] 的规范分解节点连边
            int i = u - m + 1;
            int left = m + lo[i] - 1;
            int right = m + hi[i] - 1;
            while (left <= right) {
                if (left & 1) add_edge(left++);
                if (!(right & 1)) add_edge(right--);
                left >>= 1;
                right >>= 1;
            }
        }
    }
    adj_start[node_cnt + 1] = edge_cnt;
}

int dfn[MAXM + MAXN];        // dfn[u]：Tarjan 时间戳，0 表示还没访问
int low[MAXM + MAXN];        // low[u]：u 及其 DFS 子树能回溯到的最小 dfn
int scc[MAXM + MAXN];        // scc[u]：u 所属强连通分量编号（从 1 开始）
char in_stack[MAXM + MAXN];  // u 是否还在顶点栈上，只有 0/1，用 char 省 3MB 内存
int dfs_clock;
int scc_cnt;

int vstack[MAXM + MAXN];  // Tarjan 的顶点栈
int vstack_top;

// 每次弹出一个 SCC，就把它的成员按顺序写进 pop_order，
// 于是编号 id 的成员正好是 pop_order[scc_begin[id] .. scc_begin[id+1])。
int pop_order[MAXM + MAXN];
int scc_begin[MAXM + MAXN];
int pop_cnt;

struct Frame {
    int u;    // 这一层正在处理的节点
    int idx;  // 这一层枚举到哪条出边
};
Frame frames[MAXM + MAXN];  // 手写的调用栈，替代递归（原因见文件头）

// 迭代版 Tarjan。SCC 编号按「汇点先被弹出」的顺序递增，
// 因此任意边 A -> B 都满足 scc[A] > scc[B]，编号递增本身就是拓扑序。
void tarjan() {
    for (int root = 1; root <= node_cnt; root++) {
        if (dfn[root] != 0) continue;
        int top = 1;
        frames[1].u = root;
        frames[1].idx = adj_start[root];
        dfn[root] = low[root] = ++dfs_clock;
        vstack[++vstack_top] = root;
        in_stack[root] = 1;

        while (top > 0) {
            int u = frames[top].u;
            int idx = frames[top].idx;
            if (idx < adj_start[u + 1]) {
                int v = adj_to[idx];
                frames[top].idx = idx + 1;
                if (dfn[v] == 0) {
                    // 树边：进入 v
                    dfn[v] = low[v] = ++dfs_clock;
                    vstack[++vstack_top] = v;
                    in_stack[v] = 1;
                    top++;
                    frames[top].u = v;
                    frames[top].idx = adj_start[v];
                } else if (in_stack[v] && dfn[v] < low[u]) {
                    // 只有还留在栈上的点才能更新 low
                    low[u] = dfn[v];
                }
                continue;
            }

            // u 的所有出边都走完了，回溯，把 low 传给父节点
            top--;
            if (top > 0) {
                int parent = frames[top].u;
                if (low[u] < low[parent]) low[parent] = low[u];
            }
            if (low[u] == dfn[u]) {
                // u 是本 SCC 在 DFS 树上的最高点，弹出整块
                scc_cnt++;
                while (true) {
                    int w = vstack[vstack_top--];
                    in_stack[w] = 0;
                    scc[w] = scc_cnt;
                    pop_order[pop_cnt++] = w;
                    if (w == u) break;
                }
                scc_begin[scc_cnt + 1] = pop_cnt;
            }
        }
    }
}

// 缩点后按拓扑序（SCC 编号递增）传播每个 SCC 能引爆的炸弹区间。
// 「能引爆的炸弹」一定是连续一段，所以只需维护区间左右端点：
// 用 min/max 合并，重复到达同一个炸弹也不会算重。
void propagate() {
    // SCC_MIN 初值取 +inf、SCC_MAX 初值取 0，只含线段树节点的 SCC 会被算成空区间
    vector<int> scc_min(scc_cnt + 2, INT_MAX);
    vector<int> scc_max(scc_cnt + 2, 0);
    for (int i = 1; i <= n; i++) {
        int id = scc[leaf_of(i)];
        if (i < scc_min[id]) scc_min[id] = i;
        if (i > scc_max[id]) scc_max[id] = i;
    }

    for (int id = 1; id <= scc_cnt; id++) {
        for (int p = scc_begin[id]; p < scc_begin[id + 1]; p++) {
            int u = pop_order[p];
            for (int e = adj_start[u]; e < adj_start[u + 1]; e++) {
                int v = adj_to[e];
                int j = scc[v];
                if (j == id) continue;  // SCC 内部的边不带来新信息
                if (scc_min[j] < scc_min[id]) scc_min[id] = scc_min[j];
                if (scc_max[j] > scc_max[id]) scc_max[id] = scc_max[j];
            }
        }
    }

    ll answer = 0;
    for (int i = 1; i <= n; i++) {
        int id = scc[leaf_of(i)];
        ll weight = i;                             // 第 i 个炸弹的权值，顺手提升成 ll
        ll reachable = scc_max[id] - scc_min[id] + 1;  // 第 i 个炸弹能引爆的个数
        answer = (answer + weight * reachable) % MOD;
    }
    printf("%lld\n", answer);
}

int main() {
    read_input();
    build_graph();
    tarjan();
    propagate();
    return 0;
}
