/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:43
 * update_at: 2026-10-06 12:43
 */
// roj/2089 漫游小镇：N×N 网格的哈密顿路径计数（左上角农场 -> 左下角集市）。
// 做法：DFS + 位掩码维护访问状态 + 三大可行性剪枝（区域切割 / 度 1 死胡同 / 度 0 判死）。

#include <cstdio>

typedef long long ll;
typedef unsigned long long ull;

const int MAXC = 49; // N<=7，最多 7*7=49 个格子

int n;      // 网格边长
int cells;  // 格子总数 n*n
int target; // 集市（左下角）的格子编号

ull full;          // 全部格子都访问的掩码
ull tbit;          // 集市对应的单比特掩码
ull pb[MAXC];      // pb[i]：只含第 i 位的掩码，避免反复写 1<<i
ull nmask[MAXC];   // nmask[i]：i 的四个相邻格子组成的掩码（越界不计）
ull side[MAXC][4]; // side[i]：i 的左/右/上/下邻居的单比特掩码，越界记 0

int deg[MAXC]; // deg[i]：i 当前的未访问邻居数，随搜索增量维护
ull ones;      // 度恰好为 1 的未访问非集市格掩码，是「死胡同」剪枝的信号
ull zeros;     // 度为 0 的未访问非集市格掩码，一旦出现即无解

ll answer; // 路径条数

bool inGrid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

// 从 pos 出发、已访问集合为 vis、还剩 left 个格子未走时，走向集市的路径数。
void dfs(int pos, ull vis, int left) {
    if (pos == target) { // 走到集市：必须同时走完全部格子
        if (left == 0) answer++;
        return;
    }
    ull unvis = full ^ vis;

    // 剪枝 1（区域切割）：当前格左右都被封死（越界或已访问）而上下都未访问，
    // 或上下被封死而左右都未访问；走出当前格后未访问区域会被切成两半，永远走不完。
    ull l = side[pos][0], r = side[pos][1], u = side[pos][2], d = side[pos][3];
    bool lBlock = (l == 0) || ((l & vis) != 0);
    bool rBlock = (r == 0) || ((r & vis) != 0);
    bool uBlock = (u == 0) || ((u & vis) != 0);
    bool dBlock = (d == 0) || ((d & vis) != 0);
    if ((lBlock && rBlock && !uBlock && !dBlock) ||
        (uBlock && dBlock && !lBlock && !rBlock)) {
        return;
    }

    ull avail = nmask[pos] & unvis; // 当前格可走的未访问邻居
    if (avail == 0) return;         // 四面皆堵却还没走完

    // 集市与所有可走邻居都不相邻，且已无未访问邻居，将来无法进入。
    if ((avail & tbit) == 0 && deg[target] == 0) return;

    // 存在度 0 的非集市格：那个格子永远进不去也出不来。
    if (zeros != 0) return;

    // 剪枝 2（死胡同）：度 1 的格子只能「一进一出」，必须紧贴当前格成为下一步，
    // 否则它将成为死角；若同时出现两个度 1 格则无法都照顾到，直接剪掉。
    int forced = -1;
    int forcedCnt = 0;
    ull f = ones;
    while (f != 0) {
        int w = __builtin_ctzll(f);
        f &= f - 1;
        if (w == pos) continue;
        if ((nmask[pos] & pb[w]) == 0) return;
        forced = w;
        forcedCnt++;
    }
    if (forcedCnt > 1) return;

    // 组织候选下一步：有强制步就只走它；否则把可用邻居按度数小的优先枚举，
    // 尽早撞墙，从而更早触发剪枝。
    int moves[MAXC];
    int moveCnt = 0;
    if (forcedCnt == 1) {
        moves[moveCnt++] = forced;
    } else {
        int candDeg[MAXC];
        int candId[MAXC];
        int candCnt = 0;
        ull a = avail;
        while (a != 0) {
            int w = __builtin_ctzll(a);
            a &= a - 1;
            candDeg[candCnt] = deg[w];
            candId[candCnt] = w;
            candCnt++;
        }
        for (int i = 0; i < candCnt; i++) { // 选择排序：按度数升序
            int best = i;
            for (int j = i + 1; j < candCnt; j++) {
                if (candDeg[j] < candDeg[best]) best = j;
            }
            int td = candDeg[i];
            candDeg[i] = candDeg[best];
            candDeg[best] = td;
            int ti = candId[i];
            candId[i] = candId[best];
            candId[best] = ti;
            moves[i] = candId[i];
        }
        moveCnt = candCnt;
    }

    for (int mi = 0; mi < moveCnt; mi++) {
        int x = moves[mi];
        // 集市必须是最后一格，因此还剩多于一个格子时不能进集市。
        if (x == target && left > 1) continue;

        // 离开 pos：把 pos 当作已访问，它的每个未访问邻居度数 -1，并同步 ones/zeros。
        ull nb = nmask[pos] & unvis;
        ull t = nb;
        while (t != 0) {
            int w = __builtin_ctzll(t);
            t &= t - 1;
            deg[w]--;
            if (w != target) {
                if (deg[w] == 1) { zeros &= ~pb[w]; ones |= pb[w]; }
                else if (deg[w] == 0) { ones &= ~pb[w]; zeros |= pb[w]; }
                else { ones &= ~pb[w]; zeros &= ~pb[w]; }
            }
        }
        ones &= ~pb[pos];
        zeros &= ~pb[pos];

        dfs(x, vis | pb[pos], left - 1);

        // 回溯：恢复邻居度数以及 ones/zeros，再把 pos 按原度数重新登记。
        t = nb;
        while (t != 0) {
            int w = __builtin_ctzll(t);
            t &= t - 1;
            deg[w]++;
            if (w != target) {
                if (deg[w] == 1) { zeros &= ~pb[w]; ones |= pb[w]; }
                else if (deg[w] == 0) { ones &= ~pb[w]; zeros |= pb[w]; }
                else { ones &= ~pb[w]; zeros &= ~pb[w]; }
            }
        }
        if (deg[pos] == 1) ones |= pb[pos];
        else if (deg[pos] == 0) zeros |= pb[pos];
    }
}

int main() {
    scanf("%d", &n);
    cells = n * n;
    target = (n - 1) * n; // 左下角的编号
    full = (1ULL << cells) - 1;
    for (int i = 0; i < cells; i++) pb[i] = 1ULL << i;
    tbit = pb[target];

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int r = 0; r < n; r++) { // 预计算每个格子的邻居掩码和四向掩码
        for (int c = 0; c < n; c++) {
            int i = r * n + c;
            nmask[i] = 0;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (inGrid(nr, nc)) nmask[i] |= pb[nr * n + nc];
            }
            side[i][0] = inGrid(r, c - 1) ? pb[r * n + c - 1] : 0;
            side[i][1] = inGrid(r, c + 1) ? pb[r * n + c + 1] : 0;
            side[i][2] = inGrid(r - 1, c) ? pb[(r - 1) * n + c] : 0;
            side[i][3] = inGrid(r + 1, c) ? pb[(r + 1) * n + c] : 0;
        }
    }

    ones = 0;
    zeros = 0;
    for (int i = 0; i < cells; i++) deg[i] = __builtin_popcountll(nmask[i]);
    for (int i = 0; i < cells; i++) { // 集市不参与度 1/0 的判定
        if (i == target) continue;
        if (deg[i] == 1) ones |= pb[i];
        else if (deg[i] == 0) zeros |= pb[i];
    }

    answer = 0;
    dfs(0, pb[0], cells - 1); // 起点是左上角
    printf("%lld\n", answer);
    return 0;
}
