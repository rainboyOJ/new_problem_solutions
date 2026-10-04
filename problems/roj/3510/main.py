#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:37
# update_at: 2026-10-02 04:47

import sys

NEG = -10**9  # 不可达状态的哨兵：份数超过字符数时凑不出合法划分


def match_end(text: str, words: list[str]) -> list[int | None]:
    """end[p]：从 p 出发能匹配的最短单词的末尾下标；该处匹配不到任何单词则为 None。

    同一起点匹配多个单词时只留最短的：整段落在一份里的前提是末尾不越界，
    最短的能放下，其余更长的也一定能放下。
    """
    ends: list[int | None] = []
    for p in range(len(text)):
        lens = [len(w) for w in words if text.startswith(w, p)]
        ends.append(p + min(lens) - 1 if lens else None)
    return ends


def build_cut(ends: list[int | None]) -> list[list[int]]:
    """cut[t][j]：把 [t, j) 单独作一份时能数到的单词起点数。

    起点 p 只有在“单词完整落在份内”（末尾 ≤ j-1）时才计 1 次；
    多个单词共享同一起点只算一个（首字母只能用一次）。
    """
    n = len(ends)
    cut = [[0] * (n + 1) for _ in range(n + 1)]
    for j in range(1, n + 1):
        acc = 0
        for t in range(j - 1, -1, -1):  # 右端点固定，左端点从右往左累计
            acc += ends[t] is not None and ends[t] <= j - 1
            cut[t][j] = acc
    return cut


def max_words(text: str, words: list[str], k: int) -> int:
    """把 text 切成恰好 k 份非空连续段，最大化各份内可数的单词起点总数。"""
    n = len(text)
    cut = build_cut(match_end(text, words))

    # f[j][m]：前 j 个字符恰好分成 m 份的最大单词数；t 是最后一份的左端点
    f = [[NEG] * (k + 1) for _ in range(n + 1)]
    f[0][0] = 0
    for j in range(1, n + 1):
        for m in range(1, min(j, k) + 1):  # 每份至少 1 个字符，m > j 不可达
            f[j][m] = max(f[t][m - 1] + cut[t][j] for t in range(m - 1, j))
    return f[n][k]


def solve() -> None:
    lines = [ln.strip() for ln in sys.stdin.read().splitlines() if ln.strip()]
    out: list[str] = []
    i = 0
    while i < len(lines):  # 输入可能包含多组测试数据
        p, k = map(int, lines[i].split())  # p 行字母串，切成 k 份
        i += 1
        text = "".join(lines[i:i + p])  # 每行恰好 20 个字母，合并成一个串
        i += p
        s = int(lines[i])  # 字典单词个数
        i += 1
        words = lines[i:i + s]
        i += s
        out.append(str(max_words(text, words, k)))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
