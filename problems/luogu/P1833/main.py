#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 13:30
# update_at: 2026-10-26 14:12

import sys
def parse_time(value: bytes) -> int:
    """把 hh:mm 时间转换为从 0:00 起算的分钟数。"""
    hour, minute = map(int, value.split(b":"))
    return hour * 60 + minute


def apply_bounded_item(dp: list[int], limit_time: int, tree_time: int, beauty: int, count_limit: int) -> list[int]:
    """二进制拆分有限次数物品，并逐组进行倒序 0/1 背包。"""
    group_size = 1
    while count_limit > 0:
        use_count = min(group_size, count_limit)
        group_time = use_count * tree_time
        group_beauty = use_count * beauty

        if group_time <= limit_time:
            old_dp = dp
            dp = old_dp[:group_time] + [
                candidate if candidate > old_dp[capacity] else old_dp[capacity]
                for capacity in range(group_time, limit_time + 1)
                for candidate in (old_dp[capacity - group_time] + group_beauty,)
            ]

        count_limit -= use_count
        group_size <<= 1

    return dp


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    start_time = parse_time(next(data))
    end_time = parse_time(next(data))
    n = int(next(data))
    limit_time = end_time - start_time
    dp = [0] * (limit_time + 1)

    for _ in range(n):
        tree_time = int(next(data))
        beauty = int(next(data))
        count_limit = int(next(data))

        if count_limit == 0:
            # 正序让当前树的新状态继续参与转移，实现无限次选择。
            for capacity in range(tree_time, limit_time + 1):
                candidate = dp[capacity - tree_time] + beauty
                if candidate > dp[capacity]:
                    dp[capacity] = candidate
        else:
            dp = apply_bounded_item(dp, limit_time, tree_time, beauty, count_limit)

    print(dp[limit_time])


if __name__ == "__main__":
    solve()
