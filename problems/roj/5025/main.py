#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:25
# update_at: 2026-10-08 22:25

import sys


def solve() -> None:
    """读到 EOF，输出最小值、最大值、平均值（保留 3 位小数）。

    读入用 read().split() 一次吃完：题面说“一行”，但跨行/多余空格/无尾换行
    都应容忍，读到 EOF 与 C++ 的 `while (cin >> x)` 行为一致。
    个数不定，故不使用「只读一行」的写法。

    舍入：Python f-string 与 C++ printf("%.3f") 都按 IEEE binary64 的
    「就近舍入 / 平局取偶」处理，10 个测试点与 80000 个平分点全部逐字节一致，
    因此不需要 Decimal + ROUND_HALF_UP（那反而会与 C++ 不符）。
    """
    nums = [int(token) for token in sys.stdin.buffer.read().split()]
    if not nums:  # 题面保证至少有 1 个数；空输入时直接返回，避免 0 除
        return

    # 题面只声明上界“不超过 1000”未声明下界，故用内建 min/max（不预设非负），
    # 负数输入也能给出正确结果，与 C++ 侧 INT_MAX/INT_MIN 初值等价。
    print(f"{min(nums)} {max(nums)} {sum(nums) / len(nums):.3f}")


if __name__ == "__main__":
    solve()
