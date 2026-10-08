/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:43
 * update_at: 2026-10-07 21:43
 */
// 1752《纪念碑》：二分答案 + 扫描线求矩形面积并
//
// 边长 L 的正方形由它的左下角 (lx,ly) 唯一确定：lx∈[1,W]、ly∈[1,H]，
// 其中 W=n-L+1、H=m-L+1（放不下就是不可行）。建筑 (x1,y1,x2,y2) 会挡住所有
// 两个方向都相交的左下角，即矩形 xl∈[max(1,x1-L+1), min(W,x2)]、
// yl∈[max(1,y1-L+1), min(H,y2)]。于是：
//     存在 L×L 的空正方形 <=> 这 p 个「禁止矩形」没有盖满 W×H。
// 可行性关于 L 单调（L 可行则 L-1 可行），所以二分 L，每轮用扫描线求矩形面积并。
//
// 线段树直接建在真实 y 坐标的单位区间上（2^20 > 1e6，无需坐标压缩），
// 采用迭代式 Klee 算法：区间加、维护整棵子树被覆盖的总长度，更新只走两条边界路径。

#include <cstdio>
#include <cstring>
#pragma GCC optimize("O3")   // 本题最坏点要跑 ~1.6e7 次线段树区间加，开 O3 压常数

const int MAXP = 400005;         // p 的上限
const int TREE_SHIFT = 20;       // 叶子数 2^20 = 1048576 > m 的上限 1e6
const int N = 1 << TREE_SHIFT;   // 第 i 个叶子代表 y 的单位区间 [i, i+1)

struct Rect { int x1, y1, x2, y2; };  // 一幢建筑：左下角、右上角
struct Span { int xl, xr, yl, yr; };  // 它禁止的左下角区域，y 方向为半开区间 [yl, yr)

static Rect rect[MAXP];
static Span span[MAXP];
static int usableList[MAXP];          // 禁止区域与可行域相交非空的建筑下标
static int addOrd[MAXP], remOrd[MAXP];// 按 xl / xr 升序的下标，即扫描线的进入/离开顺序
static int bucket[1000005];           // 计数排序的桶，键值域 [1, W]
static int cnt[4 * N];                // 结点被整段覆盖的次数
static int cov[4 * N];                // 结点范围内被覆盖的 y 长度；下标 >= 2N 的恒为 0
static int segLen[2 * N];             // 结点 i 代表的 y 长度（单位个数）

static int n, m, p, W, H, usableCnt;

// 区间 [l, r) 加 v（v = +1 进入、-1 离开）。叶子的孩子恒为 0，所以无需判叶子；
// 两条边界路径合并向上回溯，公其先祖（LCA）以下只各走一次，省掉一半的回溯。
static inline void update(int l, int r, int v) {
    int L = l + N, R = r + N;
    const int lift = L >> 1, rit = (R - 1) >> 1;
    while (L < R) {
        if (L & 1) { cnt[L] += v; cov[L] = cnt[L] > 0 ? segLen[L] : cov[L << 1] + cov[L << 1 | 1]; ++L; }
        if (R & 1) { --R; cnt[R] += v; cov[R] = cnt[R] > 0 ? segLen[R] : cov[R << 1] + cov[R << 1 | 1]; }
        L >>= 1; R >>= 1;
    }
    int a = lift, b = rit;
    while (a != b) {   // 两条路径同深度，必然同时到达 LCA
        cov[a] = cnt[a] > 0 ? segLen[a] : cov[a << 1] + cov[a << 1 | 1];
        cov[b] = cnt[b] > 0 ? segLen[b] : cov[b << 1] + cov[b << 1 | 1];
        a >>= 1; b >>= 1;
    }
    for (; a; a >>= 1) cov[a] = cnt[a] > 0 ? segLen[a] : cov[a << 1] + cov[a << 1 | 1];
}

// 计数排序：把 usableList[0..usableCnt) 按 xl（byLeft 真）或 xr 升序写进 dst
static void countingSort(int *dst, int byLeft) {
    int i, key, pos;
    for (i = 1; i <= W; ++i) bucket[i] = 0;
    for (i = 0; i < usableCnt; ++i) {
        key = byLeft ? span[usableList[i]].xl : span[usableList[i]].xr;
        ++bucket[key];
    }
    pos = 0;
    for (i = 1; i <= W; ++i) {
        int c = bucket[i];
        bucket[i] = pos;
        pos += c;
    }
    for (i = 0; i < usableCnt; ++i) {
        int id = usableList[i];
        key = byLeft ? span[id].xl : span[id].xr;
        dst[bucket[key]++] = id;
    }
}

