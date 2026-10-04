/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:42
 * update_at: 2026-10-05 05:42
 */

#include <cstdio>

typedef long long ll;

// 每列皇后所在的行号，row[c] 表示第 c 列（0 起）的皇后放在第 row[c] 行
int row[8];
// 搜索解的计数器，用来输出 No. k
int cnt = 0;

// 判断把皇后放在 (r, c) 是否与前面各列已放的皇后冲突：
// 同行、主对角线（r+c 相同）、副对角线（r-c 相同）都算冲突
bool conflict(int r, int c) {
    for (int j = 0; j < c; ++j) {
        if (row[j] == r) return true;                    // 同一行
        if (row[j] + j == r + c) return true;            // 同一条主对角线（左下到右上）
        if (row[j] - j == r - c) return true;            // 同一条副对角线（左上到右下）
    }
    return false;
}

// 逐列回溯：这一层决定第 c 列皇后的行号，按行号从小到大枚举
// 枚举顺序就是题目要求的输出顺序
void dfs(int c) {
    if (c == 8) {                                        // 八列都放好，得到一个解
        ++cnt;
        printf("No. %d\n", cnt);
        for (int r = 0; r < 8; ++r) {                    // 输出 8 行棋盘（样例行末有一个空格）
            for (int cc = 0; cc < 8; ++cc) {
                printf("%d ", row[cc] == r ? 1 : 0);
            }
            printf("\n");
        }
        return;
    }
    for (int r = 0; r < 8; ++r) {
        if (conflict(r, c)) continue;                    // 与前面列冲突，跳过
        row[c] = r;
        dfs(c + 1);
    }
}

int main() {
    dfs(0);                                              // 从第 0 列开始搜，共 92 个解
    return 0;
}
