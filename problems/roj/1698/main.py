#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:48
# update_at: 2026-10-07 15:48

import sys
from collections.abc import Iterator
from itertools import islice

# 同构匹配的判定：dist[i] = i 到「上一次出现同一字符的位置」的距离。
# 比较窗口内第 k 位时按窗口长度 k 裁剪：dist >= k 表示该字符在窗口内是首次出现，统一记 0。
# 模式侧第 k 位的裁剪恒为 k（窗口就是 t 的前 k 位），所以可以静态预处理成 sig[]。


def tokens() -> Iterator[bytes]:
    """逐行读入并顺序吐出 token：单行最长约 7MB，整块 split 会造出数百万个 bytes 对象。"""
    for line in sys.stdin.buffer:
        yield from line.split()


def distances(nums: Iterator[int], length: int, last: list[int]) -> list[int]:
    """dist[i] = 第 i 个字符到上一次出现位置的距离；last[x] 记录字符 x 最近出现的位置。"""
    dist = [0] * (length + 1)
    for i, x in enumerate(nums, 1):
        dist[i] = i - last[x]
        last[x] = i
    return dist


def signature(dist: list[int], m: int) -> list[int]:
    """模式侧签名 sig[k]：第 k 位按窗口长度 k 裁剪，窗口内首次出现的字符记 0。"""
    return [0] + [dist[k] if dist[k] < k else 0 for k in range(1, m + 1)]


def fail_table(sig: list[int], dist: list[int], m: int) -> list[int]:
    """失配数组 fail[i] = t 的前 i 位在同构意义下的最长真 border 长度。"""
    fail = [0] * (m + 1)
    j = 0
    for i in range(1, m):
        k = j + 1
        d = dist[i + 1] if dist[i + 1] < k else 0  # 文本侧按当前窗口长度 k 动态裁剪
        while j and d != sig[k]:
            j = fail[j]
            k = j + 1
            d = dist[i + 1] if dist[i + 1] < k else 0
        if d == sig[k]:
            j += 1
        fail[i + 1] = j
    return fail


def match_starts(text: list[int], sig: list[int], fail: list[int], n: int, m: int) -> list[int]:
    """在 s 的距离数组上跑 KMP，按升序产出所有匹配子串的首位下标。"""
    starts: list[int] = []
    j = 0
    for i in range(1, n + 1):
        k = j + 1
        d = text[i] if text[i] < k else 0
        while j and d != sig[k]:
            j = fail[j]
            k = j + 1
            d = text[i] if text[i] < k else 0
        if d == sig[k]:
            j += 1
        if j == m:
            starts.append(i + 1 - m)  # 匹配段为 [i-m+1, i]
            j = fail[j]
    return starts


def solve() -> None:
    data = tokens()
    T = int(next(data))
    charset = int(next(data))
    out: list[str] = []

    for _ in range(T):
        n = int(next(data))
        m = int(next(data))

        last = [0] * (charset + 1)  # last[x] = 字符 x 最近一次出现的位置
        s_dist = distances(map(int, islice(data, n)), n, last)
        last = [0] * (charset + 1)
        t_dist = distances(map(int, islice(data, m)), m, last)

        sig = signature(t_dist, m)
        starts = match_starts(s_dist, sig, fail_table(sig, t_dist, m), n, m)
        out.append(str(len(starts)))
        out.append(' '.join(map(str, starts)))  # 空答案就是空行，和题面输出格式一致

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
