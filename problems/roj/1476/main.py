#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:10
# update_at: 2026-09-30 13:10

import sys

ONE = b'1'  # 按空白切分后，位 1 的字节串形态；与它比较把每个位映射成孩子下标 0/1

# 01-Trie 用三个平行列表存节点，编号从 0（根）开始：
# ch[v][t] 是节点 v 沿位 t 的孩子编号（0 表示不存在），end[v] 是恰好终止在 v 的信息条数，
# through[v] 是路径经过 v 的信息条数（终止在 v 的也算经过）。
Trie = tuple[list[list[int]], list[int], list[int]]


def build_trie(messages: list[list[bytes]]) -> Trie:
    """把全部截获信息依次插入 01-Trie，统计每个节点的终止数与经过数。"""
    ch: list[list[int]] = [[0, 0]]
    end: list[int] = [0]
    through: list[int] = [0]
    for bits in messages:
        v = 0
        for t in bits:
            t = t == ONE                      # 位即孩子下标：b'0'→0，b'1'→1
            if not ch[v][t]:                  # 孩子不存在则新建节点
                ch.append([0, 0])
                end.append(0)
                through.append(0)
                ch[v][t] = len(ch) - 1
            v = ch[v][t]
            through[v] += 1
        end[v] += 1
    return ch, end, through


def match_count(bits: list[bytes], trie: Trie) -> int:
    """统计能与这条密码匹配的信息条数：重合前缀长恰好等于 min(密码长, 信息长)。"""
    ch, end, through = trie
    v = 0
    ans = 0
    for t in bits:
        v = ch[v][t == ONE]
        if not v:                             # 这一位无路可走：更深处不可能再有信息，
            return ans                        # 能匹配的只有路径上恰好终止的那些
        ans += end[v]
    return ans + through[v] - end[v]          # 密码走完：补上比密码更长、经过终点的信息


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    p = 2
    messages: list[list[bytes]] = []
    for _ in range(n):
        msg_len = int(data[p])                # 题面的 b_i
        p += 1
        messages.append(data[p:p + msg_len])
        p += msg_len

    trie = build_trie(messages)
    out: list[str] = []
    for _ in range(m):
        code_len = int(data[p])               # 题面的 c_j
        p += 1
        out.append(str(match_count(data[p:p + code_len], trie)))
        p += code_len
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
