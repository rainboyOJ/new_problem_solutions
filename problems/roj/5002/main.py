#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:41
# update_at: 2026-10-02 15:41

import sys


def num(token: bytes) -> int | float:
    """题面写"实数"，整数 token 原样返回，带小数点的才转 float。"""
    return float(token) if b"." in token else int(token)


def fmt(value: int | float) -> str:
    """整值去掉 .0，与样例的整数输出保持一致。"""
    return str(int(value)) if float(value).is_integer() else str(value)


def min_refuel(segs: list[int | float], capacity: int | float) -> tuple[int, int | float]:
    """贪心扫每段路：油不够走下一段时，在当前站加满；返回加油次数与加油总量。

    只在"被迫"时加油，且一加就加满、加在最后到达的站上——这既不增加次数
    （更晚加油不会让后面更早缺油），也给出每次能走的最长距离，故次数最少。
    """
    tank = capacity   # 出发时油箱满，这一箱不计入加油量
    cnt = 0
    total = 0
    for d in segs:
        if tank >= d:
            tank -= d
        else:
            total += capacity - tank  # 把剩下的油补满：加了多少 = 缺了多少
            tank = capacity - d       # 加满后立刻开过这一段（单段超续航时可为负，与题解口径一致）
            cnt += 1
    return cnt, total


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    while True:
        try:
            n = int(next(tokens))          # 加油站个数
            capacity = num(next(tokens))   # 满箱可跑公里数 = 油箱容量（1 升 1 公里）
        except StopIteration:
            break                          # 多组数据读到文件尾
        segs = [num(next(tokens)) for _ in range(n + 1)]  # n+1 段路的距离
        cnt, total = min_refuel(segs, capacity)
        out.append(f"{cnt} {fmt(total)}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
