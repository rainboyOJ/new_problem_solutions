/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:12
 * update_at: 2026-10-08 02:12
 */

// 一本通 1776《最大值》
// 每组数据给定序列 A 与算子 c（1=and, 2=xor, 3=or），求 max_{i<j} (A_i op A_j)。
// 三个算子各用一种经典做法：
//   c=1 与：逐位贪心，判定“至少 2 个元素包含候选掩码”
//   c=2 异或：0-1 Trie 求最大异或对
//   c=3 或：值域超集(SOS)预处理 + 逐位贪心
#include <cstdio>
#include <cstring>

// 题目数据默认 ll；这里的数组元素都是 < 2^20 的位掩码，用 int 更省内存、位运算更直接
typedef long long ll;

static const int MAXN = 100000 + 5;   // n 上限
static const int MAXB = 20;           // 题面保证 A_i < 2^20
static const int DOM = 1 << MAXB;     // 值域大小 2^20
static const int MAXNODE = MAXN * MAXB + 5;  // Trie 节点上限：每个数 20 层

static int a[MAXN];                   // 当前这组数据的序列，a[i] 是位掩码

// sup[m] != 0 表示序列中存在某个元素包含 m 的全部二进制 1（即 m 是它的子掩码）
static unsigned char sup[DOM];

// Trie 节点：两个孩子（bit=0 / bit=1）
struct TrieNode {
    int child[2];
};

// 动态化静态：TrieNode 数组 + trie_cnt 当分配指针，开点由 new_node 负责
static TrieNode trie[MAXNODE];
static int trie_cnt;

// 开一个新 Trie 节点，返回它的编号
static int new_node(void) {
    trie_cnt++;
    trie[trie_cnt].child[0] = 0;
    trie[trie_cnt].child[1] = 0;
    return trie_cnt;
}

// 取 mx 的最高二进制位编号（mx >= 1）
static int hi_bit(int mx) {
    int h = 0;
    while ((mx >> (h + 1)) != 0) h++;
    return h;
}

// c=1 与运算：从高位到低位贪心。
// 若存在至少 2 个元素都包含候选掩码 cand，则两位元素的 AND 就能保住 cand，
// 这一位可取；谓词“存在一对数使 AND 包含 cand”对 cand 的下降单调，故贪心正确。
static int solve_and(int n, int hi) {
    int cur = 0;
    for (int b = hi; b >= 0; b--) {
        int cand = cur | (1 << b);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((a[i] & cand) == cand) {
                cnt++;
                if (cnt >= 2) break;   // 够两个就不必再数
            }
        }
        if (cnt >= 2) cur = cand;
    }
    return cur;
}

// c=2 异或运算：把序列依次插入 0-1 Trie，每个数插入前先查询它与“已插入元素”的最大异或值，
// 这样天然保证两个下标不同。
static int solve_xor(int n, int hi) {
    trie_cnt = 0;
    trie[0].child[0] = 0;
    trie[0].child[1] = 0;
    int best = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        int u = 0;
        int res = 0;
        for (int b = hi; b >= 0; b--) {
            int want = ((x >> b) & 1) ^ 1;   // 这一位想走相反分支，异或结果才能置 1
            int nxt = trie[u].child[want];
            if (nxt) {
                res |= (1 << b);
                u = nxt;
            } else {
                u = trie[u].child[want ^ 1];
            }
        }
        if (res > best) best = res;

        u = 0;
        for (int b = hi; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int nxt = trie[u].child[bit];
            if (!nxt) {
                nxt = new_node();
                trie[u].child[bit] = nxt;
            }
            u = nxt;
        }
    }
    return best;
}

// c=3 或运算：逐位贪心 + 超集判定。
// 记 t_i = cand & ~a[i]（cand 中 a[i] 缺的位），则“存在一对数的 OR 包含 cand”
// 等价于“存在下标 i，使 t_i 被另一个元素包含”。
// 先对值域做一次高维后缀和得到 sup：sup[m] = 是否存在元素包含 m。
// 查询时 sup[t] != 0 就说明有某个元素包含 t；由于 a[i] 与 t 的位完全不相交，
// t != 0 时这个元素一定不是 a[i] 自己；t == 0 时 sup[0] 恒为 1，
// 对应“a[i] 自己已覆盖 cand，任取另一个下标即可”（题面保证 n >= 2）。
static int solve_or(int n, int hi) {
    int dom = 1 << (hi + 1);
    memset(sup, 0, (size_t)dom);
    for (int i = 0; i < n; i++) sup[a[i]] = 1;
    for (int b = 0; b <= hi; b++) {
        int bit = 1 << b;
        for (int m = 0; m < dom; m++) {
            if ((m & bit) == 0 && sup[m | bit]) sup[m] = 1;
        }
    }
    int cur = 0;
    for (int b = hi; b >= 0; b--) {
        int cand = cur | (1 << b);
        for (int i = 0; i < n; i++) {
            if (sup[cand & ~a[i]]) {   // cand 中 a[i] 缺的位有别的元素兜住
                cur = cand;
                break;
            }
        }
    }
    return cur;
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T-- > 0) {
        int n, c;
        if (scanf("%d %d", &n, &c) != 2) break;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (a[i] > mx) mx = a[i];
        }
        int hi = hi_bit(mx);   // 值域最高位，答案不会超过它

        int ans;
        if (c == 1) ans = solve_and(n, hi);
        else if (c == 2) ans = solve_xor(n, hi);
        else ans = solve_or(n, hi);
        printf("%d\n", ans);
    }
    return 0;
}
