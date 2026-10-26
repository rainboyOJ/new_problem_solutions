#!/usr/bin/env python3
"""生成 P2285 的对拍数据：规模用环境变量控制。

无参数运行，数据直接写 stdout，供 duipai.py --gen 调用。

    P2285_MAXN=<int>    网格边长 n 的上限（默认 6）
    P2285_MAXM=<int>    鼹鼠只数 m 的上限（默认 12，暴力 2^m 可承受）
    P2285_SLACK=<int>   时间槽冗余量（默认 2；越大时间越分散，越容易赶路）

题面要求 t 不降，且「同一时刻同一地点只出现一只」。生成器一边维护 last_t
保证 t 单调，一边用 (t, x, y) 去重；某个时刻的位置站满就自动推到下一个时刻。

手动运行示例：

    P2285_MAXN=1000 P2285_MAXM=10000 P2285_SLACK=100 python3 gen.py
"""

import os
import sys

from cyaron import IO, randint


def main():
    max_n = int(os.environ.get("P2285_MAXN", "6"))
    max_m = int(os.environ.get("P2285_MAXM", "12"))
    slack = int(os.environ.get("P2285_SLACK", "2"))

    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(1, max_n)
    m = randint(1, max_m)
    io.input_writeln(n, m)

    capacity = n * n  # 每个时刻最多容纳多少只不同位置的鼹鼠
    used = set()      # 已用掉的 (t, x, y)
    at_t = {}         # at_t[t]：时刻 t 已经放了几只
    last_t = 1

    for _ in range(m):
        # 时间整体前移，偶尔额外跳一格，模拟「同一时刻多只」与「时间分散」两种情形。
        t = last_t + randint(0, slack)
        while at_t.get(t, 0) >= capacity:  # 这个时刻站满了，推到下一时刻
            t += 1
        while True:
            x = randint(1, n)
            y = randint(1, n)
            if (t, x, y) not in used:
                break
        used.add((t, x, y))
        at_t[t] = at_t.get(t, 0) + 1
        last_t = t
        io.input_writeln(t, x, y)


if __name__ == "__main__":
    main()
