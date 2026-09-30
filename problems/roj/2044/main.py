#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 10:00
# update_at: 2026-03-31 10:00

import sys
from collections import Counter, defaultdict


def count_patterns(seq: str, min_len: int, max_len: int) -> Counter[str]:
    """统计字符串中所有长度在 [min_len, max_len] 之间的连续子串频次。"""
    n = len(seq)
    counts: Counter[str] = Counter()
    for length in range(min_len, max_len + 1):
        if length > n:
            break
        for i in range(n - length + 1):
            counts[seq[i : i + length]] += 1
    return counts


def group_and_sort_patterns(counts: Counter[str]) -> list[tuple[int, list[str]]]:
    """将子串按出现频次降序分桶，同一频次内按长度升序、二进制字典序升序排序。"""
    freq_map: defaultdict[int, list[str]] = defaultdict(list)
    for pattern, freq in counts.items():
        freq_map[freq].append(pattern)

    # 频次从大到小排序；同频次内：长度递增、二进制字典序（'0' < '1'）递增
    return [
        (freq, sorted(patterns, key=lambda s: (len(s), s)))
        for freq, patterns in sorted(freq_map.items(), key=lambda item: -item[0])
    ]


def format_frequency_groups(groups: list[tuple[int, list[str]]], top_n: int) -> list[str]:
    """将前 top_n 个频次组按每行最多 6 个模式串的规则格式化为输出行。"""
    lines: list[str] = []
    for freq, patterns in groups[:top_n]:
        lines.append(str(freq))
        for i in range(0, len(patterns), 6):
            lines.append(" ".join(patterns[i : i + 6]))
    return lines


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    a = int(tokens[0])
    b = int(tokens[1])
    n = int(tokens[2])
    seq = "".join(tokens[3:])

    counts = count_patterns(seq, a, b)
    groups = group_and_sort_patterns(counts)
    lines = format_frequency_groups(groups, n)

    print("\n".join(lines))


if __name__ == "__main__":
    solve()
