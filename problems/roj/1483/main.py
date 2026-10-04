#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:59
# update_at: 2026-09-30 13:59

import sys
from functools import cache


def get_tail(s: str, t: str) -> str:
    """t 接在 s 后面时需要补写的尾巴：先吃掉 t 能与 s 后缀重合的最长前缀。"""
    for k in range(min(len(s), len(t)), 0, -1):
        if s[-k:] == t[:k]:
            return t[k:]
    return t


@cache
def best(mask: int, j: int, strs: tuple[str, ...], tail: tuple[tuple[str, ...], ...]) -> str:
    """包含 mask 中所有串、以 strs[j] 结尾的最短母串，同长取字典序最小。

    状态里"结尾是哪个串"必须记录：新串接在哪里，取决于当前结尾与它的重合。
    """
    if mask == 1 << j:
        return strs[j]
    prev = mask ^ (1 << j)
    # 只考虑把 j 接在某个已有串后（prev >> i & 1 即 i 属于前驱集合）；
    # 更短的前缀一定更优，等长时公共尾巴不改变字典序比较结果
    return min(
        (best(prev, i, strs, tail) + tail[i][j] for i in range(len(strs)) if prev >> i & 1),
        key=lambda s: (len(s), s),
    )


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    words = [w.decode() for w in data[1:n + 1]]

    # 被别的串完全包含的串删掉：母串含住大串就自动含住了它，留着只会白花状态
    uniq = list(dict.fromkeys(words))
    strs = tuple(s for s in uniq if not any(s in t for t in uniq if t != s))

    # 补尾表：tail[i][j] = 把 strs[j] 接到 strs[i] 后面还需要写的部分
    tail = tuple(tuple(get_tail(s, t) for t in strs) for s in strs)

    full = (1 << len(strs)) - 1  # 全集掩码：所有串都已包含的终点状态
    print(min(
        (best(full, j, strs, tail) for j in range(len(strs))),
        key=lambda s: (len(s), s),
    ))


if __name__ == "__main__":
    solve()
