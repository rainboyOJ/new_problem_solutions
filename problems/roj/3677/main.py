#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:07
# update_at: 2026-10-02 15:30

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # 题面声明的串长
    text = next(data)[:n]  # 以字节读入，小写字母的 ASCII 值直接参与编码

    # 归约状态 = 栈内容。把所有出现过的栈内容组织成一棵 trie：
    # nodes[i] = (父亲节点 << 8) | 栈顶字符，0 号节点是空栈；
    # cnt[i] 记录前缀状态恰为节点 i 的次数，相同栈内容复用同一节点编号。
    nodes = [0]
    cnt = [1]  # 第 0 个前缀（空串）归约为空栈
    where: dict[int, int] = {}  # (父亲 << 8 | 栈顶字符) 编码 -> 节点编号
    cur = 0

    for c in text:
        if nodes[cur] & 255 == c:  # 栈顶与 c 相同：恰好消除这一对
            cur = nodes[cur] >> 8  # 弹栈，回到父亲节点
        else:
            key = (cur << 8) | c  # 压栈，新状态 = 旧状态 + 栈顶 c
            nxt = where.get(key)
            if nxt is None:  # 这种栈内容第一次出现，分配新编号
                nxt = len(nodes)
                where[key] = nxt
                nodes.append(key)
                cnt.append(0)
            cur = nxt
        cnt[cur] += 1  # 第 i 个前缀的状态计数 +1

    # 子串 s[l..r] 可消除 <=> 第 l-1 个与第 r 个前缀状态相同，答案即同状态点对数
    print(sum(v * (v - 1) // 2 for v in cnt))


if __name__ == "__main__":
    solve()
