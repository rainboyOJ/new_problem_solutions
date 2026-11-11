#!/usr/bin/env python3
import sys
from itertools import accumulate, batched, permutations


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    _, _, s, *queries = tokens

    # 预处理 6 种模式串的前缀汉明差异和
    # 利用 initial=0 自动对齐 1-based 前缀和
    prefs = []
    for p in permutations("abc"):
        t = [c != p[i % 3] for i, c in enumerate(s)]
        prefs.append(list(accumulate(t, initial=0)))

    # 回答查询：利用 batched 成对读取 l, r 并 O(1) 查询 6 个基准的最小差异
    out = []
    for l, r in batched(map(int, queries), 2):
        ans = min(p[r] - p[l - 1] for p in prefs)
        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
