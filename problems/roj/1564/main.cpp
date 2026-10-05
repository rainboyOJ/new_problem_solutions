/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:36
 * update_at: 2026-10-05 08:46
 */
// 树链剖分把路径拆成 O(log n) 段 dfn 区间；每种信仰单独一份结构：
// 成员集合静态可预算（初始信仰 + 所有 CC 指定的新信仰），成员的 dfn 固定，
// 按 dfn 升序建成静态位置表；dfn 区间两次二分翻译成连续秩区间，
// 秩区间求和用树状数组、求最大值用完全二叉树线段树，单点改值 O(log n)。
// 取值约定：城市 x 在信仰 c 结构里的值 = w_x（若 belief[x] == c）否则 0，
// 评级恒为正，0 是安全的中性元（不贡献和，也抢不走最大值）。

#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;

const int MAXN = 100005;      // n, q <= 1e5：城市数与操作数上限
const int MAXM = 2 * MAXN;    // 成员总数不超过 n + q

int n, q;

// 树结构（链式前向星）
int head_[MAXN], nxt[MAXN << 1], to[MAXN << 1], cnt_edge = 0;
// 树剖用：父亲、深度、子树大小、重儿子、重链顶、dfn 编号（dfn 从 0 开始）
int fa[MAXN], dep[MAXN], sz[MAXN], heavy_[MAXN], top_[MAXN], dfn[MAXN];
int order_[MAXN], order_cnt = 0; // 第一遍 DFS 的访问序
int dfn_node[MAXN];              // dfn -> 城市编号，建位置表时反查

ll weight[MAXN];   // 每座城市当前评级
int belief[MAXN];  // 每座城市当前信仰
ll cur_val[MAXN];  // 城市 x 当前在自己信仰结构里的取值（其余结构里视为 0）

struct Query {     // 一条操作：两个字符 + 两个参数
    char op[3];
    ll x, y;
} qs[MAXN];

// ---- 按信仰分堆的静态结构 ----
int pos_sorted[MAXM];         // 所有信仰的位置表依次存放：按 dfn 升序的城市编号
int table_start[MAXM];        // 信仰 c 的位置表在 pos_sorted 里的起始下标
int table_len[MAXM];          // 信仰 c 的位置表长度
// 注意：一个城市可能同时出现在多张表里（初始信仰表 + CC 目标信仰表），
// 所以「x 在信仰 c 表中的秩」不能存成单值，要按 dfn 在表内二分得到。
ll keys[MAXM];                // 预算成员用的键：c * (n+1) + dfn[x]，排序去重

ll bit[MAXM];                // 树状数组：各信仰的表分段共用一个前缀空间（ll 防前缀和溢出）
ll seg_tree[MAXM * 4];        // 完全二叉树线段树，各信仰的树依次存放
int seg_base[MAXM];           // 信仰 c 的线段树堆区在 seg_tree 里的起始下标
int seg_size[MAXM];           // 信仰 c 的线段树叶子数（2 的幂）
ll ans_out[MAXN];             // 每条查询的输出，最后统一打印

// 加边
void add_edge(int a, int b) {
    cnt_edge++;
    nxt[cnt_edge] = head_[a];
    to[cnt_edge] = b;
    head_[a] = cnt_edge;
}

// 第一遍 DFS（迭代，防链形树爆栈）：求父亲、深度、访问序，再逆序算子树大小与重儿子
void dfs_size() {
    static int stk[MAXN];
    int tp = 0;
    stk[++tp] = 1;
    fa[1] = 0;
    dep[1] = 0;
    while (tp) {
        int u = stk[tp--];
        order_[++order_cnt] = u;
        for (int e = head_[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa[u]) {
                fa[v] = u;
                dep[v] = dep[u] + 1;
                stk[++tp] = v;
            }
        }
    }
    for (int i = order_cnt; i >= 1; i--) { // 逆访问序：儿子先于父亲被处理
        int u = order_[i];
        sz[u] = 1;
        int big = 0; // 子树最大的儿子
        for (int e = head_[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa[u]) {
                sz[u] += sz[v];
                if (big == 0 || sz[v] > sz[big]) big = v;
            }
        }
        heavy_[u] = big;
    }
}

// 第二遍（迭代）：沿重链优先给 dfn 编号，每条重链拿到一段连续 dfn
void dfs_dfn() {
    static int stk[MAXN];
    int tp = 0;
    stk[++tp] = 1;
    top_[1] = 1;
    int clock_ = 0;
    while (tp) {
        int u = stk[tp--];
        int h = top_[u];
        for (int w = u; w; w = heavy_[w]) { // 沿重链一路走到叶子
            dfn[w] = clock_;
            dfn_node[clock_] = w;
            clock_++;
            top_[w] = h;
            // 轻儿子各自成链，压栈稍后处理
            for (int e = head_[w]; e; e = nxt[e]) {
                int v = to[e];
                if (v != fa[w] && v != heavy_[w]) {
                    top_[v] = v;
                    stk[++tp] = v;
                }
            }
        }
    }
}

