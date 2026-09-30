#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:51
# update_at: 2026-09-30 18:54

import sys

X_MIN = -100_000  # 存储值 x = 实际工资 - bias 的理论下界：k ≥ 0、bias ≤ 1e5
X_MAX = 200_000  # 理论上界：k ≤ 1e5、bias ≥ -1e5
POS_SIZE = X_MAX - X_MIN + 2  # 树状数组下标 1..POS_SIZE-1，比值域多留 1 位

TREE = [0] * POS_SIZE  # 树状数组：按存储值 x 的名次统计人数


def update(pos: int, delta: int) -> None:
    """树状数组第 pos 个下标增减 delta 人（pos 从 1 开始）。"""
    while pos < POS_SIZE:
        TREE[pos] += delta
        pos += pos & -pos


def kth(rank: int) -> int:
    """最小的下标 pos，使前缀人数 ≥ rank；rank 从 1 开始，即第 rank 小。"""
    pos = 0
    step = 1 << (POS_SIZE.bit_length() - 1)  # 不小于 POS_SIZE 的最高 2 次幂
    while step:
        nxt = pos + step
        if nxt < POS_SIZE and TREE[nxt] < rank:
            pos = nxt
            rank -= TREE[nxt]
        step >>= 1
    return pos + 1


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # 命令条数
    floor = int(next(data))  # 工资下界 min

    cnt: dict[int, int] = {}  # 每个存储值 x 当前的人数
    staff = 0  # 在职人数，等于树状数组总和
    bias = 0  # 全局偏移：实际工资 = 存储值 x + bias，A/S 只改它
    leave = 0  # 因扣薪低于下界离开的人数（不含入职即低于下界者）
    out: list[str] = []

    for _ in range(n):
        cmd = next(data)
        k = int(next(data))

        if cmd == b'I':
            # 入职即低于下界的直接走人：不建档也不计入离开总数
            if k >= floor:
                x = k - bias  # 存储值，保证不变量：所有在职 x ≥ floor - bias
                cnt[x] = cnt.get(x, 0) + 1
                staff += 1
                update(x - X_MIN + 1, 1)

        elif cmd == b'A':
            bias += k  # 全员加薪：只抬偏移，无人低于下界

        elif cmd == b'S':
            bias -= k
            # 下界阈值 t = floor - bias 随扣薪恰好抬高 k；由不变量只需扫描 [t-k, t)
            hi = floor - bias
            for x in range(max(hi - k, X_MIN), min(hi, X_MAX + 1)):
                gone = cnt.pop(x, 0)  # 区间内不在职的值弹出为 0，不影响结果
                if gone:
                    staff -= gone
                    leave += gone
                    update(x - X_MIN + 1, -gone)

        else:  # F k：第 k 大的工资，等价于第 staff-k+1 小的存储值
            if k > staff:
                out.append("-1")
            else:
                x = kth(staff - k + 1) - 1 + X_MIN  # 名次二分回存储值
                out.append(str(x + bias))  # 平移回实际工资

    out.append(str(leave))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
