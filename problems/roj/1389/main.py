#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:29
# update_at: 2026-09-30 08:29

import sys


def find(father: list[int], x: int) -> int:
    """求 x 所在家族的根，并把路径上的点全部直接挂到根上（路径压缩）。"""
    root = x
    while father[root] != root:  # 第一趟：顺着父亲指针走到根
        root = father[root]
    while father[x] != root:     # 第二趟回溯：整条路径一次改挂到根
        father[x], x = root, father[x]
    return root


def solve() -> None:
    """M a b 合并两个家族，Q a 输出 a 所在家族的人数。"""
    tokens = sys.stdin.buffer.read().split()
    cursor = 0  # tokens 的读取位置，等价于 C 里 scanf 的流游标

    def scanf_int(keep: int) -> int:
        """模拟 scanf("%d")：读到整数就消费返回；匹配失败时不消费 token，变量保持原值 keep。"""
        nonlocal cursor
        token = tokens[cursor] if cursor < len(tokens) else b""
        if token.isdigit():
            cursor += 1
            return int(token)
        return keep

    n, m = scanf_int(0), scanf_int(0)
    father = list(range(n + 1))
    cnt = [0] + [1] * n  # cnt[r] = 根 r 所在家族的人数；cnt[0] = 0 对应 std 全局数组的零初始化

    out: list[str] = []
    a = b = 0  # C 局部变量首次读取前的栈上旧值用 0 占位，正常数据用不到
    for _ in range(m):
        op = tokens[cursor]
        cursor += 1  # scanf("%s") 无论内容是什么都消费一个 token 当操作符
        if op == b"M":
            a, b = scanf_int(a), scanf_int(b)
            ra, rb = find(father, a), find(father, b)
            if ra != rb:  # 按大小合并：小家族整棵挂到大家族的根下
                if cnt[ra] < cnt[rb]:
                    ra, rb = rb, ra
                father[rb] = ra
                cnt[ra] += cnt[rb]
        elif op == b"Q":
            a = scanf_int(a)
            out.append(str(cnt[find(father, a)]))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
