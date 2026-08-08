/**
 * P1185 绘制二叉树
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 11;

int m, k;
bool del[1 << MAXM]; // 标记被删除的结点（按完全二叉树编号）
char canvas[800][1600]; // 画布（宽 = 2*高-1）
int height, width;
int node_row[MAXM]; // 每层结点的行号

// 递归删除子树
void remove_sub(int u) {
    if (u >= (1 << m)) return;
    del[u] = true;
    remove_sub(u * 2);
    remove_sub(u * 2 + 1);
}

// 递归绘制
void draw(int u, int level, int row, int col) {
    if (del[u]) return;
    canvas[row][col] = 'o';
    if (level == m) return;
    int child_row = node_row[level + 1];
    int gap = child_row - row;
    // 左孩子
    if (!del[u * 2]) {
        for (int step = 1; step < gap; ++step)
            canvas[row + step][col - step] = '/';
        draw(u * 2, level + 1, child_row, col - gap);
    }
    // 右孩子
    if (!del[u * 2 + 1]) {
        for (int step = 1; step < gap; ++step)
            canvas[row + step][col + step] = '\\';
        draw(u * 2 + 1, level + 1, child_row, col + gap);
    }
}

int main() {
    scanf("%d%d", &m, &k);
    // 计算画布尺寸
    height = 3 * (1 << (m - 2));
    if (m == 1) height = 1;
    width = 2 * height - 1;
    // 计算每层结点的行号
    for (int i = 1; i < m; ++i)
        node_row[i] = height - 3 * (1 << (m - i - 1));
    node_row[m] = height - 1;
    // 读入并标记删除的结点
    for (int i = 1; i <= k; ++i) {
        int level, idx;
        scanf("%d%d", &level, &idx);
        int u = (1 << (level - 1)) + idx - 1;
        remove_sub(u);
    }
    // 初始化画布为空格
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            canvas[i][j] = ' ';
    // 绘制
    draw(1, 1, 0, width / 2);
    // 输出
    for (int i = 0; i < height; ++i) {
        canvas[i][width] = '\0';
        printf("%s\n", canvas[i]);
    }
    return 0;
}
