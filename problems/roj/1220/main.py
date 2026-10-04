#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:23
# update_at: 2026-09-30 00:23

import sys


def get_gain(a: str, b: str) -> int | None:
    """词 b 接在词 a 后新增的字符数 = 词长 - 最小合法重叠；None 表示接不上。

    合法重叠要求 a 的后缀等于 b 的前缀，且重叠长度 k < 两词长度——
    k 达到任一词长就意味着整词被包含，题面禁止这种相连。
    取最小 k：重叠越短、接出的龙越长，后续只由 b 决定，短重叠严格更优。
    """
    hit = next((k for k in range(1, min(len(a), len(b))) if a[-k:] == b[:k]), None)
    return None if hit is None else len(b) - hit


def solve() -> None:
    data = iter(sys.stdin.read().split())
    word_count = int(next(data))
    words = [next(data) for _ in range(word_count)]
    head = next(data)                                # 龙的开头字母
    lens = list(map(len, words))

    # gain[i][j]：词 j 接在词 i 后的增益；nxt[i] 按增益降序，先试长的利于剪枝
    gain = [[get_gain(a, b) for b in words] for a in words]                     # n×n 张表
    nxt = [sorted((j for j, g in enumerate(row) if g),
                  key=row.__getitem__, reverse=True) for row in gain]           # 每行一个候选表

    ans = 0
    used = [0] * word_count
    # 剪枝预算：每词还能接的次数 × (词长-1)，重叠至少吃掉 1 个字符
    slack0 = 2 * sum(l - 1 for l in lens)

    def dfs(last: int, cur: int, slack: int) -> None:
        """以 last 结尾、当前长度 cur 的龙继续往下接；slack 是剩余长度上界。"""
        nonlocal ans
        ans = max(ans, cur)
        if cur + slack <= ans:                        # 剩余潜力追不上当前最优，整枝剪掉
            return
        g = gain[last]
        for j in nxt[last]:
            if used[j] < 2:                           # 每个词最多出现两次
                used[j] += 1
                dfs(j, cur + g[j], slack - (lens[j] - 1))
                used[j] -= 1

    for s, w in enumerate(words):                     # 龙头：取每个以 head 开头的词起步
        if w[0] == head:
            used[s] = 1
            dfs(s, lens[s], slack0 - (lens[s] - 1))
            used[s] = 0

    print(ans)


if __name__ == "__main__":
    solve()
