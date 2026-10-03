/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 *
 * P9247 [集训队互测 2018] 完美的队列
 *
 * 关键转化：
 *   1. 队列 i 永远只保留"最后 a_i 个压进它的操作"，所以操作 j 压入的值 x_j
 *      在所有覆盖 j 的队列里都还活着，当且仅当 j 之后覆盖该队列的操作数 < a_i。
 *   2. 定义 last[j] = max_{i in [l_j, r_j]}（使第 i 个队列里 x_j 被弹出的最早时刻），
 *      则 x_j 的存活区间就是 [j, last[j] - 1]（last[j] = m+1 表示活到最后）。
 *   3. 最后一遍时间轴扫描 + 桶：在 t 时刻加入 x_t，在 last[j] 时刻删除 x_j，
 *      维护"出现过几次的值种类数"即可。
 *
 * 计算 last 用分块（块长 sqrt(n)）：
 *   对每个块，把所有与它有交的操作按时间排成一列，
 *   整块操作（完全覆盖块）走"整体加法 + 块内最大剩余容量"的双指针；
 *   散块操作走"逐点双指针"，并用前缀和把中间整块操作一次性算出来。
 *   每个操作至多对两个块是散块，总复杂度 O((n + m) sqrt(n))。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;

int n, m;
int a[maxn];                 // 每个队列的容量
int ql[maxn], qr[maxn], qx[maxn]; // 每次操作的 l, r, x

int blockSize, blockCnt;     // 块长、块数
int blkL[maxn], blkR[maxn];  // 每个块的左右端点

// ---------- 整块影响（整块操作整体打标记，散块操作暴力重算） ----------
int curL, curR;              // 当前正在处理的块
int capTmp[maxn];            // capTmp[i] = a_i 减去块内散块操作对 i 的贡献
int gMx;                     // max_i capTmp[i]
int gAdd;                    // 整块操作的个数（整体加标记），即整块操作对每个位置的贡献

// ---------- 散块影响（逐点双指针 + 前缀和） ----------
int allOp[maxn];             // 当前块所有相关操作的时刻，末尾放哨兵 m+1
int prefixFull[maxn];        // 前缀和：相关操作中整块操作的个数
int scatterPos[maxn];        // 散块操作在 allOp 中的下标
int siz;                     // 相关操作个数
int pointIdx;                // 散块操作个数
int gMaxAdd;                 // 单点当前窗口里覆盖它的操作个数（含整块操作的贡献）

int lastOp[maxn];            // 操作 j 的存活右端点（不含），初始 0

// ---------- 扫描线 ----------
int cntVal[maxn];            // 每个值当前被多少个队列持有
vector<int> dieAt[maxn];     // dieAt[t] = 在 t 时刻死亡的操作编号

int maxInt(int x, int y) { return x > y ? x : y; }

// 把第 curr 个操作加入（val = 1）或移出（val = -1）整块影响的状态。
// 整块操作只动整体标记；散块操作需要在块内逐点暴力修改并重算最大值。
void applyOpt(int curr, int val) {
    int l = ql[curr], r = qr[curr];
    if (l > curR || r < curL) return;              // 与本块无交，直接忽略
    if (l <= curL && curR <= r) { gAdd += val; return; } // 整块操作
    gMx = 0;                                       // 散块操作：块内暴力重算
    for (int i = curL; i <= curR; i++) {
        if (l <= i && i <= r) capTmp[i] -= val;
        if (capTmp[i] > gMx) gMx = capTmp[i];
    }
}

// 整块影响：双指针求所有整块操作对应的 last。
// gMx >= gAdd 说明块内每个位置的元素个数都没超过容量，可以继续往后加操作。
void solveWholeBlock() {
    gMx = 0;
    for (int i = curL; i <= curR; i++) {
        capTmp[i] = a[i];
        if (capTmp[i] > gMx) gMx = capTmp[i];
    }
    gAdd = 0;
    int r = 0;
    for (int l = 1; l <= m; l++) {
        while (r < m && gMx >= gAdd) { // 不断加入，直到某个位置被撑爆
            r++;
            applyOpt(r, 1);
        }
        if (r == m && gMx >= gAdd) r = m + 1; // 一直没爆，视为第 m+1 时刻清空
        // 只有整块操作才由整块影响定 last，散块操作的 last 交给下面逐点处理
        if (ql[l] <= curL && curR <= qr[l]) lastOp[l] = maxInt(lastOp[l], r);
        applyOpt(l, -1); // 左端点右移，去掉第 l 个操作
    }
}

