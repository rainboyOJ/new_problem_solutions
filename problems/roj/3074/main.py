#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:45
# update_at: 2026-10-01 14:57

import sys
from operator import itemgetter

# 棋盘按“从上到下、同行从左到右”编号 0~23；每个操作是一条 7 格首尾相接的环，
# 顺箭头方向滚动一格，即环上每个位置改取它的后继格（末格取首格）。下表就是这 8 条环。
LINE = (
    (0, 2, 6, 11, 15, 20, 22),     # A 最左列自上而下
    (1, 3, 8, 12, 17, 21, 23),     # B 第二列自上而下
    (10, 9, 8, 7, 6, 5, 4),        # C 最下行自右向左
    (19, 18, 17, 16, 15, 14, 13),  # D 最右列自下而上
    (23, 21, 17, 12, 8, 3, 1),     # E 是 B 的反向
    (22, 20, 15, 11, 6, 2, 0),     # F 是 A 的反向
    (13, 14, 15, 16, 17, 18, 19),  # G 是 D 的反向
    (4, 5, 6, 7, 8, 9, 10),        # H 是 C 的反向
)
CENTER = (6, 7, 8, 11, 12, 15, 16, 17)  # 中央 8 格
BACK = (5, 4, 7, 6, 1, 0, 3, 2)         # A↔F、B↔E、C↔H、D↔G，撤销一步就是走它的反向
INF = 10 ** 9

# ROTATE[k][i] = 走完操作 k 之后，格子 i 上的数字来自哪个格子；环外的格子原地不动。
# 把“新状态该取哪些旧格子”压成 8 张 24 位取数表，热循环里一次调用即完成整盘滚动。
ROTATE = []
for line in LINE:
    source = list(range(24))  # 默认每个格子取自己
    for j in range(7):
        source[line[j]] = line[(j + 1) % 7]  # 环上第 j 格改取它的后继，末格取首格
    ROTATE.append(itemgetter(*source))
ROTATE = tuple(ROTATE)
CENTER_OF = itemgetter(*CENTER)


def lower_bound(state: tuple[int, ...]) -> int:
    """中央 8 格最少还要几步才同色。

    每条笔画与中央 8 格的交恰是该笔画里下标 2、3、4 的三个连续格，滚动一格只换掉 1 格，
    所以众数的个数每步至多 +1，即“非众数格数”每步至多 -1，它就是可采纳下界。
    """
    center = CENTER_OF(state)
    return 8 - max(center.count(1), center.count(2), center.count(3))


def solve_case(start: tuple[int, ...]) -> tuple[str, int]:
    """IDA*：先定步数上限，再按 A~H 字典序深搜，首个命中即为最短且字典序最小的解。"""
    bound = lower_bound(start)
    while True:
        path: list[int] = []
        proved: dict[tuple[int, ...], int] = {}  # 本轮已证下界：不同顺序到达同一状态（转置）时复用

        def search(state: tuple[int, ...], g: int, bad: int) -> int:
            """上限 bound 内深搜：找到目标返回 -1，否则返回后继中最小的 f=g+h。"""
            real = lower_bound(state)
            known = proved.get(state, 0)  # 取启发式与已证下界的较大者，剪枝更强但仍可采纳
            h = real if real > known else known
            if g + h > bound:
                return g + h
            if real == 0:
                return -1
            best = INF
            for k in range(8):
                if k == bad:  # 一步一撤销只是原路返回，最短解里不会出现
                    continue
                path.append(k)
                got = search(ROTATE[k](state), g + 1, BACK[k])
                if got == -1:
                    return -1
                path.pop()
                if got < best:
                    best = got
            need = bound - g + 1  # 本状态在上限内走不到目标，说明它还差至少这么多步
            if need > proved.get(state, 0):
                proved[state] = need
            return best

        if search(start, 0, -1) == -1:  # 首个成功的上限就是最短步数
            state = start
            for k in path:
                state = ROTATE[k](state)
            return ''.join(chr(65 + k) for k in path), CENTER_OF(state)[0]
        bound += 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for first in data:
        if first == 0:  # 单独一个 0 表示输入结束
            break
        start = (first, *(next(data) for _ in range(23)))
        moves, color = solve_case(start)
        out.append(moves if moves else 'No moves needed')
        out.append(str(color))
    print('\n'.join(out))


if __name__ == '__main__':
    solve()
