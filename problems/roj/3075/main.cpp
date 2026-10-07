/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:39
 * update_at: 2026-10-06 17:39
 */

// main.cpp：Square Destroyer 正解，IDA* 求解重复覆盖问题。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5;                 // 网格最大规模
const int MAXS = 64;                // 正方形数量上限：n=5 时共 55 个
const int MAXM = 64;                // 火柴数量上限：n=5 时共 60 根

int n;                              // 当前网格规模
int sq_cnt;                         // 幸存正方形数量
ll sq_mask[MAXS];                   // 每个正方形覆盖哪些火柴（位掩码）
int sq_stick[MAXS][4];              // 每个正方形的 4 根火柴编号
int sq_stick_len[MAXS];             // 每个正方形的边长（即火柴数）
ll stick_sq_mask[MAXM];             // 每根火柴参与哪些正方形（位掩码）
ll full;                            // 当前状态下还有哪些正方形幸存

// 生成所有正方形，按边长从小到大排列，并过滤已被破坏的
void build_grid(int m, bool missing[]) {
    int dd = 2 * m + 1;             // 每行展平后的位置数
    sq_cnt = 0;
    for (int size = 1; size <= m; size++) {
        for (int i = 0; i + size <= m; i++) {
            for (int j = 0; j + size <= m; j++) {
                // 计算正方形四条边上的火柴编号
                int sticks[4 * MAXN];
                int len = 0;
                // 上边和下面的横火柴
                for (int t = 0; t < size; t++) {
                    sticks[len++] = i * dd + j + t + 1;
                    sticks[len++] = (i + size) * dd + j + t + 1;
                }
                // 左边和右边的竖火柴
                for (int t = 0; t < size; t++) {
                    sticks[len++] = (i + t) * dd + j + m + 1;
                    sticks[len++] = (i + t) * dd + j + size + m + 1;
                }
                // 若该正方形已被缺失火柴破坏，则跳过
                bool broken = false;
                for (int t = 0; t < len; t++) {
                    if (missing[sticks[t]]) {
                        broken = true;
                        break;
                    }
                }
                if (broken) continue;
                sq_mask[sq_cnt] = 0;
                for (int t = 0; t < len; t++) {
                    sq_mask[sq_cnt] |= (1LL << sticks[t]);
                    sq_stick[sq_cnt][t] = sticks[t];
                }
                sq_stick_len[sq_cnt] = size;
                sq_cnt++;
            }
        }
    }
}

// 估价函数：贪心选取互不相交（无公共火柴）的幸存正方形个数，作为下界
int lower_bound(ll state) {
    int cnt = 0;
    ll taken = 0;                   // 已被选中正方形占用的火柴
    for (int i = 0; i < sq_cnt; i++) {
        if ((state >> i) & 1LL) {
            if ((sq_mask[i] & taken) == 0) {
                cnt++;
                taken |= sq_mask[i];
            }
        }
    }
    return cnt;
}

// 每根火柴按参与正方形数排序后的分支顺序缓存
int branch_order[MAXS][4];
int branch_order_len[MAXS];

// IDA* 深度优先搜索：剩余 budget 次抽取能否破坏 state 中所有正方形
bool dfs(int budget, ll state) {
    if (state == 0) return true;
    if (budget == 0) return false;
    int lb = lower_bound(state);
    if (lb > budget) return false;
    // 找到 state 中第一个（即边长最小）幸存的正方形
    int pos = 0;
    while (pos < sq_cnt && ((state >> pos) & 1LL) == 0) pos++;
    // 枚举抽走该正方形的一根火柴
    for (int t = 0; t < branch_order_len[pos]; t++) {
        int s = branch_order[pos][t];
        if (dfs(budget - 1, state & ~stick_sq_mask[s])) return true;
    }
    return false;
}

// 比较函数：按火柴参与正方形数降序排列
int stick_deg[MAXM];

bool cmp_stick(int a, int b) {
    return stick_deg[a] > stick_deg[b];
}

int solve_case(int m, bool missing[]) {
    build_grid(m, missing);
    if (sq_cnt == 0) return 0;
    // 初始化每根火柴参与哪些幸存正方形
    int max_stick = 2 * m * (m + 1);
    for (int s = 1; s <= max_stick; s++) stick_sq_mask[s] = 0;
    for (int i = 0; i < sq_cnt; i++) {
        for (int t = 0; t < 4 * sq_stick_len[i]; t++) {
            int s = sq_stick[i][t];
            stick_sq_mask[s] |= (1LL << i);
        }
    }
    // 计算每根火柴参与的正方形数，并预处理每个正方形的分支顺序
    for (int s = 1; s <= max_stick; s++) {
        stick_deg[s] = __builtin_popcountll(stick_sq_mask[s]);
    }
    for (int i = 0; i < sq_cnt; i++) {
        int len = 4 * sq_stick_len[i];
        branch_order_len[i] = len;
        for (int t = 0; t < len; t++) branch_order[i][t] = sq_stick[i][t];
        sort(branch_order[i], branch_order[i] + len, cmp_stick);
    }
    full = (1LL << sq_cnt) - 1;
    int start = lower_bound(full);
    if (start < 1) start = 1;
    // IDA* 逐层加深
    for (int depth = start; ; depth++) {
        if (dfs(depth, full)) return depth;
    }
    return -1; // 不可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        int k;
        cin >> k;
        static bool missing[MAXM];
        int max_stick = 2 * n * (n + 1);
        for (int i = 1; i <= max_stick; i++) missing[i] = false;
        for (int i = 0; i < k; i++) {
            int x;
            cin >> x;
            missing[x] = true;
        }
        cout << solve_case(n, missing) << "\n";
    }
    return 0;
}
