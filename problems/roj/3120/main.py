#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 12:40
# update_at: 2026-10-09 12:40

import sys

MAX_VAL = 1000005   # 坐标 +1 后最大 1000001，树状数组下标留一点余量
MIRROR = 1000002    # 坐标轴翻转常数，须大于最大坐标 10^6
NEG = -0x3F3F3F3F   # 树状数组空位哨兵（真实 x+y >= 2）
INF = 0x3F3F3F3F    # 询问答案初值

type Ops = list[tuple[int, int, int]]  # (id, x, y)，id=0 是插入点，>0 是第 id 个询问

ops: Ops = []        # CDQ 当前处理的序列，时间维就是它的下标顺序
tmp: Ops = []        # 归并时的临时数组
orig_ops: Ops = []   # 原始时间序，每遍翻转后从它重新生成 ops
bit: list[int] = []  # 树状数组：y <= 当前 y 的点里最大的 x + y
ans: list[int] = []  # ans[i] = 第 i 个询问当前的最近曼哈顿距离


def bit_update(i: int, val: int) -> None:
    """把 val 插入树状数组位置 i（维护最大值）。"""
    while i <= MAX_VAL:
        if val > bit[i]:
            bit[i] = val
        i += i & -i


def bit_query(i: int) -> int:
    """询问前缀 [1, i] 的最大值，全空返回 NEG。"""
    mx = NEG
    while i > 0:
        if bit[i] > mx:
            mx = bit[i]
        i -= i & -i
    return mx


def bit_reset(i: int) -> None:
    """撤销一次插入。走到 bit[i] 已经是空位即可停：更高层祖先必然也被清过了。"""
    while i <= MAX_VAL:
        if bit[i] == NEG:
            break
        bit[i] = NEG
        i += i & -i


def relax(op: tuple[int, int, int]) -> None:
    """用已插入的左下方点更新询问答案：距离 = (xq + yq) - max(xi + yi)。"""
    best = bit_query(op[2])
    if best != NEG:
        cand = op[1] + op[2] - best
        if cand < ans[op[0]]:
            ans[op[0]] = cand


def cdq(left: int, right: int) -> None:
    """CDQ 分治 ops[left..right]：时间维靠下标顺序，x 维靠归并，y 维靠树状数组。"""
    if left >= right:
        return
    mid = left + (right - left) // 2
    cdq(left, mid)
    cdq(mid + 1, right)

    i = left
    j = mid + 1
    k = left
    while i <= mid and j <= right:
        if ops[i][1] <= ops[j][1]:
            if ops[i][0] == 0:  # 左半边的插入点对右半边后续询问可见
                bit_update(ops[i][2], ops[i][1] + ops[i][2])
            tmp[k] = ops[i]
            i += 1
        else:
            if ops[j][0] > 0:
                relax(ops[j])
            tmp[k] = ops[j]
            j += 1
        k += 1

    while j <= right:
        if ops[j][0] > 0:
            relax(ops[j])
        tmp[k] = ops[j]
        j += 1
        k += 1

    # 左半边参与合并的插入点已经用完，回滚它们写进树状数组的位置
    for p in range(left, i):
        if ops[p][0] == 0:
            bit_reset(ops[p][2])

    while i <= mid:
        tmp[k] = ops[i]
        i += 1
        k += 1

    for p in range(left, right + 1):
        ops[p] = tmp[p]


def run_pass(flip_x: bool, flip_y: bool) -> None:
    """按 (flip_x, flip_y) 翻转坐标后跑一遍 CDQ，覆盖曼哈顿距离的四个象限。"""
    for i, op in enumerate(orig_ops):
        x = MIRROR - op[1] if flip_x else op[1]
        y = MIRROR - op[2] if flip_y else op[2]
        ops[i] = (op[0], x, y)
    cdq(0, len(ops) - 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
        m = next(data)
    except StopIteration:
        return

    # 初始的 n 个点看作最早发出的 n 次插入，与 m 次操作合并成一条时间序
    for _ in range(n):
        x = next(data) + 1  # 坐标 +1，避免树状数组下标为 0
        y = next(data) + 1
        orig_ops.append((0, x, y))

    q_cnt = 0
    for _ in range(m):
        t = next(data)
        x = next(data) + 1
        y = next(data) + 1
        if t == 1:
            orig_ops.append((0, x, y))
        else:
            q_cnt += 1
            orig_ops.append((q_cnt, x, y))

    ops.extend([(0, 0, 0)] * len(orig_ops))
    tmp.extend([(0, 0, 0)] * len(orig_ops))
    ans.extend([INF] * (q_cnt + 1))
    bit.extend([NEG] * (MAX_VAL + 5))

    run_pass(False, False)  # 左下象限
    run_pass(True, False)   # 右下象限
    run_pass(False, True)   # 左上象限
    run_pass(True, True)    # 右上象限

    sys.stdout.write('\n'.join(map(str, ans[1:])) + '\n' if q_cnt else '')


if __name__ == '__main__':
    solve()
