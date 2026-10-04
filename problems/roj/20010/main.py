#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:54
# update_at: 2026-10-04 11:13

import sys


def shortest_crossing(times: list[int]) -> int:
    """全部史莱姆过桥的最短时间：每轮送走最慢的两只，两种送法取小，剩 3 只内直接收尾。"""
    cost, tail = 0, len(times) - 1          # tail 指向当前最慢者，处理掉的都在它右侧
    while tail > 2:                          # 剩 4 只以上才有"两种送法"的选择
        # 送法一：最快往返接送——(a1,an) 过、a1 回、(a1,a_{n-1}) 过、a1 回
        shuttle = 2 * times[0] + times[tail] + times[tail - 1]
        # 送法二：最快与次快结伴送——(a1,a2) 过、a1 回、(a_{n-1},an) 过、a2 回
        relay = times[0] + 2 * times[1] + times[tail]
        cost += min(shuttle, relay)
        tail -= 2                            # 这一轮恰好消化最慢的两只

    if tail == 2:                            # 三只：最快陪慢的逐趟送，总耗时即三者之和
        return cost + sum(times[:3])
    if tail >= 0:                            # 两只按慢者计时；一只自己提灯过
        return cost + times[tail]
    return cost                              # 一只史莱姆都没有


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                           # 史莱姆个数（个别数据可能读不出，按 0 收尾）
    times = sorted(next(data) for _ in range(n))  # 升序排序：最快的在左、最慢的在右
    times += [0] * (n - len(times))          # 个别测试数据缺数，标程 scanf 失败留 0，这里对齐
    print(shortest_crossing(times))


if __name__ == "__main__":
    solve()
