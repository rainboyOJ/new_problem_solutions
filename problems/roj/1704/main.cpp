/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:18
 * update_at: 2026-10-07 17:18
 */
// main.cpp：奇特的猫（一本通 1704）。
// 每天按键产生的所有屏幕字符串（含空串）构成一个前缀封闭集合 S，恰好是一棵 Trie 的结点集，
// 串间编辑距离 d(P,Q)=|P|+|Q|-2*LCP(P,Q) 正是这棵 Trie 上的树距。
// 于是三天的答案都归结为 Trie 上的统计：子树大小、换根距离和、以及一次自底向上的配对 DP。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXNODE = 1000005; // 单天 Trie 的结点数上限：|S| ≤ 10^6，再加一个根
const int HASH_BITS = 22;    // 孩子查找哈希表大小 2^22，装载因子 ≤ 1/4
const int HASH_SIZE = 1 << HASH_BITS;
const int HASH_MASK = HASH_SIZE - 1;
const ll NEG_INF = -(1LL << 62); // DP 里的"不存在"哨兵

struct Node {
    int parent;      // 父结点编号，根（空串）为 -1
    int depth;       // 深度 = 该结点代表的字符串长度
    int firstChild;  // 孩子链表的头，-1 表示叶子
    int nextSibling; // 兄弟链表的后继
    int subSize;     // 子树结点个数
    int ch;          // 从父结点下来的那个字符（ASCII 值；用 int 免去字符与键之间的转换）
    ll distSum;      // 到本集合内所有结点的距离之和
};

Node trie[MAXNODE]; // 结点 v 就是 trie[v]，编号按创建顺序分配，父结点编号一定小于子结点
int nodeCnt;        // 已经创建的结点个数（编号 0..nodeCnt-1）

// 孩子哈希表：键 = 父结点编号 * 256 + 字符。键与 (结点, 字符) 一一对应，
// 因此不存在"两个不同的孩子落到同一个键"的情况，只需处理桶下标冲突。
// 0xFFFFFFFF 是空槽标记（真实键最大只有 1e6*256 ≈ 2.6e8）。
unsigned hashKey[HASH_SIZE];
int hashVal[HASH_SIZE];

ll bestB0[MAXNODE]; // bestB0[v] = 子树 v 内 max(nA*D[x] + L*depth[x])，供第 3 天取 b0 用
ll bestB1[MAXNODE]; // bestB1[v] = 子树 v 内 max(nC*D[x] + L*depth[x])，供第 3 天取 b1 用

ll dayN[3];    // 三天的 |S|
ll dayW[3];    // 三天的集合内两两距离之和
ll dayDmin[3]; // 三天里 min_v (v 到集合内所有点的距离和)
ll dayDmax[3]; // 三天里 max_v (v 到集合内所有点的距离和)

vector<char> inBuf; // 一次性读入的全部输入，避免逐字符读入的开销
size_t dayBegin[3]; // 三天按键行在 inBuf 里的起始下标
size_t inPos;       // 当前解析位置

// 把整份输入读进内存，并在末尾补一个换行，解析时不必单独处理文件尾。
void readInput() {
    char tmp[1 << 20];
    size_t got;
    while ((got = fread(tmp, 1, sizeof(tmp), stdin)) > 0)
        inBuf.insert(inBuf.end(), tmp, tmp + got);
    inBuf.push_back('\n');
}

// 定位三行输入在缓冲里的起点：一天恰好一行，空行也是一天（该天只有空串）。
// 读入时已在末尾补了换行，所以最后一行的行尾也一定能找到。
void splitLines() {
    size_t p = 0;
    for (int d = 0; d < 3; ++d) {
        dayBegin[d] = p;
        while (p < inBuf.size() && inBuf[p] != '\n')
            ++p;
        ++p; // 跳过行尾换行，下一行的起点
    }
}

// 动态化静态开点：新建一个结点并返回编号。
int newNode(int par, int c) {
    int id = nodeCnt++;
    trie[id].parent = par;
    trie[id].depth = (par == -1 ? 0 : trie[par].depth + 1);
    trie[id].firstChild = -1;
    trie[id].nextSibling = -1;
    trie[id].subSize = 1;
    trie[id].ch = c;
    trie[id].distSum = 0;
    return id;
}

