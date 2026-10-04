#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:50
# update_at: 2026-09-30 14:06

import sys
from collections import deque


def build_automaton(words: list[bytes]) -> tuple[list[list[int]], list[int]]:
    """插入屏蔽词建 trie 并 BFS 补全转移表，返回完整 goto 表 go 与词尾长度 lend。

    go[v][c] 是"在状态 v 读到字符 c 后该去哪"，BFS 时若 v 没有 c 边就直接继承 fail[v]
    的 c 转移，于是每个字符都只查一次表，不必再沿 fail 链回退。lend[v] 只在 v 是某个
    屏蔽词结尾时非 0，值就是该词长度；题目保证没有屏蔽词是另一个的子串，所以每个状
    态至多是一个词的结尾，这个长度可以直接当"删多少"用。
    """
    trie: list[dict[int, int]] = [{}]  # 根是 0；每节点一个 dict，只存 trie 上真实存在的边
    lend: list[int] = [0]              # lend[v]：以 v 结尾的屏蔽词长度，非结尾为 0

    for w in words:
        node = 0
        for c in w:
            nxt = trie[node].get(c)
            if nxt is None:
                trie[node][c] = len(trie)
                trie.append({})
                lend.append(0)
                nxt = len(trie) - 1
            node = nxt
        lend[node] = len(w)

    # BFS 补全：go[v][c] 默认继承 go[fail[v]][c]，根上缺的边一律回到根。
    go = [[0] * 256 for _ in trie]
    for v, edges in enumerate(trie):
        for c, u in edges.items():
            go[v][c] = u

    fail: list[int] = [0] * len(trie)  # 根与根的孩子 fail 都默认是 0
    queue = deque(trie[0].values())
    while queue:
        node = queue.popleft()
        base = go[fail[node]]          # 缺边时要继承的那一行
        for c, nxt in trie[node].items():
            fail[nxt] = base[c]
            queue.append(nxt)
        for c in range(256):           # 补全 node 自己缺的边（含 26 个字母与其余无关字符）
            if not go[node][c]:
                go[node][c] = base[c]
    return go, lend


def censor(text: bytes, go: list[list[int]], lend: list[int]) -> bytes:
    """从左到右扫描 text，边扫边删屏蔽词，返回删除后的结果。

    关键：删除后"从头重新找"并不需要真的重扫，因为删除只会让左边已匹配的前缀去
    接右边新来的字符。用栈保存每个字符以及"读入它之后自动机所在的状态"，一旦命
    中屏蔽词就把栈顶 pop 掉对应长度，并把自动机回退到 pop 后栈顶记录的状态——这
    正是"从头重新找"会到达的状态，于是整体只需一趟线性扫描。
    """
    kept = bytearray()                # 保留下来的字符，即答案
    state = [0]                       # state[i]：读完 kept[:i] 后自动机所在状态
    node = 0
    for c in text:
        node = go[node][c]            # 转移表已补全，O(1) 就能读到下一个状态
        kept.append(c)
        state.append(node)
        length = lend[node]                     # 非 0 表示刚读入的字符凑齐了一个屏蔽词
        if length:
            del kept[len(kept) - length:]
            del state[len(state) - length:]     # 同步弹掉这 length 个字符记录的状态
            node = state[-1]                    # 等价于回到删除前的位置重新匹配
    return bytes(kept)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    text = next(data)
    n = int(next(data))
    words = [next(data) for _ in range(n)]            # n 个屏蔽词
    go, lend = build_automaton(words)
    sys.stdout.buffer.write(censor(text, go, lend) + b'\n')


if __name__ == "__main__":
    solve()
