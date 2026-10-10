#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:47
# update_at: 2026-10-07 15:47

import sys

MOD = 1000000007  # 答案对 1e9+7 取模

type Ends = list[bool]  # ends[i] = s 的前 i 个字符是否恰好以 t 结尾


def matched_ends(s: str, t: str) -> Ends:
    """线性时间标记 t 在 s 中的每一次出现（允许重叠），返回按结束位置索引的布尔表。"""
    m = len(t)
    # 一次前缀函数求出全部匹配：拼成 t + 分隔符 + s，分隔符取小写字母之外的字符，
    # 这样前缀长度永远跨不过分隔符，等于 m 的位置就是一次完整匹配。
    text = t + '\x00' + s
    pi = [0] * len(text)
    ends: Ends = [False] * (len(s) + 1)
    for i in range(1, len(text)):
        j = pi[i - 1]
        while j and text[i] != text[j]:
            j = pi[j - 1]
        if text[i] == text[j]:
            j += 1
        pi[i] = j
        if j == m:                # 前缀函数涨到 m，说明此处恰好匹配了一整个 t
            ends[i - m] = True    # text 下标 i 换成 s 的 1 起结束位置就是 i - m
    return ends


def count_meanings(s: str, t: str) -> int:
    """按「最靠右的那个取深意的匹配」分类，用 dp 统计互不重叠的匹配组数。"""
    ends = matched_ends(s, t)
    m = len(t)
    # dp[i] = 前 i 个字符的含义种数，dp[0] = 1；要回退 m 格，所以整张表要留着
    dp: list[int] = [1]
    for i in range(1, len(s) + 1):
        best = dp[i - 1]                                  # 没有匹配结束在 i：末段取原意
        if ends[i]:
            best = (best + dp[i - m]) % MOD               # 末尾这段 t 取深意，前面随意
        dp.append(best)
    return dp[-1]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    T = int(next(data))
    out: list[str] = []

    for _ in range(T):
        s = next(data).decode()  # 题面的 s
        t = next(data).decode()  # 题面的 t
        out.append(str(count_meanings(s, t)))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
