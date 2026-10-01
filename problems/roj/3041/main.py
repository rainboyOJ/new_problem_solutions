#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:39
# update_at: 2026-10-01 11:39

import sys

children: list[dict[int, int]] = [{}]  # children[i][字符编码] = 结点 i 沿该边的儿子编号
cnt: list[int] = [0]                   # cnt[i] = 在结点 i 结尾的 S_i 个数（即它作为完整串出现几次）


def insert(word: bytes) -> None:
    """把 word 插进 Trie：已有的边直接走，缺的边现建儿子。"""
    node = 0
    for ch in word:
        nxt = children[node].get(ch)
        if nxt is None:
            nxt = len(children)
            children.append({})
            cnt.append(0)
            children[node][ch] = nxt
        node = nxt
    cnt[node] += 1


def count_prefix(word: bytes) -> int:
    """word 是多少个 S_i 的前缀：word 的每个前缀对应 Trie 根向下的一条路径，累加路径各点的结尾计数。"""
    node, total = 0, 0
    for ch in word:
        node = children[node].get(ch, -1)
        if node < 0:  # 这条前缀在 Trie 里都走不出来，更长的更不可能
            break
        total += cnt[node]
    return total


def solve() -> None:
    data = sys.stdin.buffer.read().split()  # 保留 bytes：迭代时逐个产出字符编码，省去解码
    n, m = int(data[0]), int(data[1])
    for word in data[2:2 + n]:
        insert(word)
    print('\n'.join(str(count_prefix(q)) for q in data[2 + n:2 + n + m]))


if __name__ == "__main__":
    solve()
