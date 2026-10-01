#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:57
# update_at: 2026-10-01 09:57

MAX_N = 12  # 题面要求输出 n = 1..12 的全部答案


def solve() -> None:
    """按四塔递推填出 f[1..MAX_N] 并逐行输出。"""
    f = [0] * (MAX_N + 1)  # f[n]：n 个盘从 A 柱搬到 D 柱的最少步数；f[0] = 0 表示空柱不用搬
    for n in range(1, MAX_N + 1):
        # 枚举第一个"拆点" k：先用四塔把 k 个最小盘搬到中转柱（f[k] 步），
        # 再用三塔把剩下 n-k 个大盘搬到 D 柱（1 << (n - k) 再减 1 步，此时中转柱被小盘占住），
        # 最后用四塔把 k 个最小盘接到 D 柱上（又是 f[k] 步）。
        # k = 0 对应"不借第四座塔"，即标准三塔搬法 2^n - 1 步，同样要参与取最小。
        f[n] = min(2 * f[k] + (1 << (n - k)) - 1 for k in range(n))
    print("\n".join(map(str, f[1:])))


if __name__ == "__main__":
    solve()
