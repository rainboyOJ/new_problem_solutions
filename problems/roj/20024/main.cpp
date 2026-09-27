/**
 * Author by Rainboy blog: https://rainboylv.com github:
 * https://github.com/rainboylvx rbook: -> https://rbook.roj.ac.cn
 * https://rbook2.roj.ac.cn rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-26 12:00
 * update_at: 2026-09-26 12:43
 */
// main.cpp：T4 棋(Chess) 正式解
// 12bit 状压 DP：一列 = 图案 pat(3bit) + 已计入标记 mark(3bit)；
// 状态 = 窗口左端"旧列 A" + "中列 B"，共 12bit，枚举新列 C 后结算旧列 A。
// 6 条三连写成常量表 T[6][3]（每个格子是 {行,
// 列偏移}），转移时用一个循环统一判定。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG = -(1LL << 60);
const int MAXN = 1005;
const int SZ = 1 << 12; // 12bit 状态，共 4096 种

// dp[s]：状态 s = (旧列A, 中列B) 时，窗口左端之前的列已全部结算完的最大分数；
//         状态里 mark 标出的格子还只是"挂账"，权值要等它滑出窗口时才加入。
ll dp[SZ];

// ndp[s]：滚动数组的下一层，含义同 dp，用来承接枚举新列 C 之后的转移结果。
ll ndp[SZ];

int n;
ll w[3][MAXN]; // w[行][列]：每个格子的权值

// 得到数字x 的第 k 位是0 还是1
int bit(int x, int k) { return (x >> k) & 1; }

// 列图案 p 第 r 行的染色符号：X(bit=1) 红取 +1，O(bit=0) 蓝取 -1。
int sgn(int p, int r) { return bit(p, r) ? 1 : -1; }

// 三列窗口里的一个格子：行 row(0~2) + 列偏移 col(0=旧列A, 1=中列B, 2=新列C)。
struct offset {
  int row, col;
};

// 6 条三连，每条 3 个格子；只收录"最左格落在 A 列"的直线：
// 1 条 A 列纵向 + 3 条横向 + 2 条对角线。
const offset T[6][3] = {
    {{0, 0}, {1, 0}, {2, 0}}, // 纵向：整列 A
    {{0, 0}, {0, 1}, {0, 2}}, // 横向 行0
    {{1, 0}, {1, 1}, {1, 2}}, // 横向 行1
    {{2, 0}, {2, 1}, {2, 2}}, // 横向 行2
    {{0, 0}, {1, 1}, {2, 2}}, // 对角线 ↘
    {{2, 0}, {1, 1}, {0, 2}}  // 对角线 ↗
};

// 状态编码：s = pA | (mA<<3) | (pB<<6) | (mB<<9)
//  [mB][pB][mA][pA]
inline int encode(int pA, int mA, int pB, int mB) {
  return pA | (mA << 3) | (pB << 6) | (mB << 9);
}

// 解码
inline void decode(int s, int &pA, int &mA, int &pB, int &mB) {
  pA = s & 7;
  mA = (s >> 3) & 7;
  pB = (s >> 6) & 7;
  mB = (s >> 9) & 7;
}

// 结算窗口 (A,B,C) 里的旧列 A：返回本轮 gain，并更新三个"已计入"标记。
// 规则：命中三连的 A 格当场结算（已计入的跳过），B、C 格只打标记。
// colA 列的下标: 第j列, p[3] pA,pB,pC 的状态
// mA mB mC 是否已经计算
ll gain(int colA, int p[3], int &mA, int &mB, int &mC) {
  ll g = 0; // 结果
  // 旧列 A 中"更早窗口已判定染色"的挂账格子，落账
  for (int r = 0; r < 3; r++) {
    if (bit(mA, r)) g += w[r][colA] * sgn(p[0], r);
  }
  // 6 条三连统一判定
  for (int t = 0; t < 6; t++) {
    int v = bit(p[T[t][0].col], T[t][0].row); // 第 t 条三连的第 0 个格子"的颜色
    if (bit(p[T[t][1].col], T[t][1].row) != v) continue;
    if (bit(p[T[t][2].col], T[t][2].row) != v) continue;
    for (int k = 0; k < 3; k++) { // 枚举这一条的三个格子
      int r = T[t][k].row, c = T[t][k].col;
      if (c == 0) { // 旧列 A：计入
        if (!bit(mA, r)) {
          g += w[r][colA] * sgn(p[0], r);
          mA |= 1 << r;
        }
      } else if (c == 1) { // 中列 B：只标记
        mB |= 1 << r;
      } else { // 新列 C：只标记
        mC |= 1 << r;
      }
    }
  }
  return g;
}

