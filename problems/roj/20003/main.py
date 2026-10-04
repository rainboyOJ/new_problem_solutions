#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:18
# update_at: 2026-10-04 10:36

import sys
from functools import cmp_to_key


def bigger_first(a: str, b: str) -> int:
    """拼接比较器：a 放在 b 前拼出的数更大时返回负数，让 sort 产出最大拼接。"""
    ab, ba = a + b, b + a
    if ab > ba:
        return -1
    return 1 if ab < ba else 0


def solve() -> None:
    data = iter(sys.stdin.read().split())
    n = int(next(data))                    # 数字个数，n < 20
    nums = [next(data) for _ in range(n)]  # 保留字符串：拼接按位比较，转 int 反而丢掉顺序信息
    nums.sort(key=cmp_to_key(bigger_first))  # 比较器等价于键 x/(10^len-1) 降序，全序保证贪心最优
    print(''.join(nums))


if __name__ == "__main__":
    solve()
