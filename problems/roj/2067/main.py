#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:17
# update_at: 2026-10-01 06:17

import heapq
import sys
from collections.abc import Iterator


def finish_times(times: list[int], jobs: int) -> list[int]:
    """把 jobs 个工件派给这批同型机器，按升序返回「全车间完成第 k 个工件」的时刻。

    每台机器的工作时间总是 t 的倍数：t, 2t, 3t, ...。把「现在派一个工件给这台机器」
    看成一次待选事件，键取该事件产生的完工时刻，则小根堆弹出第 k 次就是第 k 个工件
    最早能完工的时刻；得到的升序向量在各派工方案中逐项最小，最后一项即最短完工时间。
    """
    heap = [(t, t) for t in times]  # (此刻派活的完工时刻, 机器时长)
    heapq.heapify(heap)
    done: list[int] = []
    for _ in range(jobs):
        finish, t = heap[0]                       # 下一次派活完工最早的机器
        heapq.heapreplace(heap, (finish + t, t))  # 同一台机器顺延到下一件
        done.append(finish)
    return done


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n, m1, m2 = next(data), next(data), next(data)
    time_a = [next(data) for _ in range(m1)]  # A 型机器做一次操作的时间
    time_b = [next(data) for _ in range(m2)]  # B 型机器做一次操作的时间

    finish_a = finish_times(time_a, n)  # 升序：A 车间第 k 个完工时刻
    finish_b = finish_times(time_b, n)  # 升序：B 车间第 k 个可收尾槽位
    ans_a = finish_a[-1]
    # 慢的先交给 B：A 完工时刻从大到小，对齐 B 从小到大的空闲槽位，最大值最小
    ans_b = max(a + b for a, b in zip(reversed(finish_a), finish_b))

    print(ans_a, ans_b)


if __name__ == "__main__":
    solve()
