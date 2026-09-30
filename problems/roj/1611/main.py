#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:59
# update_at: 2026-09-30 21:59

import sys
from collections.abc import Iterator


def read_ints() -> Iterator[int]:
    """按块解码输入：一次 read() 全读再 split() 会同时留下 25 MB 字节和 300 万个 token 对象。"""
    stream = sys.stdin.buffer
    tail = b""
    while block := stream.read(1 << 20):
        body, _, tail = (tail + block).rpartition(b"\n")  # 末行可能被切断，留给下一块拼
        yield from map(int, body.split())
    yield from map(int, tail.split())


def solve() -> None:
    data = read_ints()
    n = next(data)

    # 凸壳用「队尾 list.append/list.pop + 队头指针 h」实现，两个数是斜率 m 和截距 b。
    slope: list[int] = []
    intercept: list[int] = []
    head = 0
    # 前缀量边读边更新：W = W[i-1] = sum_{t<i} P_t，D = D[i-1] = sum_{t<i} P_t*X_t；
    # best = dp[i-1]，即「前 i-1 个工厂处理完且第 i-1 个建仓」的最小费用。
    W = D = best = 0

    for _ in range(n):
        x, p, c = next(data), next(data), next(data)

        # dp[j] 对应的直线 y = -W[j]*x + dp[j] + D[j]，新直线永远接在队尾
        m, b = -W, best + D
        while len(slope) - head >= 2:
            # 两条旧直线的交点横坐标 x12 与末条、新直线的交点 x23：x12 >= x23 时末条永不为最小
            x12 = (intercept[-1] - intercept[-2]) * (slope[-1] - m)
            x23 = (b - intercept[-1]) * (slope[-2] - slope[-1])
            if x12 < x23:
                break
            slope.pop()
            intercept.pop()
        slope.append(m)
        intercept.append(b)

        while len(slope) - head >= 2:
            # 查询点 x 单调不减：队头一旦不优于第二条，之后也不会翻身
            if slope[head] * x + intercept[head] < slope[head + 1] * x + intercept[head + 1]:
                break
            head += 1

        best = c + x * W - D + slope[head] * x + intercept[head]  # dp[i]
        W += p
        D += p * x

    print(best)


if __name__ == "__main__":
    solve()