// 把路径 x -> y 拆成若干段连续 dfn 闭区间，存进 span_l / span_r
int span_l[70], span_r[70]; // 单条路径最多约 2*log2(n) 段，70 足够
int span_cnt = 0;
void path_spans(int x, int y) {
    span_cnt = 0;
    while (top_[x] != top_[y]) { // 不在同一条链上，摘链顶更深的一侧整段
        if (dep[top_[x]] < dep[top_[y]]) {
            int t = x; x = y; y = t;
        }
        span_cnt++;
        span_l[span_cnt] = dfn[top_[x]];
        span_r[span_cnt] = dfn[x];
        x = fa[top_[x]];
    }
    if (dep[x] > dep[y]) { // 同链时浅的是 LCA，收尾一段
        int t = x; x = y; y = t;
    }
    span_cnt++;
    span_l[span_cnt] = dfn[x];
    span_r[span_cnt] = dfn[y];
}

// ---- 树状数组（1 起）：单点加 / 前缀和，全长 MAXM，各信仰的表分段共用 ----
void fenwick_add(int i, int delta) {
    for (; i < MAXM; i += i & (-i)) bit[i] += delta;
}
ll fenwick_sum(int i) {
    ll s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

// 把信仰 c 的线段树第 i 个叶子（0 起）改成 v，并回溯更新祖先的最大值
void seg_update(int c, int i, ll v) {
    int base = seg_base[c], size = seg_size[c];
    int j = size + i; // 转成堆下标
    seg_tree[base + j] = v;
    for (j >>= 1; j >= 1; j >>= 1) {
        seg_tree[base + j] = std::max(seg_tree[base + (j << 1)], seg_tree[base + (j << 1 | 1)]);
    }
}

// 信仰 c 的线段树区间最大值：叶子区间 [l, r) 内的最大值，空区间记 0
ll seg_max(int c, int l, int r) {
    int base = seg_base[c], size = seg_size[c];
    ll res = 0;
    l += size;
    r += size;
    while (l < r) {
        if (l & 1) { res = std::max(res, seg_tree[base + l]); l++; }
        if (r & 1) { r--; res = std::max(res, seg_tree[base + r]); }
        l >>= 1;
        r >>= 1;
    }
    return res;
}

// 在信仰 c 的位置表里二分：返回第一个 dfn >= v 的秩（0 起）
int bisect_first(int c, int v) {
    int lo = table_start[c], hi = table_start[c] + table_len[c]; // [lo, hi)
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (dfn[pos_sorted[mid]] < v) lo = mid + 1; else hi = mid;
    }
    return lo - table_start[c];
}

// 在信仰 c 的位置表里二分：返回第一个 dfn > v 的秩（0 起）
int bisect_last(int c, int v) {
    int lo = table_start[c], hi = table_start[c] + table_len[c];
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (dfn[pos_sorted[mid]] <= v) lo = mid + 1; else hi = mid;
    }
    return lo - table_start[c];
}

// 把城市 x 在信仰 c 结构里的取值改成 v（v=0 表示 x 当前不信仰 c）。
// x 的 dfn 必在 c 的表里（成员全集已预算），秩由表内二分得到。
// 树状数组只吃增量：旧值可由 cur_val 推出（x 只在 belief[x] 的表里非 0）。
void paint(int c, int x, ll v) {
    ll oldv = 0;
    if (belief[x] == c) oldv = cur_val[x];
    if (oldv == v) return;
    if (belief[x] == c) cur_val[x] = v;
    int i = bisect_first(c, dfn[x]);
    seg_update(c, i, v);
    fenwick_add(table_start[c] + i + 1, v - oldv);
}