// 收尾结算一列：右侧没有第三列，只可能是"已有标记 + 纵向三连"。
ll settle_last(int col, int p, int m) {
  ll g = 0;
  for (int r = 0; r < 3; r++) {
    if (bit(m, r)) g += w[r][col] * sgn(p, r);
  }
  if (p == 0 || p == 7) { // 整列同色 -> 纵向三连
    for (int r = 0; r < 3; r++) {
      if (!bit(m, r)) g += w[r][col] * sgn(p, r);
    }
  }
  return g;
}

// n <= 2：列数不够 3，只有纵向三连，每列独立，直接累加 |列和|。
void solve_small() {
  ll ans = 0;
  for (int c = 0; c < n; c++) {
    ll s = w[0][c] + w[1][c] + w[2][c];
    ans += max(s, -s); // = |s|
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < n; c++) {
      cin >> w[r][c];
    }
  }

  if (n <= 2) {
    solve_small();
    return 0;
  }

  for (int s = 0; s < SZ; s++) dp[s] = NEG;
  // 初始：只确定第 0、1 列图案，还没有任何格子计入
  for (int p0 = 0; p0 < 8; p0++) {
    for (int p1 = 0; p1 < 8; p1++) {
      dp[encode(p0, 0, p1, 0)] = 0;
    }
  }

  // ==================== 主循环：一列一列往右推 ====================
  // 进入第 j 轮时，dp 里的状态 s = (旧列 A, 中列 B) 对应 A = j-2、B = j-1，
  // 即"棋盘已确定到第 j-1 列，第 j 列还没放"。
  // 本轮枚举第 j 列的图案 pC，凑出完整三列窗口 (j-2, j-1, j)。
  // 有了这个窗口，列 j-2 的颜色就完全确定了：
  //   - 它作为"右格/中格"的三连（窗口 j-4、j-3）之前已查过，结果记在 mA 里；
  //   - 它作为"左格"的三连（窗口 j-2 本身）以及纵向三连，现在才第一次可见。
  // 所以本轮把列 j-2 的账一次结清，然后窗口整体右移一列。
  for (int j = 2; j < n; j++) {
    int colA = j - 2; // 本轮要结算、并即将滑出窗口左端的列

    // ndp 是下一层 DP，先全部清成不可达
    for (int s = 0; s < SZ; s++) ndp[s] = NEG;

    // 枚举当前层的每一个状态 s = (A 的图案/标记, B 的图案/标记)
    for (int s = 0; s < SZ; s++) {
      if (dp[s] == NEG) continue; // 不可达状态直接跳过

      int pA, mA, pB, mB;
      decode(s, pA, mA, pB, mB); // 拆出 A、B 两列的图案与"已计入"标记

      // 枚举新列 C（第 j 列）的 8 种图案
      for (int pC = 0; pC < 8; pC++) {
        // 用副本承接本轮的新标记（直接改 mA/mB 会污染 dp[s]，因为 s 还要被其它
        // pC 复用）
        int nA = mA, nB = mB, mC = 0;

        // 结算窗口 (A,B,C)：算出列 A 本轮得分 g，并把新标记写回 nA/nB/mC
        int p[3] = {pA, pB, pC};
        ll g = gain(colA, p, nA, nB, mC);

        // 窗口右移一列：新状态是 (B, C)，其中 B 带新标记 nB、C 带新标记 mC
        int ns = encode(pB, nB, pC, mC);

        // 松弛：从状态 s 走一步到 ns，保留更优的分数
        ndp[ns] = max(ndp[ns], dp[s] + g);
      }
    }

    // 本轮所有转移做完，滚动到下一层
    for (int s = 0; s < SZ; s++) dp[s] = ndp[s];
  }

  // 收尾：最后两列永远不会滑到窗口左端，单独结算
  ll ans = NEG;
  for (int s = 0; s < SZ; s++) {
    if (dp[s] == NEG) continue;
    int pA, mA, pB, mB;
    decode(s, pA, mA, pB, mB);
    ll v = dp[s] + settle_last(n - 2, pA, mA) + settle_last(n - 1, pB, mB);
    ans = max(ans, v);
  }
  cout << ans << '\n';
  return 0;
}
