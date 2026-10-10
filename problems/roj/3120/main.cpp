/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 12:32
 * update_at: 2026-10-09 12:32
 */

#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

// 坐标整体 +1 后落在 [1, 1000001]，树状数组下标上界留到 1000005
const int MAX_VAL = 1000005;
// 初始 n 个点 + m 次操作合并后的操作总数，n, m <= 5*10^5 所以不超过 10^6
const int MAX_OPS = 1000005;
// 坐标轴翻转的镜像常数：必须大于最大坐标 10^6，保证 MIRROR - (y+1) >= 1
const int MIRROR = 1000002;
// 树状数组空位的哨兵（比任何真实的 x+y 都小，真实 x+y >= 2）
const int NEG = -0x3f3f3f3f;
// 询问答案的初值，比任何真实距离都大
const ll INF = 0x3f3f3f3f;

struct Op {
    int id; // 0 表示插入点，>0 表示第 id 个询问（id 从 1 开始）
    int x;  // 当前翻转后的横坐标
    int y;  // 当前翻转后的纵坐标
};

// 坐标值 <= 10^6，字段用 int 控制内存：三份 Op 数组共约 36 MB
Op ops[MAX_OPS];      // CDQ 分治当前处理的序列（每遍翻转后重新填入）
Op tmp[MAX_OPS];      // 分治归并时的临时数组
Op orig_ops[MAX_OPS]; // 原始的时间有序序列，id / x / y 建好之后不再改动
ll ans[MAX_OPS];      // ans[i] 记录第 i 个询问当前的最近曼哈顿距离
int bit[MAX_VAL + 5]; // 树状数组：维护 y <= 当前 y 的点里最大的 x + y

int n, m;   // 初始点数、操作数
int op_cnt; // 合并初始点与 m 次操作之后的操作总数
int q_cnt;  // 询问总数，也就是输出行数

// 单点取 max，把 val 插入到树状数组的位置 i
void bit_update(int i, int val) {
    for (; i <= MAX_VAL; i += i & -i) {
        bit[i] = max(bit[i], val);
    }
}

// 询问前缀 [1, i] 里的最大值，空位返回 NEG
int bit_query(int i) {
    int mx = NEG;
    for (; i > 0; i -= i & -i) {
        mx = max(mx, bit[i]);
    }
    return mx;
}

// 撤销一次插入：把 i 及其所有祖先位置清回空位
void bit_reset(int i) {
    for (; i <= MAX_VAL; i += i & -i) {
        bit[i] = NEG;
    }
}

// 用树状数组里已经插入的左下方点，尝试更新询问的答案
void relax(const Op &op) {
    int best = bit_query(op.y);
    if (best != NEG) {
        // 距离 = (xq + yq) - (xi + yi)，xq + yq 上界 2*10^6，答案用 ll 承接
        ll cand = op.x + op.y - best;
        if (cand < ans[op.id]) ans[op.id] = cand;
    }
}

// CDQ 分治：处理 ops[l..r]。时间维由数组顺序天然提供，
// 合并时按 x 归并（保证左半边的 x <= 右半边），树状数组解决 y 维。
void cdq(int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (ops[i].x <= ops[j].x) {
            // 左半边的插入点对右边后续询问可见
            if (ops[i].id == 0) bit_update(ops[i].y, ops[i].x + ops[i].y);
            tmp[k++] = ops[i++];
        } else {
            if (ops[j].id > 0) relax(ops[j]);
            tmp[k++] = ops[j++];
        }
    }
    while (j <= r) {
        if (ops[j].id > 0) relax(ops[j]);
        tmp[k++] = ops[j++];
    }
    // 左半边参与合并的插入点已经用完，回滚它们对树状数组的写入
    for (int p = l; p < i; p++) {
        if (ops[p].id == 0) bit_reset(ops[p].y);
    }
    while (i <= mid) tmp[k++] = ops[i++];
    for (int p = l; p <= r; p++) ops[p] = tmp[p];
}

// 按 (flip_x, flip_y) 把 orig_ops 翻转后填入 ops，再跑一遍 CDQ。
// 曼哈顿距离按象限分四种情况，翻转坐标轴后另外三个象限都化成"左下象限"模型。
void run_pass(int flip_x, int flip_y) {
    for (int i = 1; i <= op_cnt; i++) {
        ops[i] = orig_ops[i];
        if (flip_x) ops[i].x = MIRROR - orig_ops[i].x;
        if (flip_y) ops[i].y = MIRROR - orig_ops[i].y;
    }
    cdq(1, op_cnt);
}

void solve() {
    if (!(cin >> n >> m)) return;

    // 初始的 n 个点可以看作最早发出的 n 次插入操作，与 m 次操作合并在同一序列
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x++; // 坐标 +1，避免树状数组下标为 0
        y++;
        orig_ops[++op_cnt] = {0, x, y};
    }
    for (int i = 0; i < m; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        x++;
        y++;
        if (t == 1) {
            orig_ops[++op_cnt] = {0, x, y};
        } else {
            q_cnt++;
            orig_ops[++op_cnt] = {q_cnt, x, y};
        }
    }

    for (int i = 1; i <= q_cnt; i++) ans[i] = INF;
    for (int i = 0; i <= MAX_VAL; i++) bit[i] = NEG;

    // 四个象限各跑一遍，取最小值即得完整答案
    run_pass(0, 0); // 左下象限
    run_pass(1, 0); // 右下象限
    run_pass(0, 1); // 左上象限
    run_pass(1, 1); // 右上象限

    for (int i = 1; i <= q_cnt; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
