#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:52
# update_at: 2026-09-30 20:52

import sys
from collections import deque

PART = 100_000  # 输出分块大小：整行 join 会同时生成上百万个临时 str，分块后峰值内存大幅下降


def window_extremes(a: list[int], k: int, want_max: bool) -> list[int]:
    """单调队列求每个长为 k 的窗口的最值：want_max=False 求最小值，True 求最大值。

    队列里只保留下标，且对应值保持单调，队首就是当前窗口的最值候选。
    """
    # 队尾保留条件：只有新元素不比队尾优才留着队尾；两个方向共用同一段扫描逻辑
    # 求最大时队列递减（保留「不更大」的队尾），求最小时队列递增（保留「不更小」的队尾）
    keep_tail = (lambda new, old: new <= old) if want_max else (lambda new, old: new >= old)
    dq: deque[int] = deque()
    out: list[int] = []
    for i, x in enumerate(a):
        while dq and not keep_tail(x, a[dq[-1]]):
            dq.pop()                      # 队尾被新元素压过，窗口右移后它只会更旧，永远出局
        dq.append(i)
        if dq[0] <= i - k:                # 队首已滑出窗口左边界
            dq.popleft()
        if i >= k - 1:                    # 第一个完整窗口形成，之后每步产出一个答案
            out.append(a[dq[0]])
    return out


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n, k = data[0], data[1]               # 数组长度、窗口长度
    a = data[2 : 2 + n]
    del data                               # 序列已由 a 持有，尽早释放整个 token 列表

    # 按题面顺序：第一行最小值、第二行最大值；算完一行分块写出，临时 str 列表不整行堆积
    write = sys.stdout.write
    for want_max in (False, True):
        ext = window_extremes(a, k, want_max)
        for start in range(0, len(ext), PART):
            if start:                     # 块间补一个空格，整行仍是单空格分隔、末尾无空格
                write(" ")
            write(" ".join(map(str, ext[start : start + PART])))
        write("\n")


if __name__ == "__main__":
    solve()
