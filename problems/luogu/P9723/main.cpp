/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:55
 *
 * P9723 [EC Final 2022] Chinese Checker
 *
 * 核心结论
 * --------
 * 一次 move 从头到尾只动 checker a，其它棋子全程不动。所以终局只是把
 * 「a 的起点 p0」和「a 的终点 p」这两个格子互换，而 p0 一定是原本有棋子的格子。
 * 因此一次 move 唯一对应一个空闲格子 p（p 从 p0 出发可达，且 p != p0），
 * 不同的 move 数 = sum over p0 in S ( 从 p0 出发能到达的空格数 - 1 )。
 *
 * 固定 p0 后怎么求可达集合
 * ------------------------
 * 把 p0 自己视为空（它已经离开了），其余 n-1 颗棋子当成障碍。
 * 一步 step 就是：选一个方向，找该方向上离 p0 最近的棋子 b 当 pivot，
 * 跳到关于 b 的对称点 q = 2b - p0，要求 q 在盘内且为空。
 *   * pivot 不必与 a 相邻，所以 q 可能离得很远；
 *   * "a 与 q 之间除 b 外没有其它棋子"等价于：该方向的第二近棋子必须在 q 之外。
 * 于是每个 p0 只需求一次 BFS，答案就是所有可达空格数之和。
 * 棋盘只有 121 格、6 个方向，T <= 100，轻松通过。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int OFFSET = 15;          // 轴向坐标 -12..12 平移到 0..30
const int WIDTH = 40;           // 平移后坐标的取值范围
const int MAXC = 121 + 5;       // 棋盘上的格子总数 121

// 17 行的格子数（从上到下）
int row_len[17] = {1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1};

int id_of[20][WIDTH];           // (行, 平移后轴向坐标) -> 格子编号；-1 表示不在盘上
int cell_row[MAXC];             // 格子编号 -> 行号(1 起)
int cell_col[MAXC];             // 格子编号 -> 该行内第几个(1 起)
int cell_x[MAXC];               // 格子编号 -> 平移后的轴向坐标
int cell_cnt;

// 6 个方向。行变化 + 轴向坐标变化：
// 前两个是水平方向，中间两个是左下/右上，后两个是左上/右下。
int step_row[6] = {0, 0, 1, 1, -1, -1};
int step_dx[6]  = {2, -2, 1, -1, 1, -1};

bool occ[MAXC];                 // 当前局面下该格子是否有棋子
bool vis[MAXC];
int q[MAXC];                    // BFS 队列
int n;
int piece[MAXC];                // 第 i 颗棋子所在格子编号

// (行, 平移后轴向坐标) 是否在棋盘上
bool on_board(int row, int x) {
    if (row < 1 || row > 17) return false;
    int len = row_len[row - 1];
    // 该行的轴向坐标范围是 OFFSET-(len-1) .. OFFSET+(len-1)，步长 2
    return x >= OFFSET - (len - 1) && x <= OFFSET + (len - 1) && x < WIDTH;
}

// 建立棋盘：第 r 行有 row_len[r-1] 个格子，第 c 个格子的轴向坐标是 OFFSET-(len-1)+2*(c-1)
void build_board() {
    memset(id_of, -1, sizeof(id_of));
    cell_cnt = 0;
    for (int r = 1; r <= 17; r++) {
        int len = row_len[r - 1];
        for (int c = 1; c <= len; c++) {
            int x = OFFSET - (len - 1) + 2 * (c - 1);
            cell_cnt++;
            id_of[r][x] = cell_cnt;
            cell_row[cell_cnt] = r;
            cell_col[cell_cnt] = c;
            cell_x[cell_cnt] = x;
        }
    }
}

// 尝试从格子 u 沿方向 d 跳一步，能跳则把落点写入 np 并返回 true。
// 做法：一路扫过去，记下最近棋子的步数 first 和第二近棋子的步数 second。
//   * 没有棋子 -> 这个方向没有 pivot，不能走；
//   * second <= 2*first -> 第二近的棋子落在段内（或正好占了落点），不能走；
//   * 落点 = u 沿 d 走 2*first 步，若出界或已被占则不能走。
bool try_hop(int u, int d, int &np) {
    int r = cell_row[u], x = cell_x[u];
    int k = 0, first = -1, second = -1;
    while (true) {
        r += step_row[d];
        x += step_dx[d];
        k++;
        if (!on_board(r, x)) break;
        int v = id_of[r][x];
        if (occ[v]) {
            if (first == -1) first = k;
            else { second = k; break; }
        }
    }
    if (first == -1) return false;
    if (second != -1 && second <= 2 * first) return false;
    r = cell_row[u] + 2 * first * step_row[d];
    x = cell_x[u] + 2 * first * step_dx[d];
    if (!on_board(r, x)) return false;
    np = id_of[r][x];
    return !occ[np];                // 落点必须为空
}

// 以 p0 为起点 BFS（调用前需把 occ[p0] 置为 false），返回可达格子数（含 p0 自己）
int bfs_count(int p0) {
    memset(vis, 0, sizeof(bool) * (cell_cnt + 1));
    int head = 0, tail = 0;
    q[tail++] = p0;
    vis[p0] = true;
    int reached = 1;
    while (head < tail) {
        int u = q[head++];
        for (int d = 0; d < 6; d++) {
            int np = -1;
            if (!try_hop(u, d, np)) continue;
            if (vis[np]) continue;
            vis[np] = true;
            reached++;
            q[tail++] = np;
        }
    }
    return reached;
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
            piece[i] = id_of[r][x];
            occ[piece[i]] = true;
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            int p0 = piece[i];
            occ[p0] = false;                // 移动的这颗棋子离开了起点
            ans += bfs_count(p0) - 1;       // 去掉"终点就是起点"这一种
            occ[p0] = true;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
