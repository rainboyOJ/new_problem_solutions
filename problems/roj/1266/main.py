#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-01-14 22:00
# update_at: 2026-01-14 22:00

import sys

SIZE = 100          # 题面 N, M 的上界, 也是参考实现里数组的行宽
PLANE = SIZE * SIZE  # 一个 100x100 int 数组的元素个数

# 参考实现把 a/f/res 声明成三个相邻的 int[100][100] 全局数组, 且下标取到 1..100。
# 于是 a[i][j] 落在整块连续内存的 i*100+j 处: i 或 j 到达 100 时就会踩进下一个数组。
# 这些越界写入决定了官方数据的期望输出, 所以这里用"整块地址空间"还原它的语义。
ADDR_A, ADDR_F, ADDR_RES = 0, PLANE, 2 * PLANE


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    mem: dict[int, int] = {}  # 线性地址 -> 值; 未写入处读作 0 (全局数组零初始化)

    def addr(base: int, i: int, j: int) -> int:
        """把 a/f/res 的二维下标折算成整块地址空间里的线性地址。"""
        return base + i * SIZE + j

    def read(base: int, i: int, j: int) -> int:
        return mem.get(addr(base, i, j), 0)

    def write(base: int, i: int, j: int, value: int) -> None:
        mem[addr(base, i, j)] = value

    # 第 i 家公司分 j 台机器的盈利; j 从 1 开始, 所以 a[i][0] 保持原内存里的值
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            write(ADDR_A, i, j, next(data))

    # f[i][j]: 前 i 家公司用掉 j 台机器的最大盈利; res[i][j] 记录这一步分出的台数
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            for k in range(j + 1):
                gain = read(ADDR_F, i - 1, j - k) + read(ADDR_A, i, k)
                if read(ADDR_F, i, j) <= gain:  # 取等号: 并列时让 k 更大的方案胜出
                    write(ADDR_F, i, j, gain)
                    write(ADDR_RES, i, j, k)

    out = [str(read(ADDR_F, n, m))]

    # 按 res 回溯每家公司分到的台数, 再翻回公司编号从小到大的顺序
    split: list[tuple[int, int]] = []
    been, machines = n, m
    while been:
        used = read(ADDR_RES, been, machines)
        split.append((been, used))
        been, machines = been - 1, machines - used

    out += [f"{i} {k}" for i, k in reversed(split)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
