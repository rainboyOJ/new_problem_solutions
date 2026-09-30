#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from heapq import heappush, heappop

def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m = next(data)   # 初始奖励
    n = next(data)   # 游戏数
    deadlines = [next(data) for _ in range(n)]   # 各游戏的规定完成期限
    fines = [next(data) for _ in range(n)]       # 各游戏超期扣款数

    # 按期限从小到大逐个尝试安排：小根堆里存“已安排”游戏的扣款数。
    # 若当前游戏安排不下（已安排数超过其期限 deadline），就淘汰堆里扣款最小的一个
    # （记为超期），保证最终扣款总和最小。
    heap: list[int] = []   # 已安排游戏的扣款数（小根堆）
    for deadline, fine in sorted(zip(deadlines, fines)):
        heappush(heap, fine)
        if len(heap) > deadline:                 # 时段不够，牺牲扣款最小的一个
            heappop(heap)

    penalty = sum(fines) - sum(heap)             # 未被安排的游戏才扣款
    print(m - penalty)

if __name__ == "__main__":
    solve()
