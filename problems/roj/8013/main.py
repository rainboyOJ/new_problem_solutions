#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:37
# update_at: 2026-10-02 16:37

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    day_count = int(next(data))             # 记账天数 n
    debt = {who: 0 for who in "DGZ"}        # 净额桶：正 = 欠别人几顿，负 = 借给别人几顿

    for _ in range(day_count):              # 每天一条记录：欠账人 欠给 被欠人
        debtor, creditor = next(data).decode(), next(data).decode()
        debt[debtor] += 1                   # 欠账人净额 +1（欠了别人一顿）
        debt[creditor] -= 1                 # 被欠人净额 -1（借给别人一顿）

    # 固定按 D G Z 三行输出，桶里没有出现过的人保持 0
    print("\n".join(f"{who} {debt[who]}" for who in "DGZ"))


if __name__ == "__main__":
    solve()
