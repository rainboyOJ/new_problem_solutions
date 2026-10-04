#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 13:04
# update_at: 2026-10-01 13:04

import heapq
import sys
from bisect import bisect_left
from collections import deque

INF = 10**18                          # 大于一切输入时刻的"无穷远"
FREE: list[list[int]] = []            # 地址升序的空闲块 [首地址, 长度]


def alloc(need: int) -> int | None:
    """首地址最小、长度放得下 need 的空闲片：划走 need 并返回首地址；放不下返回 None。"""
    for i, (start, size) in enumerate(FREE):
        if size >= need:
            if size > need:
                FREE[i] = [start + need, size - need]   # 片尾余量留在原地
            else:
                FREE.pop(i)
            return start
    return None


def release(start: int, size: int) -> None:
    """归还 [start, start+size)：按地址插回空闲表，并与左右相邻的空闲块合并。"""
    i = bisect_left(FREE, start, key=lambda block: block[0])
    if i and FREE[i - 1][0] + FREE[i - 1][1] == start:   # 与左邻块衔接
        start, size = FREE[i - 1][0], size + FREE[i - 1][1]
        FREE.pop(i - 1)
        i -= 1
    if i < len(FREE) and FREE[i][0] == start + size:     # 与右邻块衔接
        size += FREE[i][1]
        FREE.pop(i)
    FREE.insert(i, [start, size])


def simulate(N: int, arrive: list[tuple[int, int, int]]) -> tuple[int, int]:
    """事件推进模拟：先释放、再派队头、后处理新到达；返回 (全部结束时刻, 进过队列的进程数)。"""
    FREE.clear()
    FREE.append([0, N])                           # 初始整段空闲
    running: list[tuple[int, int, int]] = []      # 二叉堆 (结束时刻, 首地址, 长度)
    wait: deque[tuple[int, int]] = deque()        # 等待队列 (单元数, 运行时间)
    queued = 0                                    # 放入过等待队列的进程总数
    now, i = 0, 0

    while i < len(arrive) or running:
        # 下一事件时刻：最早到达的进程与最早结束的进程，谁早听谁的
        now = min(arrive[i][0] if i < len(arrive) else INF,
                   running[0][0] if running else INF)

        # 1) 此刻结束的进程全部归还：T+P 时刻它们占的单元已经可用
        while running and running[0][0] == now:
            _, start, size = heapq.heappop(running)
            release(start, size)

        # 2) 队头放得下就立刻上机；队头放不下时，队列里谁也不能越过它上机
        while wait:
            start = alloc(wait[0][0])
            if start is None:
                break                              # 队头还是放不下，后面的进程没资格先上
            m, p = wait.popleft()
            heapq.heappush(running, (now + p, start, m))

        # 3) 时刻 now 到达的进程依次申请：放不下才进队列；直接到达者不受队头约束
        while i < len(arrive) and arrive[i][0] == now:
            m, p = arrive[i][1], arrive[i][2]
            start = alloc(m)
            if start is None:
                wait.append((m, p))                # 进过队列就算数，之后再被弹出也一样
                queued += 1
            else:
                heapq.heappush(running, (now + p, start, m))
            i += 1

    return now, queued                             # 循环结束时 running 已清空，now 即全部结束时刻


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    N = next(data)                                 # 总内存单元数，地址 0..N-1

    arrive: list[tuple[int, int, int]] = []        # (申请时刻, 单元数, 运行时间)，已按时刻升序
    while True:
        T, M, P = next(data), next(data), next(data)
        if T == 0 and M == 0 and P == 0:
            break
        arrive.append((T, M, P))

    finish, queued = simulate(N, arrive)
    print(finish)
    print(queued)


if __name__ == "__main__":
    solve()
