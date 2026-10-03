/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:20
 */
// P9726 [EC Final 2022] Magic
//
// n 个区间 [l_i, r_i)（赋值 i 到位置 l_i..r_i-1），2n 个端点互不相同。
// 任意顺序执行每个区间一次，最大化 a_0..a_{2n} 中相邻不同的位置数。
//
// 模型：位置 i 成为“断点”当且仅当 a_i != a_{i+1}。
//   所有区间都覆盖 l_i，但都不覆盖 l_i-1；位置 r_i-1 被 i 覆盖，r_i 不被 i 覆盖。
//   因此断点只可能出现在 2n 个端点处，且每个端点 s 是否成为断点
//   等价于“把写着 s 的那个区间放到最后”这一件事是否被安排成真。
//
// 关键观察：对相交且不包含的两个区间 l_i < l_j < r_i < r_j，
//   它们不可能同时“在最后写自己的断点”：谁先执行，谁的那一侧端点就被对方覆盖。
//   于是只有 l_i < l_j < r_i < r_j 这样的“交错对”才会产生二选一冲突：
//       选 r_i 当断点  <=>  区间 j 必须排在 i 前面
//       选 l_j 当断点  <=>  区间 i 必须排在 j 前面
//   两者不能同时成立，也就是二分图中“r_i 与 l_j 不能同时被选”。
//
// 把 2n 个端点分成两类：左部点 = 每个区间的 r_i，右部点 = 每个区间的 l_j；
// 若 l_i < l_j < r_i < r_j 则在 r_i 与 l_j 之间连边。
// 那么“可同时当选断点的端点集合”正是这张二分图的一个独立集，
// 答案是 2n - 最大匹配（König 定理：最大独立集 = 总点数 - 最大匹配）。
//   上界方向：设最终断点集合为 B，则 {r_i : r_i 不在 B} ∪ {l_j : l_j 不在 B}
//             是一个大小 2n-|B| 的独立集，故 |B| <= 2n - 最大匹配。
//   可达方向：取最大独立集 S，对每个 s ∈ S 与包含它的区间连有向边
//             （“被覆盖者必须在覆盖者之后执行”），这张图无环，
//             任一拓扑序都能让 S 中所有端点成为断点。
//
// 复杂度：建图 O(n^2)，匈牙利算法 O(n^3/64)（邻接矩阵用 64 位压位），
// 空间 O(n^2/64)。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005;
const int maxw = (maxn + 63) / 64;

int n;
int words;                          // 邻接矩阵按 64 位分成的“字”数
int lft[maxn], rgt[maxn];           // 第 i 个区间覆盖位置 [lft_i, rgt_i - 1]
unsigned long long adj[maxn][maxw]; // 二分图：左部点 i（r_i）-> 右部点 j（l_j）
int matchR[maxn];                   // 右部点匹配到的左部点，-1 表示未匹配
int matchL[maxn];                   // 左部点匹配到的右部点，-1 表示未匹配
unsigned long long visR[maxw];      // 本轮匈牙利中右部点的访问标记

// 匈牙利算法：从左侧点 u 出发找增广路。
// 右部点的访问标记按位存储，未访问的候选点 = adj[u] & ~visR，一次能跳过一整字。
bool dfs(int u) {
    for (int w = 0; w < words; w++) {
        unsigned long long cur = adj[u][w] & ~visR[w];
        while (cur) {
            int b = __builtin_ctzll(cur); // 取出最低位的 1
            cur &= cur - 1;               // 抹掉这一位
            visR[w] |= 1ULL << b;
            int v = (w << 6) + b;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
    }
    return false;
}

void read_data() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> lft[i] >> rgt[i];
    }
}

void solve() {
    words = (n + 63) / 64;
    // 建图：l_i < l_j < r_i < r_j 时连边 i -> j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (lft[i] < lft[j] && lft[j] < rgt[i] && rgt[i] < rgt[j]) {
                adj[i][j >> 6] |= 1ULL << (j & 63);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        matchR[i] = -1;
        matchL[i] = -1;
    }

    int matching = 0;
    for (int i = 0; i < n; i++) {
        if (matchL[i] != -1) {
            continue;
        }
        memset(visR, 0, sizeof(unsigned long long) * words);
        if (dfs(i)) {
            matching++;
        }
    }

    cout << 2 * n - matching << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read_data();
    solve();
    return 0;
}
