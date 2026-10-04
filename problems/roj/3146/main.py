#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:09
# update_at: 2026-10-01 21:29

import sys
from functools import cache

NEG = -(1 << 60)  # 合并时的 -∞ 哨兵：标记"这对子区间合不出任何合法结果"


def calc(op: str, lvals: tuple[int, int], rvals: tuple[int, int]) -> tuple[int, int]:
    """已知左右两段各自的 (最小, 最大)，算出这一步合并后能取到的 (最大, 最小)。

    两侧取值互相独立：加法看两端点相加；乘法只有同号才能变正，
    所以四个端点两两组合全部算一遍，取最大和最小即可。
    """
    pairs = [l * r if op == 'x' else l + r
             for l in lvals for r in rvals]
    return max(pairs), min(pairs)


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    n = int(tokens[0])
    # 输入从边 1 开始按「边、点」交替描述，第 i 对里的 op 是连接顶点 i-1 与顶点 i
    # 的那条边上的运算符，即顶点 j 与 j+1 之间的运算是 ops[(j+1) % n]
    ops: list[str] = [tokens[2 * i + 1].decode() for i in range(n)]
    nums: list[int] = [int(tokens[2 * i + 2]) for i in range(n)]

    @cache
    def merged(i: int, j: int) -> tuple[int, int]:
        """把顶点 i..j（环上顺时针，下标已对 2n 取模）合并成一个顶点后，返回 (最大值, 最小值)。

        区间 DP：枚举最后一次合并发生在哪条内部边上（分割点 k），
        左段 i..k 与右段 k+1..j 各自的最值已知，再用该边运算符合并。
        同时保留最小值，是因为乘法遇负数时"最小"才可能翻成"最大"。
        """
        if i == j:
            return nums[i % n], nums[i % n]
        best, worst = NEG, -NEG
        for k in range(i, j):  # 最后一次合并的是顶点 k 与 k+1 之间的边
            hi, lo = calc(ops[(k + 1) % n], merged(i, k), merged(k + 1, j))
            best = max(best, hi)
            worst = min(worst, lo)
        return best, worst

    doubled = 2 * n  # 环破成链：顶点复制一份接到后面，长度 n 的弧共有 n 种起点
    edge_scores = [merged(i, i + n - 1)[0] for i in range(doubled)]
    best_score = max(edge_scores)

    # 第一步删边 i（连接顶点 i-1 与顶点 i）得到的分值就是从顶点 i 出发的
    # 弧 [i, i+n-1] 的最大值；与全局最优并列的边按编号从小到大输出
    winning = [str(i + 1) for i in range(n) if edge_scores[i] == best_score]
    print(best_score)
    print(' '.join(winning))


if __name__ == "__main__":
    solve()
