/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:20
 * update_at: 2026-10-06 11:20
 */
// 经典跳棋互换谜题 (Shuttle Puzzle, USACO 4.4.1)。
// 最少步数恒为 (N+1)^2 - 1：N^2 次跳跃恰好翻转全部异色对，
// 剩下 2N 次相邻平移补足位移。DFS 时按被移动棋子的原下标
// 从小到大尝试，首次到达目标的解即为字典序最小的最优解。

#include <cstdio>

typedef long long ll;

const int MAXN = 30;        // N <= 12，棋盘长度最多 2*12+1 = 25
const int MAXSTEP = (12 + 1) * (12 + 1); // 最深步数 (N+1)^2 - 1 = 168

// 棋盘状态：0 = 空格，1 = 白棋 W，2 = 黑棋 B
int board[MAXN];
int n;                      // 白棋/黑棋个数
int max_steps;              // 最少步数 (N+1)^2 - 1
int path[MAXSTEP];          // path[i] = 第 i 步被移动棋子的原位置（1 起始）
int step_cnt;               // 当前已走步数

// 判断是否已到达目标：左侧 N 个黑棋、中间空格、右侧 N 个白棋
bool is_target() {
    for (int i = 1; i <= n; ++i)
        if (board[i] != 2) return false;   // 左半必须是黑棋
    if (board[n + 1] != 0) return false;   // 中间必须是空格
    for (int i = n + 2; i <= 2 * n + 1; ++i)
        if (board[i] != 1) return false;   // 右半必须是白棋
    return true;
}

// 检查 pos 位置的棋子能否移入 blank 空格（均为 1 起始下标）
bool can_move(int pos, int blank) {
    if (pos < 1 || pos > 2 * n + 1) return false;
    if (blank - pos == 2) return board[pos] == 1 && board[pos + 1] == 2; // 白棋右跳
    if (blank - pos == 1) return board[pos] == 1;                       // 白棋右移
    if (blank - pos == -1) return board[pos] == 2;                      // 黑棋左移
    if (blank - pos == -2) return board[pos] == 2 && board[pos - 1] == 1; // 黑棋左跳
    return false;
}

// 回溯搜索：blank 为当前空格的 1 起始下标
// 返回 true 表示沿当前路径能走到目标状态（即已找到字典序最小的解）
bool dfs(int blank) {
    if (step_cnt == max_steps)
        return is_target(); // 步数已用完，恰好应到达目标

    // 候选位置从小到大枚举，保证输出序列字典序最小
    for (int pos = 1; pos <= 2 * n + 1; ++pos) {
        if (!can_move(pos, blank)) continue;
        // 把 pos 处棋子移入空格：棋子落到 blank，空格来到 pos
        int piece = board[pos]; // 暂存被移动棋子的颜色，便于回溯还原
        board[blank] = piece;
        board[pos] = 0;
        step_cnt++;
        path[step_cnt] = pos; // 输出的就是棋子的 1 起始原下标

        if (dfs(pos)) return true;

        step_cnt--;
        board[pos] = piece; // 回溯还原：棋子回到 pos，blank 恢复为空格
        board[blank] = 0;
    }
    return false;
}

int main() {
    scanf("%d", &n);

    // 初始：下标 1..n 白棋，n+1 空格，n+2..2n+1 黑棋
    for (int i = 1; i <= 2 * n + 1; ++i)
        board[i] = (i <= n) ? 1 : (i == n + 1 ? 0 : 2);

    max_steps = (n + 1) * (n + 1) - 1;
    step_cnt = 0;
    dfs(n + 1); // 空格初始在位置 n+1

    // 每行输出 20 个数
    for (int i = 1; i <= max_steps; ++i) {
        printf("%d", path[i]);
        if (i % 20 == 0 || i == max_steps) printf("\n");
        else printf(" ");
    }
    return 0;
}
