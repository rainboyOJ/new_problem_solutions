/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 07:45
 * update_at: 2026-10-09 08:12
 */
// 一本通 2072《【例2.15】歌手大奖赛》（ROJ 5073）
//
// 题意（题面为无输入题，答案唯一）：6 名评委打分的平均分为 9.6 分；
//   去掉一个最高分后 5 人平均分为 9.4 分；去掉一个最低分后 5 人平均分为 9.8 分；
//   求去掉一个最高分和一个最低分后 4 人的平均分，按 %5.2f 输出（保留 2 位小数）。
//
// 推导：总分 T = 6 * 9.6 = 57.6；最高分 H = T - 5 * 9.4 = 10.6；
//       最低分 L = T - 5 * 9.8 = 8.6；答案 = (T - H - L) / 4 = 38.4 / 4 = 9.6。
//       通式 ans = (5b + 5c - 6a) / 4（a/b/c 为三个平均分）。
//       本题 b + c = 19.2 = 2a，故 ans 恰好等于全体平均分 a —— 这是本题
//       给定数字的巧合，不是普遍规律（反例 a=9.6, b=9.4, c=9.9 => ans=9.725）。
//
// 题面未指定实现手段（grep 「利用|循环|递归|不使用|必须用」「（算法名）」均无命中），
//   故按 O(1) 直接计算。
//
// 浮点安全：答案精确值 9.6，离 0 极远，不存在 -0.00 折点；double 计算值
//   9.6000000000000014211 与实际 9.6 的偏差为 1.78e-15，比 printf 的舍入
//   容差 0.005 小 12 个数量级；且三个参数都是编译期常量，g++ -O2 会把整个
//   表达式折叠成单个 double 字面量（main.s 中无任何浮点算术指令），
//   不存在 FMA 收缩的空间。
#include <cstdio>

typedef long long ll;

// 题面给定的三个平均分（题目条件，不是答案）
const double AVG_ALL = 9.6;        // 6 名评委打分的平均分
const double AVG_DROP_HIGH = 9.4;  // 去掉一个最高分后 5 人的平均分
const double AVG_DROP_LOW = 9.8;   // 去掉一个最低分后 5 人的平均分

const ll SCORE_CNT = 6;            // 评委人数
const ll REST_CNT = 4;             // 去掉一高一低后剩下的人数

double ans; // 去掉一个最高分和一个最低分后，剩下 4 人的平均分

// 由三个平均分反解出最高分、最低分，再求剩余 4 人的平均分。
void solve() {
    double total = SCORE_CNT * AVG_ALL;                          // 6 人总分 57.6
    double high = total - (SCORE_CNT - 1) * AVG_DROP_HIGH;       // 最高分 10.6
    double low = total - (SCORE_CNT - 1) * AVG_DROP_LOW;         // 最低分 8.6
    ans = (total - high - low) / REST_CNT;                       // 38.4 / 4 = 9.6

    // 题面要求 %5.2f：9.60 占 4 个字符，场宽 5 故左侧补 1 个空格 => " 9.60"。
    printf("%5.2f\n", ans);
}

int main() {
    solve();
    return 0;
}
