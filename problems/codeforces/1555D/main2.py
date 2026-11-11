#!/usr/bin/env python3
import itertools
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    _, _, s, *queries = tokens

    # 预处理 6 种全排列在原串各个位置上的累积汉明差异前缀和
    prefs = [
        list(itertools.accumulate((c != p[i % 3] for i, c in enumerate(s)), initial=0))
        for p in itertools.permutations("abc")
    ]

    # 成对读取 l, r 并 O(1) 提取 6 个基准的最小差异
    it = iter(map(int, queries))
    sys.stdout.write(
        "\n".join(str(min(p[r] - p[l - 1] for p in prefs)) for l, r in zip(it, it))
        + "\n"
    )


if __name__ == "__main__":
    solve()
