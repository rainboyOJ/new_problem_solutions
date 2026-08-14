/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P2089 烤鸡：递归枚举 10 种配料各放 1~3 克，总和等于 n 时记下方案。 */

#include <iostream>

const int ingredient_count = 10;   // 配料种类数
const int max_solutions = 59049;   // 每种配料 3 种选择，最多 3^10 = 59049 个方案

int target_sum;                          // 目标美味程度
int ingredient[ingredient_count];        // ingredient[dep]：第 dep 种配料放的质量
int solution_count = 0;                  // 合法方案数
int solutions[max_solutions][ingredient_count];  // 保存全部合法方案

// 决定第 dep 种配料的质量，决定完 10 种后检查总和。
void dfs(int dep) {
    if (dep == ingredient_count) {
        int sum = 0;
        for (int i = 0; i < ingredient_count; i += 1) {
            sum += ingredient[i];
        }
        if (sum == target_sum) {
            for (int i = 0; i < ingredient_count; i += 1) {
                solutions[solution_count][i] = ingredient[i];
            }
            solution_count += 1;
        }
        return;
    }

    // 当前配料可以放 1、2、3 克，每种尝试一次。
    for (int gram = 1; gram <= 3; gram += 1) {
        ingredient[dep] = gram;  // 记录当前选择；同一位置下次会被覆盖，不需要恢复
        dfs(dep + 1);
    }
}

int main() {
    std::cin >> target_sum;
    dfs(0);

    std::cout << solution_count << '\n';
    for (int i = 0; i < solution_count; i += 1) {
        for (int j = 0; j < ingredient_count; j += 1) {
            std::cout << solutions[i][j];
            if (j < ingredient_count - 1) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    return 0;
}
