#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:44
# update_at: 2026-09-30 05:44

import sys
from collections.abc import Iterator
from itertools import cycle, islice


def dance_lines(men_count: int, women_count: int, dances: int) -> Iterator[str]:
    """产出前 dances 支舞曲的配对行「男生号 女生号」。

    队头出队、同一个人再排回队尾，在编号上就是 1, 2, ..., 人数, 1, 2, ...
    无限循环；两支队伍的出队序列各是一个 cycle，逐支舞曲并排配对即可。
    """
    men = cycle(range(1, men_count + 1))      # 男队队头序列
    women = cycle(range(1, women_count + 1))  # 女队队头序列
    return islice(map('{} {}'.format, men, women), dances)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    men_count, women_count = next(data), next(data)
    dances = next(data)  # 舞曲数目
    sys.stdout.write('\n'.join(dance_lines(men_count, women_count, dances)) + '\n')


if __name__ == "__main__":
    solve()
