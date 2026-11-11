#!/usr/bin/env python3
from collections import Counter
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, x = int(tokens[0]), int(tokens[1])

    # 使用 Counter 一行统计频次，缺失键默认返回 0
    cnt = Counter(map(int, tokens[2:]))

    for i in range(1, x):
        if cnt[i] % (i + 1):
            sys.stdout.write("No\n")
            return
        cnt[i + 1] += cnt[i] // (i + 1)

    sys.stdout.write("Yes\n")


if __name__ == "__main__":
    solve()
