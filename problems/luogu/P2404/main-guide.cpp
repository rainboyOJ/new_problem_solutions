/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>

const int max_n = 15; // n <= 8，全 1 拆分时序列最长也只有 n 项

int n;
int path[max_n]; // path[0..depth-1] 保存当前拆分序列
int depth = 0;   // 当前序列长度

// 还需凑出 remaining，下一个加数至少为 min_val
void dfs(int remaining, int min_val) {
    if (remaining == 0) {
        if (depth > 1) { // 排除只有 n 本身的单项方案
            for (int i = 0; i < depth; i += 1) {
                if (i > 0) {
                    std::cout << '+';
                }
                std::cout << path[i];
            }
            std::cout << '\n';
        }
        return;
    }

    // 加数从小到大尝试，下一个不小于当前值，保证序列不下降
    for (int val = min_val; val <= remaining; val += 1) {
        path[depth] = val;
        depth += 1;
        dfs(remaining - val, val);
        depth -= 1; // 恢复现场：撤销这次选择，再尝试下一个加数
    }
}

int main() {
    std::cin >> n;
    dfs(n, 1);
    return 0;
}