// 查询 x->y 路径上信仰 c 的评级和 / 最大值
ll query_sum(int x, int y, int c) {
    path_spans(x, y);
    ll res = 0;
    for (int k = 1; k <= span_cnt; k++) {
        int i1 = bisect_first(c, span_l[k]);
        int i2 = bisect_last(c, span_r[k]);
        if (i2 > i1) {
            res += fenwick_sum(table_start[c] + i2) - fenwick_sum(table_start[c] + i1);
        }
    }
    return res;
}
ll query_max(int x, int y, int c) {
    path_spans(x, y);
    ll res = 0; // 评级恒为正且端点必命中，0 不会被返回
    for (int k = 1; k <= span_cnt; k++) {
        int i1 = bisect_first(c, span_l[k]);
        int i2 = bisect_last(c, span_r[k]);
        if (i2 > i1) {
            res = std::max(res, seg_max(c, i1, i2));
        }
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld %d", &weight[i], &belief[i]);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    for (int i = 1; i <= q; i++) scanf("%s %lld %lld", qs[i].op, &qs[i].x, &qs[i].y);

    dfs_size();
    dfs_dfn();

    // 预算成员全集：初始 n 个 + 所有 CC 事件的目标成员，键排序去重后按信仰分组。
    // 键 = c * (n+1) + dfn[x]：同键去重即同 (信仰, 城市) 去重，组内天然按 dfn 升序。
    int cnt_keys = 0;
    for (int i = 1; i <= n; i++) {
        keys[cnt_keys++] = (ll)belief[i] * (n + 1) + dfn[i];
    }
    for (int i = 1; i <= q; i++) {
        if (qs[i].op[0] == 'C' && qs[i].op[1] == 'C') {
            keys[cnt_keys++] = (ll)qs[i].y * (n + 1) + dfn[qs[i].x];
        }
    }
    std::sort(keys, keys + cnt_keys);
    cnt_keys = (int)(std::unique(keys, keys + cnt_keys) - keys);

    // 分组建表：每种信仰一段位置表 + 一棵 2 的幂叶子的线段树
    int mem_cnt = 0;   // 已放入 pos_sorted 的成员数
    int seg_top = 1;   // seg_tree 已用到的堆下标（从 1 开始，各树顺次存放）
    for (int k = 0; k < cnt_keys; k++) {
        int c = (int)(keys[k] / (n + 1));
        int d = (int)(keys[k] % (n + 1));
        if (k == 0 || c != (int)(keys[k - 1] / (n + 1))) {
            // 新信仰：先收尾上一棵树（无），再为本信仰开表开树
            table_start[c] = mem_cnt;
            table_len[c] = 0;
            int size = 1;
            while (size < 1) size <<= 1; // 占位，下面按整组长度再定
            // 叶子数先按组内剩余数量上界暂定，整组结束时用实际长度重定不划算，
            // 因此先扫出该信仰的成员个数
            int j = k;
            while (j < cnt_keys && (int)(keys[j] / (n + 1)) == c) j++;
            int len = j - k;
            int size2 = 1;
            while (size2 < len) size2 <<= 1;
            seg_base[c] = seg_top; // 堆区占 2*size2 个下标（含 0 号不用）
            seg_size[c] = size2;
            for (int t = 0; t < 2 * size2; t++) seg_tree[seg_top + t] = 0;
            seg_top += 2 * size2;
        }
        int x = dfn_node[d];
        pos_sorted[mem_cnt] = x;
        mem_cnt++;          // 秩 = mem_cnt - table_start[c] - 1，用时按 dfn 表内二分
        table_len[c]++;
    }
    for (int i = 1; i <= n; i++) { // 初始全员在自己的信仰里
        cur_val[i] = weight[i];
        int c = belief[i];
        int r = bisect_first(c, dfn[i]);
        int base = seg_base[c], size = seg_size[c];
        seg_tree[base + size + r] = weight[i];
        fenwick_add(table_start[c] + r + 1, weight[i]);
    }
    // 初始写值后自底向上建各信仰线段树：直接对每个内部节点取两儿子最大值
    for (int k = 0; k < cnt_keys; k++) {
        int c = (int)(keys[k] / (n + 1));
        if (k > 0 && c == (int)(keys[k - 1] / (n + 1))) continue;
        int base = seg_base[c], size = seg_size[c];
        for (int j = size - 1; j >= 1; j--) {
            seg_tree[base + j] = std::max(seg_tree[base + (j << 1)], seg_tree[base + (j << 1 | 1)]);
        }
    }

    // 逐条处理操作
    int out_cnt = 0;
    for (int i = 1; i <= q; i++) {
        int x = (int)qs[i].x;
        if (qs[i].op[0] == 'Q') {
            int c = belief[x]; // 查询只问 c_x 这一种信仰
            if (qs[i].op[1] == 'S') ans_out[++out_cnt] = query_sum(x, (int)qs[i].y, c);
            else ans_out[++out_cnt] = query_max(x, (int)qs[i].y, c);
        } else if (qs[i].op[1] == 'W') { // CW x w：改评级，刷自己信仰那一份
            weight[x] = qs[i].y;
            paint(belief[x], x, weight[x]);
        } else { // CC x c：旧信仰置 0，新信仰置 w_x
            int c = (int)qs[i].y;
            if (belief[x] != c) {
                paint(belief[x], x, 0);
                belief[x] = c;
                paint(c, x, weight[x]);
            }
        }
    }
    for (int i = 1; i <= out_cnt; i++) printf("%lld\n", ans_out[i]);
    return 0;
}
