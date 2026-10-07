/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:14
 * update_at: 2026-10-07 15:25
 */
// main.cpp：【17NOIP普及组】成绩，把百分号权重放大 10 倍变成整数权重，全程整数运算。
// 与 main.py 同一算法：总成绩 = (2A + 3B + 5C) / 10。

#include <cstdio>

typedef long long ll;

ll work_score;  // A：作业成绩
ll test_score;  // B：小测成绩
ll exam_score;  // C：期末考试成绩

int main() {
    scanf("%lld %lld %lld", &work_score, &test_score, &exam_score);

    // 20% / 30% / 50% 统一乘 10 变成整数权重 2 / 3 / 5：既避开浮点误差，
    // 又不用引入分数。三个权重之和正好是 10，即还原成百分制要除的除数。
    ll total = work_score * 2 + test_score * 3 + exam_score * 5;

    // A、B、C 都是 10 的整数倍，所以 total 一定被 10 整除，整数除法不丢任何精度
    printf("%lld\n", total / 10);
    return 0;
}
