#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:10
# update_at: 2026-10-02 12:14

import sys
from collections import deque
from collections.abc import Iterator

WINDOW = 86400  # 统计窗口：船到达时刻往前 24 小时 = 86400 秒


def read_ships(lines: Iterator[bytes]) -> Iterator[tuple[int, list[int]]]:
    """从标准输入的行流里依次产出 (到达时间, 国籍列表)，逐行读入、不整份驻留内存。

    每行前两个数是到达时间 t 和乘客数 k，其后恰好 k 个国籍。
    """
    n = int(next(lines))
    for _ in range(n):
        t, k, *nats = map(int, next(lines).split())  # k 只用于占位，国籍个数由行本身给出
        yield t, nats


def window_answers(ships: Iterator[tuple[int, list[int]]]) -> Iterator[int]:
    """依次产出每艘船到达后，窗口 (t-86400, t] 内的不同国籍数。

    船按到达时间递增，退出窗口的船只会出现在队首，整船出窗即可；
    计数归零的国籍立即删键，len(counter) 才恒等于窗口内的国籍数。
    """
    window: deque[tuple[int, list[int]]] = deque()  # 窗口内的船 (到达时间, 国籍列表)
    counter: dict[int, int] = {}                    # 窗口内每个国籍的人数
    for t, nats in ships:
        window.append((t, nats))
        for x in nats:
            counter[x] = counter.get(x, 0) + 1

        expire_before = t - WINDOW  # 早于该时刻到达的船已滑出 24 小时窗口
        while window[0][0] <= expire_before:
            _, old = window.popleft()
            for x in old:
                if counter[x] == 1:
                    del counter[x]  # 该国籍在窗口内只剩这一个人，随船一起消失
                else:
                    counter[x] -= 1

        yield len(counter)


def solve() -> None:
    ships = read_ships(sys.stdin.buffer)
    write = sys.stdout.buffer.write
    for answer in window_answers(ships):
        write(f"{answer}\n".encode())  # 逐行输出，不攒整份答案字符串


if __name__ == "__main__":
    solve()
