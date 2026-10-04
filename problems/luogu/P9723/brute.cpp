/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:55
 *
 * P9723 [EC Final 2022] Chinese Checker —— 暴力对拍解
 *
 * 思路完全照抄题面，不做任何优化：
 *   1. 枚举移动的棋子 a；
 *   2. 从 a 的起点开始 DFS：枚举棋盘上每个别的棋子 b 当 pivot，
 *      若 a、b 连线平行于三个轴之一，就逐格检查题面的三条限制：
 *        - 除 b 外，a 到对称点的中间格必须为空；
 *        - 对称点 q = 2b - a 必须在盘内、且为空；
 *        - q 不能是 a 的起点 p0（不允许走回去）。
 *      满足就走一步，并且每一步之后都可以选择停下；
 *   3. 每个终局用"所有棋子所在格编号排序后的序列"表示，丢进 set 去重。
 *
 * 只有当 n 很小（生成器限制 n <= 8）时才能跑得动。
 */
#include <bits/stdc++.h>
using namespace std;

const int CELLS = 121 + 5;
const int OFFSET = 15;   // 轴向坐标 -12..12 平移到 0..30
const int WIDTH = 40;

int row_len[17] = {1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1};

int row_of[CELLS], x_of[CELLS];
int id_at[20][WIDTH];    // (行, 平移后的轴向坐标) -> 格编号，-1 表示不在盘上
int cell_cnt;

// 六个方向：(行变化, 轴向坐标变化)
int dr6[6] = {0, 0, 1, 1, -1, -1};
int dx6[6] = {2, -2, 1, -1, 1, -1};

int n;
int start_cell[20];      // 输入的棋子所在格
bool occ[CELLS];
bool reached[CELLS];    // 本次 a 已经到过的位置（避免绕圈无限递归）

set<vector<int> > finals;   // 去重后的终局集合

// u 沿方向 d 走一步的格编号，出界返回 -1
int next_cell(int u, int d) {
    int r = row_of[u] + dr6[d];
    int x = x_of[u] + dx6[d];
    if (r < 1 || r > 17) return -1;
    if (x < 0 || x >= WIDTH) return -1;
    return id_at[r][x];
}

void build_board() {
    memset(id_at, -1, sizeof(id_at));
    cell_cnt = 0;
    for (int r = 1; r <= 17; r++) {
        int len = row_len[r - 1];
        for (int c = 1; c <= len; c++) {
            int x = OFFSET - (len - 1) + 2 * (c - 1);
            cell_cnt++;
            id_at[r][x] = cell_cnt;
            row_of[cell_cnt] = r;
            x_of[cell_cnt] = x;
        }
    }
}

void dfs(int a, int pos, int p0) {
    // pos == p0 表示还没走出任何一步，不算一个 move；否则当前位置就是一个终局
    if (pos != p0) {
        vector<int> conf;
        for (int i = 1; i <= n; i++) {
            if (i == a) continue;              // 跳过正在移动的那颗棋子
            conf.push_back(start_cell[i]);
        }
        conf.push_back(pos);
        sort(conf.begin(), conf.end());
        finals.insert(conf);
    }

    for (int b = 1; b <= n; b++) {
        int bc = start_cell[b];
        if (b == a) continue;       // pivot 必须是另一颗棋子

        // 找 pos -> bc 的方向（必须同轴）
        int d = -1;
        for (int k = 0; k < 6; k++) {
            int cur = pos;
            while (true) {
                cur = next_cell(cur, k);
                if (cur == -1) break;
                if (cur == bc) { d = k; break; }
            }
            if (d != -1) break;
        }
        if (d == -1) continue;      // 不在同一条轴上

        // 数出 pos 到 bc 有多少步
        int step = 0, cur = pos;
        while (true) {
            cur = next_cell(cur, d);
            if (cur == -1) break;
            step++;
            if (cur == bc) break;
        }

        // 对称点 q = pos 沿 d 走 2*step 步
        cur = pos;
        bool bad = false;
        for (int t = 1; t <= 2 * step; t++) {
            cur = next_cell(cur, d);
            if (cur == -1) { bad = true; break; }
        }
        if (bad) continue;          // 对称点出界
        int q = cur;
        if (occ[q]) continue;       // 落点被占（含 q == bc 的情形）
        if (q == p0) continue;      // 不允许回到移动前的位置
        if (reached[q]) continue;   // 该位置之前已到过，再走只会重复

        // 中间格（严格夹在 pos 与 q 之间）除 bc 外必须为空
        bool ok = true;
        cur = pos;
        for (int t = 1; t <= 2 * step - 1; t++) {
            cur = next_cell(cur, d);
            if (cur == bc) continue;
            if (occ[cur]) { ok = false; break; }
        }
        if (!ok) continue;

        // 落子，继续搜索
        occ[pos] = false;
        occ[q] = true;
        reached[q] = true;
        dfs(a, q, p0);
        reached[q] = false;
        occ[q] = false;
        occ[pos] = true;
    }
}

int main() {
    build_board();
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(occ, 0, sizeof(occ));
        for (int i = 1; i <= n; i++) {
            int r, c;
            scanf("%d %d", &r, &c);
            int len = row_len[r - 1];
            int x = OFFSET - (len - 1) + 2 * (c - 1);
            start_cell[i] = id_at[r][x];
            occ[start_cell[i]] = true;
        }
        finals.clear();
        for (int a = 1; a <= n; a++) {
            int p0 = start_cell[a];
            occ[p0] = false;                 // a 离开起点
            memset(reached, 0, sizeof(reached));
            reached[p0] = true;
            dfs(a, p0, p0);
            occ[p0] = true;
        }
        printf("%d\n", (int)finals.size());
    }
    return 0;
}
