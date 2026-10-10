/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:46
 * update_at: 2026-10-08 06:46
 */
// 1992 书架book（同 [ZJOI2006] 书架 / 洛谷 P2596）
//
// 算法：树状数组（BIT）维护“位置是否被占” + 每个书编号映射到具体位置。
//
// 关键观察：Top / Bottom 只会把书放到序列的首/尾，Insert 只在相邻位置之间交换，
// 因此可以把整个序列摆进一个“足够宽的连续坐标轴”里：
//   - 初始时第 i 本书放在坐标 BASE + i 处，BASE 上方预留下 m 个空位；
//   - Top S    : 把 S 搬到当前左侧游标 lo 处（lo 每次左移一格）；
//   - Bottom S : 把 S 搬到当前右侧游标 hi 处（hi 每次右移一格）；
//   - Insert S T: 与“排名相差 T 的那本书”直接交换坐标（坐标集合不变，BIT 不用动）；
//   - Ask S    : S 的排名 = 坐标 <= pos[S] 的书本数量，即 BIT 前缀和；
//   - Query S  : BIT 上二分（倍增）找第 S 个 1 所在坐标，再查该坐标上的书。
// 每个操作都是 O(log n)，总复杂度 O((n + m) log n)。
//
// 复杂度之上还有一层常量优势：BIT 的常数远小于平衡树，n, m <= 8e4 时非常轻松。
#include <cstdio>

const int MAXN = 80005;
const int MAXM = 80005;
const int MAXP = 2 * MAXM + MAXN + 10; // 坐标轴长度：预留 m 个顶部空位 + n 本书 + m 个底部空位

typedef long long ll;

int n, m;
int bit[MAXP];   // 树状数组：坐标 x 上有没有书
int rev[MAXP];   // rev[x] = 坐标 x 上的书的编号（0 表示空位）
int pos[MAXN];   // pos[v] = 书 v 当前所在坐标
int lo, hi;      // lo: 下一次 Top 使用的坐标；hi: 下一次 Bottom 使用的坐标

// 树状数组单点加减
void add(int x, int delta) {
    for (; x < MAXP; x += x & -x) bit[x] += delta;
}

// 树状数组前缀和：坐标 <= x 的书本数量
int sum(int x) {
    int s = 0;
    for (; x > 0; x -= x & -x) s += bit[x];
    return s;
}

// 倍增求第 k 个 1 所在的坐标（k 从 1 开始）
int kth(int k) {
    int x = 0;
    for (int step = 1 << 18; step; step >>= 1) { // 2^18 > MAXP，从大到小倍增
        if (x + step < MAXP && bit[x + step] < k) {
            x += step;
            k -= bit[x];
        }
    }
    return x + 1;
}

int main() {
    scanf("%d %d", &n, &m);

    const int BASE = m + 5;  // 初始书堆的起点：左边留 m 格给 Top，右边留 m 格给 Bottom
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        int x = BASE + i;
        pos[v] = x;
        rev[x] = v;
        add(x, 1);
    }
    lo = BASE;
    hi = BASE + n;

    char op[16];
    for (int i = 0; i < m; i++) {
        int s, t = 0;
        scanf("%s %d", op, &s);
        if (op[0] == 'T') {           // Top S：搬到最上面
            int p = pos[s];
            add(p, -1);
            rev[p] = 0;
            lo--;
            pos[s] = lo;
            rev[lo] = s;
            add(lo, 1);
        } else if (op[0] == 'B') {    // Bottom S：搬到最下面
            int p = pos[s];
            add(p, -1);
            rev[p] = 0;
            hi++;
            pos[s] = hi;
            rev[hi] = s;
            add(hi, 1);
        } else if (op[0] == 'I') {    // Insert S T：与排名相差 T 的书交换坐标
            scanf("%d", &t);
            if (t == 0) continue;
            int p = pos[s];
            int k = sum(p);           // s 当前的 1-indexed 排名
            int q = kth(k + t);       // 相邻的那本书的坐标
            int other = rev[q];
            // 两本书互换坐标：坐标集合没变，所以 BIT 不需要改动
            rev[p] = other;
            rev[q] = s;
            pos[other] = p;
            pos[s] = q;
        } else if (op[0] == 'A') {    // Ask S：S 上面有多少本书
            printf("%d\n", sum(pos[s] - 1));
        } else {                      // Query S：从上数第 S 本书的编号
            printf("%d\n", rev[kth(s)]);
        }
    }
    return 0;
}
