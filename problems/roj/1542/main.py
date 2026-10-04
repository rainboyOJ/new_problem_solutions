#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:20
# update_at: 2026-09-30 17:20

import sys
from collections import deque
from collections.abc import Iterator


def window_extremes(arr: list[int], k: int) -> Iterator[tuple[int, int]]:
    """滑动窗口依次产出每个窗口的 (最大值, 最小值)：单调队列按淘汰时机保候选极值。

    hi/lo 存下标，值分别单调递减/递增，队首即当前窗口极值候选；
    下标只增不减，过期元素（下标 <= i-k）从队首弹掉，整体均摊 O(1)。
    """
    hi: deque[int] = deque()  # 队首最大：入队前弹掉所有不小于当前值的下标
    lo: deque[int] = deque()  # 队首最小：入队前弹掉所有不大于当前值的下标
    for i, value in enumerate(arr):
        while hi and arr[hi[-1]] <= value:
            hi.pop()
        hi.append(i)
        while lo and arr[lo[-1]] >= value:
            lo.pop()
        lo.append(i)

        expired = i - k  # 窗口左端已推进到 i-k+1，其前的下标全部过期
        if hi[0] <= expired:
            hi.popleft()
        if lo[0] <= expired:
            lo.popleft()
        if i >= k - 1:  # 首个完整窗口形成后才有答案
            yield arr[hi[0]], arr[lo[0]]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    arr = [next(data) for _ in range(n)]

    out = [f"{mx} {mn}" for mx, mn in window_extremes(arr, k)]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