// 乘法散列：把键摊到 2^22 个桶上，装载因子低，线性探测足够快。
unsigned hashPos(unsigned key) {
    return (key * 2654435761u) >> (32 - HASH_BITS);
}

// 结点 u 沿字符 c 向下走一步：没有对应孩子就现场新建一个。
int walkChild(int u, int c) {
    unsigned key = u * 256 + c;
    unsigned pos = hashPos(key);
    while (hashKey[pos] != 0xFFFFFFFFu && hashKey[pos] != key)
        pos = (pos + 1) & HASH_MASK;
    if (hashKey[pos] == key)
        return hashVal[pos];
    int id = newNode(u, c);
    trie[id].nextSibling = trie[u].firstChild; // 头插进父结点的孩子链表
    trie[u].firstChild = id;
    hashKey[pos] = key;
    hashVal[pos] = id;
    return id;
}

// 建好一天的 Trie 后统计这一天的三个量。
// 关键性质：结点编号就是拓扑序（父结点编号一定小于子结点编号），
// 所以倒着扫一遍能累加子树大小，正着扫一遍能由父结点推出子结点的距离和。
void calcDay(int d) {
    for (int v = nodeCnt - 1; v >= 1; --v)
        trie[trie[v].parent].subSize += trie[v].subSize; // 孩子编号更大，此时子树大小已完整

    dayN[d] = nodeCnt;
    dayW[d] = 0;
    for (int v = 1; v < nodeCnt; ++v) {
        ll s = trie[v].subSize; // 边 (parent,v) 一侧有 s 个点，另一侧有 n-s 个点
        dayW[d] += s * (dayN[d] - s);
    }

    ll d0 = 0; // 根（空串）到所有结点的距离和 = 所有结点的深度和
    for (int v = 0; v < nodeCnt; ++v)
        d0 += trie[v].depth;
    trie[0].distSum = d0;
    for (int v = 1; v < nodeCnt; ++v) { // 换根：从父结点走到子结点，子树内的点都近 1，其余点都远 1
        int p = trie[v].parent;
        trie[v].distSum = trie[p].distSum + dayN[d] - 2 * trie[v].subSize;
    }

    dayDmin[d] = trie[0].distSum;
    dayDmax[d] = trie[0].distSum;
    for (int v = 1; v < nodeCnt; ++v) {
        dayDmin[d] = min(dayDmin[d], trie[v].distSum);
        dayDmax[d] = max(dayDmax[d], trie[v].distSum);
    }
}

// 读入第 d 天的按键序列并建 Trie（退格 8 = 回父结点），然后统计该天。
void buildDay(int d) {
    memset(hashKey, 0xFF, sizeof(hashKey)); // 清空孩子哈希表
    nodeCnt = 0;
    newNode(-1, 0); // 根 = 空串

    inPos = dayBegin[d];
    int cur = 0;
    while (inPos < inBuf.size() && inBuf[inPos] != '\n') {
        char c = inBuf[inPos];
        if (c == ' ' || c == '\r' || c == '\t') {
            ++inPos;
            continue;
        }
        int val = 0;
        while (inPos < inBuf.size() && inBuf[inPos] >= '0' && inBuf[inPos] <= '9') {
            val = val * 10 + (inBuf[inPos] - '0');
            ++inPos;
        }
        if (val == 8) { // 退格：光标回退，串变成父结点代表的串
            if (cur != 0)
                cur = trie[cur].parent;
        } else {
            cur = walkChild(cur, val);
        }
    }
    calcDay(d);
}

