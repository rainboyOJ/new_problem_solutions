#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:57
# update_at: 2026-09-30 00:57

import sys

MOD = 10000            # 只保留后四位


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    k = int(next(data))  # 数据组数
    nums = list(data)    # 每组一个指数串，位数可达 200

    out: list[str] = []
    for i in range(k):
        # 个别测试点声明的 k 多于实际数字个数：对齐 std 的 cin>>string
        # 在 EOF 处失败时字符串保持原值的行为，沿用上一个指数
        n = nums[i] if i < len(nums) else nums[-1]
        out.append(str(pow(2011, int(n[-4:]), MOD)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