// 散块影响：把第 q 个散块操作加入当前单点窗口。
// isFirst 表示窗口本来为空（此时要把 [上一个散块, 当前散块) 之间的整块操作一次算进来）。
void updatePart(int i, int q, int isFirst, int val) {
    int idx = allOp[scatterPos[q]];
    if (!isFirst) gMaxAdd += (prefixFull[scatterPos[q]] - prefixFull[scatterPos[q - 1]]) * val;
    if (ql[idx] <= i && i <= qr[idx]) gMaxAdd += val;
}

// 左端点右移：删掉第 l 个散块操作（以及它到下一个散块之间的整块操作）。
void delPart(int i, int l) {
    int idx = allOp[scatterPos[l]];
    if (l < pointIdx) gMaxAdd -= prefixFull[scatterPos[l + 1]] - prefixFull[scatterPos[l]];
    if (ql[idx] <= i && i <= qr[idx]) gMaxAdd -= 1;
}

// 散块影响：块内每个点单独跑一次双指针。
// 一个点只关心自己这个队列，所以 mx = a_i 固定；
// 窗口里"覆盖该点"的操作个数 gMaxAdd 一旦超过 a_i 就会弹掉队首。
void solveScatter() {
    siz = 0;
    pointIdx = 0;
    prefixFull[0] = 0;
    for (int t = 1; t <= m; t++) {
        if (ql[t] > curR || qr[t] < curL) continue; // 与本块无交
        siz++;
        allOp[siz] = t;
        if (ql[t] <= curL && curR <= qr[t]) {
            prefixFull[siz] = prefixFull[siz - 1] + 1; // 整块操作
        } else {
            prefixFull[siz] = prefixFull[siz - 1];
            scatterPos[++pointIdx] = siz;             // 记下散块操作的位置
        }
    }
    allOp[siz + 1] = m + 1; // 哨兵

    for (int i = curL; i <= curR; i++) {
        int mx = a[i];
        gMaxAdd = 0;
        int r = 0;
        for (int l = 1; l <= pointIdx; l++) {
            while (r < pointIdx && mx >= gMaxAdd) { // 还能塞，继续加散块操作
                r++;
                updatePart(i, r, l == r, 1);
            }
            int idx = allOp[scatterPos[l]];
            if (ql[idx] <= i && i <= qr[idx]) { // 这个散块操作真的覆盖点 i
                if (mx < gMaxAdd) {             // 回溯一格，回到"恰好还装得下"
                    updatePart(i, r, l == r, -1);
                    r--;
                    int need = mx - gMaxAdd + 1; // 还差几次覆盖才撑爆
                    int t = scatterPos[r] + need;
                    if (t > siz + 1) t = siz + 1; // 后面不够了就活到清空时刻
                    lastOp[idx] = maxInt(lastOp[idx], allOp[t]);
                    r++;
                    updatePart(i, r, l == r, 1);
                } else {
                    int need = mx - gMaxAdd + 1;
                    int t = scatterPos[r] + need;
                    if (t > siz + 1) t = siz + 1;
                    lastOp[idx] = maxInt(lastOp[idx], allOp[t]);
                }
            }
            delPart(i, l);
        }
    }
}

void read_data() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int t = 1; t <= m; t++) cin >> ql[t] >> qr[t] >> qx[t];
}

void solve() {
    blockSize = (int)sqrt((double)n);
    if (blockSize < 1) blockSize = 1;
    blockCnt = (n + blockSize - 1) / blockSize;
    for (int b = 1; b <= blockCnt; b++) {
        blkL[b] = (b - 1) * blockSize + 1;
        blkR[b] = b * blockSize;
        if (blkR[b] > n) blkR[b] = n;
    }

    for (int b = 1; b <= blockCnt; b++) {
        curL = blkL[b];
        curR = blkR[b];
        solveWholeBlock(); // 整块操作决定的 last
        solveScatter();    // 散块操作决定的 last
    }

    // 时间轴扫描：x_j 存活区间 [j, lastOp[j] - 1]
    for (int j = 1; j <= m; j++) dieAt[lastOp[j]].push_back(j);

    int res = 0;
    for (int t = 1; t <= m; t++) {
        if (++cntVal[qx[t]] == 1) res++;          // 加入第 t 次操作的值
        for (size_t k = 0; k < dieAt[t].size(); k++) {
            int j = dieAt[t][k];
            if (--cntVal[qx[j]] == 0) res--;      // 删除在 t 时刻死掉的值
        }
        cout << res << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    read_data();
    solve();
    return 0;
}
