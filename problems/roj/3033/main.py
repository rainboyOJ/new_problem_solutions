#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:16
# update_at: 2026-10-04 12:28

import sys
from collections import deque
from collections.abc import Iterator

GROUP = -1  # member[x] 是 x 的小组下标；-1 表示该编号没有被任何小组收录


def run_case(data: Iterator[bytes], member: list[int], t: int) -> list[str]:
    """跑完一个测试用例，返回该用例要输出的所有行。"""
    # 两级队列：order 存「小组块」的先后，seats[g] 存小组 g 内部成员的先后。
    # 小组一旦进入 order 就不再重复入队，新人只追加到自己小组的 seats 里。
    order: deque[int] = deque()
    seats: list[deque[int]] = [deque() for _ in range(t)]
    out: list[str] = []

    while True:
        command = next(data)
        if command == b"STOP":
            return out

        if command == b"DEQUEUE":
            g = order[0]  # order 非空是题意保证：队列为空时不会要求出队
            out.append(str(seats[g].popleft()))
            if not seats[g]:  # 这个小组的最后一个人走了，小组才离开块序列
                order.popleft()
        else:
            x = int(next(data))
            g = member[x]
            if not seats[g]:  # 组内已经有人在排，新人才挨着自己的组员插队
                order.append(g)
            seats[g].append(x)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    scenario = 0

    while True:
        t = int(next(data))
        if t == 0:
            break

        # 人数可能为 0，小组描述会退化成孤零零一个数字，所以整份输入按 token 读
        member = [GROUP] * 1000000  # 编号域是 0~999999，直接下标寻址比 dict 快
        for g in range(t):
            size = int(next(data))
            ids = [int(next(data)) for _ in range(size)]
            for x in ids:
                member[x] = g

        scenario += 1
        out.append(f"Scenario #{scenario}")
        out += run_case(data, member, t)
        out.append("")  # 每个测试用例输出结束都补一个空行，含最后一个用例

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
