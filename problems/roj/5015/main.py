#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2024-12-08 19:30
# update_at: 2026-10-08 21:07

import sys

# 最优子集大小必为奇数 2k+1（偶数大小去掉中心两个之一不会更差），
# 故升序排序后枚举中位数 a[i]，以它为中位数时左右各取 k 个（左侧取紧邻的 k 个、
# 右侧取最大的 k 个），价值关于 k 单峰，用三分法求峰；比较全程交叉相乘避免浮点误差。


def subset_sum(pref: list[int], n: int, i: int, k: int) -> int:
    """以 a[i] 为中位数时的子集元素和：左侧取紧邻的 k 个，右侧取最大的 k 个。"""
    return (pref[i] - pref[i - k - 1]) + (pref[n] - pref[n - k])


def best_value(a: list[int]) -> tuple[int, int]:
    """返回最优价值的 (分子, 分母)：a[1..n] 已升序，下标 0 是占位。"""
    n = len(a) - 1
    pref = [0] * (n + 1)
    for i in range(1, n + 1):
        pref[i] = pref[i - 1] + a[i]

    best_num, best_den = 0, 1  # 单元素子集价值为 0，故答案不低于 0
    for i in range(1, n + 1):
        low, high = 0, min(i - 1, n - i)  # k 的取值范围：左右两边都要够取
        # 对 k 三分：平均数 S(k)/(2k+1) 关于 k 单峰；区间长度收到 2 以内就停手逐个比
        while low < high - 2:
            m1 = low + (high - low) // 3
            m2 = high - (high - low) // 3
            s1, s2 = subset_sum(pref, n, i, m1), subset_sum(pref, n, i, m2)
            if s1 * (2 * m2 + 1) < s2 * (2 * m1 + 1):  # 交叉相乘，避免浮点误差
                low = m1
            else:
                high = m2
        for k in range(low, high + 1):
            s = subset_sum(pref, n, i, k)
            num, den = s - a[i] * (2 * k + 1), 2 * k + 1
            if best_num * den < num * best_den:
                best_num, best_den = num, den
    return best_num, best_den


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    a = [0] + sorted(next(data) for _ in range(n))
    num, den = best_value(a)
    print("%.5f" % (num / den))


if __name__ == "__main__":
    solve()