// 第 3 天最大值里唯一需要配对优化的部分：
//   max over b0,b1 in B of [ nA*D[b0] + nC*D[b1] + L*d(b0,b1) ]，L = nA*nC。
// 用 d(b0,b1) = depth(b0) + depth(b1) - 2*depth(lca) 拆开，就变成
//   max over b0,b1 of [ f[b0] + g[b1] - 2*L*depth(lca(b0,b1)) ]，
// 再按 lca 分类：对每个结点 v 枚举"lca 恰好是 v"的配对（两端都是 v / 一端是 v 另一端在某个孩子子树 /
// 两端在两个不同的孩子子树），倒序编号保证孩子先算好。
ll maxPairInB(ll coefA, ll coefC) {
    ll L = coefA * coefC;
    ll best = NEG_INF;
    for (int v = nodeCnt - 1; v >= 0; --v) {
        ll f = coefA * trie[v].distSum + L * trie[v].depth; // 取 b0 = v 时的权值
        ll g = coefC * trie[v].distSum + L * trie[v].depth; // 取 b1 = v 时的权值
        ll cur = f + g;                                     // b0 = b1 = v
        ll sub0 = f, sub1 = g;                              // 子树内 max f / max g
        ll other0 = NEG_INF, other1 = NEG_INF;              // 已处理过的孩子子树里 max f / max g
        for (int c = trie[v].firstChild; c != -1; c = trie[c].nextSibling) {
            cur = max(cur, f + bestB1[c]);   // 一端是 v，另一端在子树 c
            cur = max(cur, bestB0[c] + g);
            if (other0 != NEG_INF)
                cur = max(cur, other0 + bestB1[c]); // 两端分别在两个不同的孩子子树
            if (other1 != NEG_INF)
                cur = max(cur, other1 + bestB0[c]);
            other0 = max(other0, bestB0[c]);
            other1 = max(other1, bestB1[c]);
            sub0 = max(sub0, bestB0[c]);
            sub1 = max(sub1, bestB1[c]);
        }
        bestB0[v] = sub0;
        bestB1[v] = sub1;
        cur -= 2 * L * trie[v].depth; // lca 恰好是 v，扣掉多算的两段 depth
        best = max(best, cur);
    }
    return best;
}

int main() {
    readInput();
    splitLines();

    buildDay(0);
    buildDay(1);
    buildDay(2);

    ll nA = dayN[0], nB = dayN[1], nC = dayN[2];

    // 第 1 天：集合 A 内所有字符串对的距离之和。
    ll day1 = dayW[0];

    // 第 2 天：把 A、B 并成一个整体，A0、B0 固定后所有对的距离之和
    //   = W(A) + W(B) + [A×B 的对：nA*nB + nB*D_A[A0] + nA*D_B[B0]]。
    ll day2min = dayW[0] + dayW[1] + nA * nB + nB * dayDmin[0] + nA * dayDmin[1];
    ll day2max = dayW[0] + dayW[1] + nA * nB + nB * dayDmax[0] + nA * dayDmax[1];

    // 第 3 天：A、B、C 三个集合并成一个整体，A0、B0、B1、C0 固定后所有对的距离之和
    //   = W(A)+W(B)+W(C) + [A×B 的对] + [B×C 的对] + [A×C 的对]，
    // 其中 A×C 的距离是 d(P,A0)+1+d(B0,B1)+1+d(C0,Q)，展开后系数为：
    //   base 部分 (nA*nB + nB*nC + 2*nA*nC) 固定，
    //   A0 的系数是 nB+nC，C0 的系数是 nA+nB，B0/B1 的系数分别是 nA/nC 且带 d(B0,B1) 一项。
    ll base = dayW[0] + dayW[1] + dayW[2] + nA * nB + nB * nC + 2 * nA * nC;
    ll day3min = base + (nB + nC) * dayDmin[0] + (nA + nB) * dayDmin[2] + (nA + nC) * dayDmin[1];

    // 最小值取 B0 = B1 同为 D_B 最小的点即可（d ≥ 0）；
    // 最大值要在 B 上重新建树做配对 DP，所以重读一次第 2 天的按键。
    buildDay(1);
    ll maxPair = maxPairInB(nA, nC);
    ll day3max = base + (nB + nC) * dayDmax[0] + (nA + nB) * dayDmax[2] + maxPair;

    cout << day1 << " " << day1 << "\n";
    cout << day2min << " " << day2max << "\n";
    cout << day3min << " " << day3max << "\n";
    return 0;
}
