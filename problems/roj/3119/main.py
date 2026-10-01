#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:17
# update_at: 2026-10-01 18:23

import sys
from bisect import bisect_left, bisect_right


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    ops: list[tuple[int, int]] = [
        (next(data), next(data)) for _ in range(n)
    ]  # 全部操作先存下来，方便离线压缩坐标

    # 离线坐标：所有可能出现过的数值。操作 4 的 x 是排名而不是数值，必须排除，
    # 否则小排名会被塞进坐标表，污染“排名为 k 的数值”的答案。
    coords: list[int] = sorted({x for opt, x in ops if opt != 4})
    tree: list[int] = [0] * (len(coords) + 1)  # 树状数组，1-based：tree[i] 维护坐标 [i-lowbit(i), i-1]

    def add(pos: int, delta: int) -> None:
        """把坐标 pos（0-based）上的出现次数改变 delta。"""
        i = pos + 1
        while i < len(tree):
            tree[i] += delta
            i += i & -i  # 跳到下一个覆盖该点的位置（加上最低位的 1）

    def count_below(pos: int) -> int:
        """统计下标严格小于 pos 的坐标上已有的元素总数，pos 是坐标下标。"""
        total = 0
        while pos:
            total += tree[pos]
            pos -= pos & -pos  # 抹掉最低位的 1，跳到上一层区间
        return total

    def value_at(rank: int) -> int:
        """返回第 rank 小（1-based）的数值；数据保证该排名一定存在，无需判空。"""
        i = 0  # 已经走过的前缀长度（也是 1-based 坐标）
        step = 1 << (len(tree).bit_length() - 1)  # 最大不超过 tree 长度的 2 的幂
        while step:
            nxt = i + step
            if nxt < len(tree) and tree[nxt] < rank:
                i = nxt  # tree[nxt] 恰好是这一段区间的计数和，可以整段跳过
                rank -= tree[nxt]
            step >>= 1
        # 退出时 i 是最后一个前缀计数仍小于 rank 的坐标，加 1 才是答案坐标；
        # 因为 i 初值为 0，coords[i] 恰好就是 0-based 的答案下标。
        return coords[i]

    out: list[str] = []
    for opt, x in ops:
        if opt == 1:
            add(bisect_left(coords, x), 1)
        elif opt == 2:
            add(bisect_left(coords, x), -1)
        elif opt == 3:  # 排名 = 严格小于 x 的个数 + 1
            out.append(str(count_below(bisect_left(coords, x)) + 1))
        elif opt == 4:  # 第 x 小的数值
            out.append(str(value_at(x)))
        elif opt == 5:  # 前驱：严格小于 x 的个数，就是前驱的排名
            out.append(str(value_at(count_below(bisect_left(coords, x)))))
        else:  # 后继：小于等于 x 的个数加一，就是后继的排名
            out.append(str(value_at(count_below(bisect_right(coords, x)) + 1)))

    sys.stdout.write("\n".join(out) + ("\n" if out else ""))  # 全是插入/删除时没有任何输出，不写裸换行


if __name__ == "__main__":
    solve()