// 判定：是否存在边长 L 的空正方形（即禁止矩形没盖满可行域）
static bool check(int L) {
    W = n - L + 1;
    H = m - L + 1;
    if (W < 1 || H < 1) return false;   // 网格里根本放不下 L×L
    int i, k;
    usableCnt = 0;
    for (i = 0; i < p; ++i) {
        int xl = rect[i].x1 - L + 1; if (xl < 1) xl = 1;
        int xr = rect[i].x2;         if (xr > W) xr = W;
        int yl = rect[i].y1 - L + 1; if (yl < 1) yl = 1;
        int yr = rect[i].y2 + 1;     if (yr > H + 1) yr = H + 1;
        if (xl > xr || yl >= yr) continue;          // 与可行域不相交，挡不住任何位置
        span[i].xl = xl; span[i].xr = xr; span[i].yl = yl; span[i].yr = yr;
        usableList[usableCnt++] = i;
    }
    if (usableCnt == 0) return true;                // 一个都挡不住
    countingSort(addOrd, 1);
    countingSort(remOrd, 0);

    memset(cnt, 0, sizeof(int) * (2 * N));   // 只有 [1, 2N) 会被写，更高下标恒为 0
    memset(cov, 0, sizeof(int) * (2 * N));
    int ja = 0, jr = 0;
    long long area = 0;
    const long long total = (long long)W * H;
    int prevX = 1;
    while (ja < usableCnt || jr < usableCnt) {
        int xa = ja < usableCnt ? span[addOrd[ja]].xl : W + 1;
        int xb = jr < usableCnt ? span[remOrd[jr]].xr + 1 : W + 1;
        int cur = xa < xb ? xa : xb;
        if (cur > prevX) {
            if (cov[1] < H) return true;      // 这一整段里有一列没被盖满 -> 那里任一点都是空正方形
            area += (long long)(cur - prevX) * cov[1];
            if (area >= total) return false;  // 可行域已被盖满
            prevX = cur;
        }
        while (ja < usableCnt && span[addOrd[ja]].xl == cur) {
            k = addOrd[ja++];
            update(span[k].yl, span[k].yr, 1);
        }
        while (jr < usableCnt && span[remOrd[jr]].xr + 1 == cur) {
            k = remOrd[jr++];
            update(span[k].yl, span[k].yr, -1);
        }
    }
    if (cov[1] < H) return true;
    area += (long long)(W + 1 - prevX) * cov[1];
    return area < total;
}

// ── 读入：把整个 stdin 一次性读进缓冲区再自己解析，省掉 scanf 的开销 ──
static char buf[1 << 25];
static int bufLen, bufPos;

static inline int nextInt() {
    while (bufPos < bufLen && (buf[bufPos] < '0' || buf[bufPos] > '9') && buf[bufPos] != '-') ++bufPos;
    bool neg = false;
    if (bufPos < bufLen && buf[bufPos] == '-') { neg = true; ++bufPos; }
    int x = 0;
    while (bufPos < bufLen && buf[bufPos] >= '0' && buf[bufPos] <= '9') {
        x = x * 10 + (buf[bufPos] - '0');
        ++bufPos;
    }
    return neg ? -x : x;
}

int main() {
    bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
    bufPos = 0;
    for (int i = 1; i < N; ++i) segLen[i] = N >> (31 - __builtin_clz(i));
    for (int i = N; i < 2 * N; ++i) segLen[i] = 1;   // 叶子代表一个单位长度
    while (true) {
        while (bufPos < bufLen && (buf[bufPos] < '0' || buf[bufPos] > '9')) ++bufPos;
        if (bufPos >= bufLen) break;      // 输入读完（跳过尾部空白后无数字）
        n = nextInt(); m = nextInt(); p = nextInt();
        for (int i = 0; i < p; ++i) {
            int a = nextInt(), b = nextInt(), c = nextInt(), d = nextInt();
            if (a > c) { int t = a; a = c; c = t; }   // 容错：题面保证给出左下、右上
            if (b > d) { int t = b; b = d; d = t; }
            rect[i].x1 = a; rect[i].y1 = b; rect[i].x2 = c; rect[i].y2 = d;
        }
        int lo = 0, hi = n < m ? n : m, ans = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
