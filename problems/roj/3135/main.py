#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:22
# update_at: 2026-10-01 19:34

import sys


def relax(dp: list[int], b: list[int], x: int) -> int:
    """把 A 里遇到的这个 x 并入 dp，返回本次写入 dp 的最大值。

    dp[j] 的含义是「以 b[j] 结尾、只用到 A 已扫过前缀」的 LCIS 长度。
    一次从左到右的扫描就能同时完成两件事：best 收集所有 b[j] < x 的 dp[j]
    （它们都是可以接在 x 前面的候选），遇到 b[j] == x 时再用 best + 1 更新。
    因为 best 只增不减，最后一次写入的就是本次的最大值；也因此这里可以直接
    dp[j] = best + 1（不必和旧值取 max）：旧值 g(i-1, j) <= best + 1 恒成立。
    """
    best = 0     # 扫描到当前位置时，所有 b[j] < x 的 dp[j] 的最大值
    written = 0  # 本次写入的最大值，恰好就是「以 x 结尾」的 LCIS 长度
    for j, y in enumerate(b):
        if y < x:
            d = dp[j]
            if d > best:
                best = d
        elif y == x:
            written = best + 1
            dp[j] = written
    return written


def lcis(a: list[int], b: list[int]) -> int:
    """两个等长数列的最长公共上升子序列长度。"""
    dp = [0] * len(b)
    shared = set(a) & set(b)
    upper = len(shared)  # 严格递增，答案不会超过公共不同值的个数
    answer = 0
    for x in a:
        if x not in shared:  # x 不在 B 中，不可能是公共子序列的结尾
            continue
        written = relax(dp, b, x)
        if written > answer:
            answer = written
        if answer == upper:  # 已经取到上界，继续扫也不会更大
            break
    return answer


def solve() -> None:
    nums = list(map(int, sys.stdin.buffer.read().split()))
    n = nums[0]
    # 两个数列都只读实际给出的部分：数据文件末尾若被截断，就按读到的长度算
    a, b = nums[1:n + 1], nums[n + 1:2 * n + 1]
    print(lcis(a, b) if b else 0)


if __name__ == "__main__":
    solve()
