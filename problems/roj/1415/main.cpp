/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-17 23:02
 * update_at: 2026-10-17 23:02
 */
// main.cpp：矩形加、点查询——二维差分 + 二维树状数组。
//
// 1416（静态覆盖计数）的做法是：把「矩形覆盖」沿 x 拆成进/出事件，
// y 方向用差分 + 一维树状数组，靠一次扫描线把 x 维度消掉。
// 本题多了一个维度——时间：加矩形与查询交替出现，x 不能提前扫完。
// 于是把 1416 的「一维差分 + 前缀和」整体升到二维：
//
//   D 为二维差分数组。矩形 [l,r) x [d,u) 加 w 等价于 4 个单点加：
//     D(l,d) += w,  D(l,u) -= w,  D(r,d) -= w,  D(r,u) += w
//   点 (x,y) 的答案 = sum_{x'<=x, y'<=y} D(x',y')（二维前缀和）
//
// 二维前缀和/单点加用「树状数组套树状数组」：外层按 x 建 BIT，
// 每个外层节点再按 y 建一个 BIT。x、y 都先离线收集所有出现过的坐标做离散化，
// 这样不用真的开 1e9 * 1e9 的数组。单次操作 O(log^2)。

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXOP = 200005; // 操作上限：初始 N 个矩形 + Q 次操作，N、Q <= 1e5

// 一条操作：type = 0 加矩形，type = 1 查询点
struct Op {
    int type;
    int l, d, r, u; // type 0：矩形 [l,r) x [d,u)
    ll w;           // type 0：矩形权值
    int x, y;       // type 1：询问点 (x,y)
};

Op op[MAXOP]; // 全部操作，按输入顺序
int q_cnt;    // 操作个数

int xs[MAXOP * 4]; // 离散化用的 x 坐标：矩形的 l、r 与询问的 x
int nx;            // 去重后的 x 个数

vector<int> col[MAXOP * 4];   // col[i]：外层节点 i 的内层 y 坐标，升序去重
vector<ll> bit[MAXOP * 4];    // bit[i]：外层节点 i 对应的一维树状数组

// 离散化表：值 -> 1 起的名次
int rank_of(int value, int table[], int n) {
    return lower_bound(table + 1, table + n + 1, value) - table;
}

// 把 (x, y) 这个点登记到外层 x 路径上，供后面建内层 y 表用
void prepare_point(int x, int y) {
    for (int i = rank_of(x, xs, nx); i <= nx; i += i & -i) col[i].push_back(y);
}

// 内层单点加：外层节点 i 里，把 y 名次 j 处加上 v
void inner_add(int i, int j, ll v) {
    int m = col[i].size();
    for (; j <= m; j += j & -j) bit[i][j] += v;
}

// 内层前缀和：外层节点 i 里，y 名次 <= j 的和
ll inner_sum(int i, int j) {
    ll s = 0;
    for (; j > 0; j -= j & -j) s += bit[i][j];
    return s;
}

// 二维单点加：D(x, y) += v。x 走外层 BIT，y 走每个外层节点的内层 BIT
void add_point(int x, int y, ll v) {
    for (int i = rank_of(x, xs, nx); i <= nx; i += i & -i) {
        // 同一个外层节点里，内层用 upper_bound 找到 y 的名次
        int j = lower_bound(col[i].begin(), col[i].end(), y) - col[i].begin() + 1;
        inner_add(i, j, v);
    }
}

// 二维前缀和：sum_{x'<=x, y'<=y} D(x', y')
ll prefix_sum(int x, int y) {
    ll s = 0;
    for (int i = rank_of(x, xs, nx); i > 0; i -= i & -i) {
        // 内层要取 <= y 的所有列，用 upper_bound 得到名次上界
        int j = upper_bound(col[i].begin(), col[i].end(), y) - col[i].begin();
        s += inner_sum(i, j);
    }
    return s;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int xs_cnt = 0; // 收集到的 x 坐标个数，后面排序去重得到外层 BIT 长度
    // 初始矩形直接当成一开始就发生的「加矩形」操作
    for (int i = 1; i <= n; i++) {
        op[++q_cnt].type = 0;
        scanf("%d %d %d %d %lld", &op[q_cnt].l, &op[q_cnt].d, &op[q_cnt].r, &op[q_cnt].u, &op[q_cnt].w);
        xs[++xs_cnt] = op[q_cnt].l;
        xs[++xs_cnt] = op[q_cnt].r;
    }
    for (int i = 1; i <= q; i++) {
        int t;
        scanf("%d", &t);
        op[++q_cnt].type = t;
        if (t == 0) {
            scanf("%d %d %d %d %lld", &op[q_cnt].l, &op[q_cnt].d, &op[q_cnt].r, &op[q_cnt].u, &op[q_cnt].w);
            xs[++xs_cnt] = op[q_cnt].l;
            xs[++xs_cnt] = op[q_cnt].r;
        } else {
            scanf("%d %d", &op[q_cnt].x, &op[q_cnt].y);
            xs[++xs_cnt] = op[q_cnt].x;
        }
    }

    // x 离散化：外层 BIT 的下标
    sort(xs + 1, xs + xs_cnt + 1);
    nx = unique(xs + 1, xs + xs_cnt + 1) - (xs + 1);
    // y 不单独做全局离散化：每个外层节点的内层 y 表 col[i] 各管自己那一段

    // 预处理：把所有会出现的点（矩形的 4 个差分角 + 询问点）登记到外层路径上，
    // 这样每个外层节点需要的内层 y 集合就确定了
    for (int i = 1; i <= q_cnt; i++) {
        if (op[i].type == 0) {
            prepare_point(op[i].l, op[i].d);
            prepare_point(op[i].l, op[i].u);
            prepare_point(op[i].r, op[i].d);
            prepare_point(op[i].r, op[i].u);
        } else {
            prepare_point(op[i].x, op[i].y);
        }
    }
    for (int i = 1; i <= nx; i++) {
        sort(col[i].begin(), col[i].end());
        col[i].erase(unique(col[i].begin(), col[i].end()), col[i].end());
        bit[i].assign(col[i].size() + 1, 0); // 下标 0 占位
    }

    // 按时间顺序处理：加矩形写 4 个差分点，查询取二维前缀和
    for (int i = 1; i <= q_cnt; i++) {
        if (op[i].type == 0) {
            int l = op[i].l, r = op[i].r, d = op[i].d, u = op[i].u;
            ll w = op[i].w;
            add_point(l, d, w);
            add_point(l, u, -w);
            add_point(r, d, -w);
            add_point(r, u, w);
        } else {
            printf("%lld\n", prefix_sum(op[i].x, op[i].y));
        }
    }
    return 0;
}
