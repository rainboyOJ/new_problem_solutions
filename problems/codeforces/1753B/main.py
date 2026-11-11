#!/usr/bin/env python3
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, x = int(tokens[0]), int(tokens[1])

    # 统计每个数字出现的次数
    cnt = [0] * (x + 1)
    for v in map(int, tokens[2:]):
        cnt[v] += 1

    # 阶乘进位模拟：从 1! 到 x!
    for i in range(1, x):
        if cnt[i] % (i + 1) != 0:
            sys.stdout.write("No\n")
            return
        cnt[i + 1] += cnt[i] // (i + 1)

    sys.stdout.write("Yes\n")


if __name__ == "__main__":
    solve()
