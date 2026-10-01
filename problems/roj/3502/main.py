#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:27
# update_at: 2026-10-02 04:27

import sys
from functools import cache


def min_overlap(a: str, b: str) -> int | None:
    """a 后接 b 的最小合法重叠长度：k 从 1 试起，接不上返回 None。

    k 只试到 min(len(a), len(b)) - 1，自动排除整词包含——如 at 接 atide
    唯一能对上的重叠 k=2 恰好等于 len(at)，所以两词不能相连。
    """
    for k in range(1, min(len(a), len(b))):
        if a[-k:] == b[:k]:
            return k
    return None


def solve() -> None:
    data = iter(sys.stdin.read().split())
    word_count = int(next(data))
    words = [next(data) for _ in range(word_count)]
    head = next(data)

    # overlap[i][j]：词 j 接在词 i 后的最小合法重叠；None 表示接不上
    overlap: list[list[int | None]] = [
        [min_overlap(a, b) for b in words] for a in words  # n^2 对
    ]

    @cache
    def remain(last: int, used: tuple[int, ...]) -> int:
        """词 last 收尾、各词已用次数为 used 时，还能追加的最大字符数。"""
        best = 0
        for j, k in enumerate(overlap[last]):
            if used[j] == 2 or k is None:
                continue                                       # 用满两次或接不上
            used_j = used[:j] + (used[j] + 1,) + used[j + 1:]  # 只改第 j 位，保持 tuple 可哈希
            gain = len(words[j]) - k                           # 重叠部分在龙里只计一次
            best = max(best, gain + remain(j, used_j))
        return best

    # 龙头：任一以 head 开头的词做第一个词，整词计入长度
    ans = 0
    for i, w in enumerate(words):
        if w[0] != head:
            continue
        used = [0] * word_count
        used[i] = 1
        ans = max(ans, len(w) + remain(i, tuple(used)))
    print(ans)


if __name__ == "__main__":
    solve()
