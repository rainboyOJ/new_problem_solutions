/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1706 全排列问题：used 数组记录已用数字，回溯时恢复。 */

#include <iostream>
#include <iomanip>

const int max_n = 10;  // n 最大为 9

int n;
int chosen[max_n];  // chosen[pos]：第 pos 位填的数字
int used[max_n];    // used[value] = 1 表示数字 value 已被前面的位置使用

// 填第 pos 位（0 起始），所有位置填完就输出一个排列。
void dfs(int pos) {
    if (pos == n) {
        for (int i = 0; i < n; i += 1) {
            std::cout << std::setw(5) << chosen[i];
        }
        std::cout << '\n';
        return;
    }

    // 每一位可以尝试任意一个还没用过的数字。
    for (int value = 1; value <= n; value += 1) {
        if (used[value]) {
            continue;  // 这个数字已经出现在前面的位置
        }
        used[value] = 1;    // 前进阶段：标记 value 被占用
        chosen[pos] = value;  // 记录当前位的选择
        dfs(pos + 1);
        used[value] = 0;    // 回溯阶段：释放 value，让下一个分支可以再用
    }
}

int main() {
    std::cin >> n;
    dfs(0);
    return 0;
}
