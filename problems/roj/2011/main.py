#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def find_longest_palindrome(letters: str) -> tuple[int, int, int]:
    """用 Manacher 算法计算最长回文子串在字母串中的 (长度, 起始下标, 结束下标)。"""
    t = "^#" + "#".join(letters) + "#$"
    p = [0] * len(t)
    center = right = 0
    max_len = 0
    best_start = 0

    for i in range(1, len(t) - 1):
        p[i] = min(right - i, p[2 * center - i]) if right > i else 0
        while t[i + 1 + p[i]] == t[i - 1 - p[i]]:
            p[i] += 1
        if i + p[i] > right:
            center, right = i, i + p[i]
        # p[i] 即为原字母串中以相应中心为核心的回文半径/长度
        if p[i] > max_len:
            max_len = p[i]
            best_start = (i - p[i]) // 2  # 映射回 letters 中的起始下标

    return max_len, best_start, best_start + max_len - 1


def solve() -> None:
    raw = sys.stdin.read()
    if not raw:
        return

    # 提取所有字母及其在原始文本中的索引，统一转小写进行匹配
    indexed_letters = [(ch.lower(), idx) for idx, ch in enumerate(raw) if ch.isalpha()]
    if not indexed_letters:
        print(0)
        return

    clean_chars = "".join(ch for ch, _ in indexed_letters)
    max_len, l_idx, r_idx = find_longest_palindrome(clean_chars)

    orig_start = indexed_letters[l_idx][1]
    orig_end = indexed_letters[r_idx][1]

    print(max_len)
    print(raw[orig_start : orig_end + 1])


if __name__ == "__main__":
    solve()
