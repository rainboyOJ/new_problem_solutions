/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:15
 * update_at: 2026-10-06 13:18
 */
#include <cstdio>
#include <cstring>

typedef long long ll;

// 二五语言：合法单词等价于 5x5 标准杨表（每行每列递增）。
// 按字母 A..Y 从小到大依次填入时，已填格必为左上对齐的阶梯形，
// 用各行长度 (a,b,c,d,e) 即可完整描述一个中间状态（共 C(10,5)=252 个）。

const int EMPTY = -1;    // 棋盘格尚未填字母时的哨兵值
int board[5][5];         // board[r][c] 表示第 r 行第 c 列预填字母(0..24)，EMPTY 表示未填
ll memo[6][6][6][6][6];  // memo[a][b][c][d][e] 表示各行已填 a>=b>=c>=d>=e 个字母时的方案数

// 在 board 的预填约束下，计算把剩余字母继续按从小到大填满杨表的合法方案数。
// ch = a+b+c+d+e 是当前要放的字母，它只能落在某一行末尾。
ll dfs_count(int a, int b, int c, int d, int e) {
    int ch = a + b + c + d + e;
    if (ch == 25) {
        return 1;
    }
    if (memo[a][b][c][d][e] != -1) {
        return memo[a][b][c][d][e];
    }
    ll ways = 0;
    // 第 0~4 行：行尾格未预填或恰好预填 ch，才允许把当前字母放进去
    if (a < 5 && (board[0][a] == EMPTY || board[0][a] == ch)) {
        ways += dfs_count(a + 1, b, c, d, e);
    }
    if (b < a && (board[1][b] == EMPTY || board[1][b] == ch)) {
        ways += dfs_count(a, b + 1, c, d, e);
    }
    if (c < b && (board[2][c] == EMPTY || board[2][c] == ch)) {
        ways += dfs_count(a, b, c + 1, d, e);
    }
    if (d < c && (board[3][d] == EMPTY || board[3][d] == ch)) {
        ways += dfs_count(a, b, c, d + 1, e);
    }
    if (e < d && (board[4][e] == EMPTY || board[4][e] == ch)) {
        ways += dfs_count(a, b, c, d, e + 1);
    }
    memo[a][b][c][d][e] = ways;
    return ways;
}

// 清空记忆化并重新计算当前 board 约束下的方案总数
ll count_ways() {
    memset(memo, -1, sizeof(memo));
    return dfs_count(0, 0, 0, 0, 0);
}

// 模式 N：把排名 rank（从 1 开始）还原成对应的合法单词（字典序逐位确定）
void decode_rank(ll rank) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            board[r][c] = EMPTY;
        }
    }
    bool used[25];
    memset(used, 0, sizeof(used));
    char word[30];

    for (int i = 0; i < 25; i++) {
        int r = i / 5;
        int c = i % 5;
        for (int ch = 0; ch < 25; ch++) {
            if (used[ch]) {
                continue;
            }
            // 当前位置必须大于上方和左方已填字母
            if (r > 0 && board[r - 1][c] > ch) {
                continue;
            }
            if (c > 0 && board[r][c - 1] > ch) {
                continue;
            }
            board[r][c] = ch;
            ll ways = count_ways();
            if (ways >= rank) {
                used[ch] = true;
                word[i] = 'A' + ch;
                break;
            }
            // 该位放 ch 时后面不足 rank 个单词，跳过这些单词继续试更大的字母
            rank -= ways;
            board[r][c] = EMPTY;
        }
    }
    word[25] = '\0';
    printf("%s\n", word);
}

// 模式 W：求合法单词的排名（从小到大累计更小字母可形成的方案数）
ll encode_word(const char *word) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            board[r][c] = EMPTY;
        }
    }
    bool used[25];
    memset(used, 0, sizeof(used));

    ll rank = 1; // 字典序排名从 1 开始
    for (int i = 0; i < 25; i++) {
        int r = i / 5;
        int c = i % 5;
        int target = word[i] - 'A';
        for (int ch = 0; ch < target; ch++) {
            if (used[ch]) {
                continue;
            }
            if (r > 0 && board[r - 1][c] > ch) {
                continue;
            }
            if (c > 0 && board[r][c - 1] > ch) {
                continue;
            }
            board[r][c] = ch;
            rank += count_ways();
            board[r][c] = EMPTY;
        }
        board[r][c] = target;
        used[target] = true;
    }
    return rank;
}

int main() {
    char mode;
    if (scanf(" %c", &mode) != 1) {
        return 0;
    }
    if (mode == 'N') {
        ll rank;
        scanf("%lld", &rank);
        decode_rank(rank);
    } else {
        char word[30];
        scanf("%s", word);
        printf("%lld\n", encode_word(word));
    }
    return 0;
}
