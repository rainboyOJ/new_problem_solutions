/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 22:30
 */

#include <cstdio>
typedef long long ll;

ll confirmed; // 甲流确诊数
ll died;      // 甲流死亡数

int main() {
    scanf("%lld %lld", &confirmed, &died);
    // 死亡率 = 死亡数 ÷ 确诊数 × 100，按百分数保留 3 位小数输出
    double rate = died * 100.0 / confirmed;
    printf("%.3f%%\n", rate);
    return 0;
}
