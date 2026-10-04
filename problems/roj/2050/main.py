#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:07
# update_at: 2026-10-01 05:13

import sys
from collections import deque

# 状态统一用"顺时针取出的 8 个数字"表示：前 4 位是上行（按从左到右读，序列上却是从右往左），
# 后 4 位是下行（从左到右）。基本状态就是这个序列的字典序最小值 (1,2,3,4,5,6,7,8)。
IDENTITY = (1, 2, 3, 4, 5, 6, 7, 8)


def apply_a(state: tuple[int, ...]) -> tuple[int, ...]:
    """操作 A：交换上下两行，两行各自还需要左右翻转一次才符合顺时针读法。"""
    return state[4:][::-1] + state[:4][::-1]


def apply_b(state: tuple[int, ...]) -> tuple[int, ...]:
    """操作 B：每行循环右移一位（最右一列插入最左）。"""
    return (state[3],) + state[:3] + state[5:] + (state[4],)


def apply_c(state: tuple[int, ...]) -> tuple[int, ...]:
    """操作 C：中央四格顺时针旋转，只有序列下标 1、2、5、6 四个位置参与。"""
    return (state[0], state[6], state[1], state[3], state[4], state[2], state[5], state[7])


# 枚举顺序就是题目要求的字典序：A < B < C。BFS 逐层扩展，层内队列按路径字典序出队，
# 所以每个状态第一次被写入 parent 时，拿到的既是最近距离，也是同距离里字典序最小的路径。
OPS = (("A", apply_a), ("B", apply_b), ("C", apply_c))


def shortest_ops(target: tuple[int, ...]) -> str:
    """从基本状态出发 BFS，返回到达 target 的最短且字典序最小的操作序列。"""
    if target == IDENTITY:  # 不用动一步，直接返回，省掉一次完整 BFS
        return ""

    parent: dict[tuple[int, ...], tuple[tuple[int, ...], str] | None] = {IDENTITY: None}
    queue = deque([IDENTITY])

    while queue:
        state = queue.popleft()
        for name, op in OPS:
            nxt = op(state)
            if nxt in parent:  # 已经用更短或字典序更小的路径到达过
                continue
            parent[nxt] = (state, name)
            if nxt == target:  # 第一次生成即最优，可以立刻回溯
                steps: list[str] = []
                cur = nxt
                while parent[cur] is not None:
                    prev, op_name = parent[cur]
                    steps.append(op_name)
                    cur = prev
                return "".join(reversed(steps))
            queue.append(nxt)

    return ""  # 走不到这里：8! 个状态全部可达，目标一定会被生成


def solve() -> None:
    target = tuple(map(int, sys.stdin.buffer.read().split()))
    ops = shortest_ops(target)

    print(len(ops))
    # 题面要求除最后一行外每行 60 个字符，按 60 切块输出。
    print("\n".join(ops[i : i + 60] for i in range(0, len(ops), 60)))


if __name__ == "__main__":
    solve()
