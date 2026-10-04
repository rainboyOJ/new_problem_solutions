#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def next_jam(word: str, t: int) -> str | None:
    """求紧接在 word 之后的 Jam 数字；已是最大则返回 None。

    从最右位往左找第一个还能增大的位置：该位的上界是
    t（最右位）或右邻位的前一个字母（其余位，保证严格递增）。
    该位加 1 后，右边所有位取「能取的最小字母」，即紧随其后的连续字母。
    """
    for i in reversed(range(len(word))):
        # 上界：最右位是第 t 号字母，其余位是右邻位的前一个字母（保证严格递增）
        limit = ord('a') + t - 1 if i == len(word) - 1 else ord(word[i + 1]) - 1
        if ord(word[i]) < limit:
            # 右侧 w-1-i 位取 word[i]+1 起的连续字母
            return word[:i] + ''.join(chr(ord(word[i]) + 1 + k)
                                      for k in range(len(word) - i))
    return None


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    s = int(next(tokens))
    t = int(next(tokens))
    w = int(next(tokens))
    word = next(tokens).decode()  # s 在找后继时用不到，读入只为完整解析输入

    out = []
    for _ in range(5):
        word = next_jam(word, t)
        if word is None:
            break
        out.append(word)
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
