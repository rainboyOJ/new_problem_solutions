#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:30
# update_at: 2026-10-08 07:30

import sys

MAX_N = 30                # 题面上限 n <= 30
MAX_SUM = 2 * MAX_N - 1   # 相邻两数之和的上界 n + (n-1) = 59

# ISPRIME[s]：相邻两数之和 s 是否为素数，下标即和本身；59 以内试除足够快
ISPRIME: list[bool] = [s > 1 and all(s % d for d in range(2, int(s ** 0.5) + 1))
                       for s in range(MAX_SUM + 1)]  # 素数表 60 项


def find_ring(n: int) -> list[int] | None:
    """找一条以 1 开头、候选递增的首个素数链；无解返回 None。

    n 为奇数时无解：n >= 4 的相邻和都是奇素数，故环上相邻两数必须一奇一偶、
    奇偶交替，而奇数 n 的 1..n 中奇数比偶数多一个，必有"奇+奇"相邻，和为偶且 > 2。
    """
    if n % 2:
        return None

    path = [1]  # 固定起点为 1，破掉环的旋转对称
    used = [False] * (n + 1)
    used[1] = True

    def dfs() -> bool:
        """在链尾接一个未用过的数，使相邻和为素数；能否接成完整素数环。"""
        if len(path) == n:
            return ISPRIME[path[-1] + path[0]]  # 只剩尾首闭合这一对要检查
        for v in range(2, n + 1):
            can_place = not used[v] and ISPRIME[path[-1] + v]
            if not can_place:
                continue
            used[v] = True
            path.append(v)
            if dfs():  # 只要任意一组解，成功信号层层上传
                return True
            path.pop()  # 失败回溯：撤销 v
            used[v] = False
        return False

    return path[:] if dfs() else None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)
    ring = find_ring(n) if 1 <= n <= MAX_N else None
    if ring is None:
        return  # 奇数 n 无解：与数据约定一致，输出为空
    # 输出时把起点 1 挪到末尾：环无起点，等价读法，与题面样例 `4 3 2 5 6 1` 一致
    print(*ring[1:] + ring[:1])


if __name__ == "__main__":
    solve()
