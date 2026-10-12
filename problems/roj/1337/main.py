#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:57
# update_at: 2026-10-12 14:52

# 单词查找树的最少结点数 = 去重后的不同前缀个数（含根），
# 用「排序 + 相邻 LCP 计数」直接算出，不真正建树：
# 字典序排序后，第 i 个单词与前面所有单词 LCP 的最大值就是它与前一单词的 LCP，
# 于是它新贡献的结点数 = len(w) - LCP(w, 前一单词)，重复单词贡献 0。
# 如何使用：
# 1. read_words()   按空白切分读入单词表并整体排序（bytes，忽略空行）
# 2. common_prefix(a, b)  求最长公共前缀长度
# 3. count_nodes()  累加 1 + Σ(len(w) - 相邻 LCP)，1 是根结点
# 4. solve()        输出结点总数

import sys

words: list[bytes] = []  # 单词表：bytes 保存，逐字节比较最直接


def read_words() -> None:
    """按空白切分读入所有单词；每行一个，多余的空行自动忽略。"""
    global words
    words = sorted(sys.stdin.buffer.read().split())


def common_prefix(a: bytes, b: bytes) -> int:
    """a、b 的最长公共前缀长度：按位比较，遇到第一个不同的字母就停。"""
    i = 0
    while i < len(a) and i < len(b) and a[i] == b[i]:
        i += 1
    return i


def count_nodes() -> int:
    """结点数 = 1 + Σ(len(w_i) - LCP(w_i, w_{i-1}))，1 是根结点。"""
    nodes = 1 + len(words[0])  # 第一个单词贡献它的全部前缀
    for i in range(1, len(words)):
        # 与前一单词的 LCP 就是与前面所有单词 LCP 的最大值，重复单词贡献 0
        nodes += len(words[i]) - common_prefix(words[i], words[i - 1])
    return nodes


def solve() -> None:
    read_words()
    print(count_nodes())


if __name__ == "__main__":
    solve()
