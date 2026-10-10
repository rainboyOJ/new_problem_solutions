#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:43
# update_at: 2026-10-07 15:43

import sys

EMPTY_PREFIX = 0  # 下标 0 代表空前缀，fail[0] = 0 且它本身不参与答案统计


def fail_table(text: str) -> list[int]:
    """fail[length] = 长度 length 的前缀的最长真 border 长度；fail[0] 恒为 0。"""
    n = len(text)
    fail = [EMPTY_PREFIX] * (n + 1)
    k = 0                                            # 当前已匹配上的 border 长度
    for length in range(2, n + 1):
        while k > 0 and text[k] != text[length - 1]:
            k = fail[k]                              # 失配就沿 fail 链往回跳
        if text[k] == text[length - 1]:
            k += 1                                   # 接上了，border 长度加一
        fail[length] = k
    return fail


def count_even_prefixes(fail: list[int]) -> int:
    """求所有偶数长度的前缀在整串中出现的次数之和。

    fail 把每个前缀长度连向它的最长真 border，构成一棵以空前缀为根的树；
    长度 i 的前缀每作为别人的 border 出现一次，就对应它的一个后代，
    所以自底向上把子树和并给父亲，得到的 occur[i] 就是出现次数。
    """
    n = len(fail) - 1
    # 每个非空前缀至少以整串起点出现一次；下标 EMPTY_PREFIX 是空前缀，不计数
    occur = [1] * (n + 1)
    occur[EMPTY_PREFIX] = 0
    for length in range(n, 0, -1):                   # 儿子编号恒大于父亲，逆序即自底向上
        occur[fail[length]] += occur[length]
    return sum(occur[2::2])                          # 只保留长度 2、4、6、… 的前缀


def solve() -> None:
    # 输入只有一行字符串，直接按行读可以原样保留字符；这里没有位置量需要按 next() 消费
    text = sys.stdin.readline().strip()
    print(count_even_prefixes(fail_table(text)))


if __name__ == "__main__":
    solve()
