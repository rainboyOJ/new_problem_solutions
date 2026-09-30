#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:20
# update_at: 2026-10-01 04:20

import sys

MAX_RUNAROUND = 9682415  # 位数递增时循环数总数为 9+20+12+48+160+96+112，7 位以上为空


def is_runaround(n: int) -> bool:
    """n 的十进制各位非零且互不相同，且从第 0 位起按"当前位数字"跳格恰好走遍所有位并回到 0。"""
    s = str(n)
    if '0' in s or len(set(s)) != len(s):  # 含 0 或数字重复，直接排除
        return False
    length = len(s)
    pos, visited = 0, 0
    for _ in range(length):
        if visited >> pos & 1:  # 同一位置踩两次：说明跳格没覆盖全部位，绕不到起点
            return False
        visited |= 1 << pos
        pos = (pos + int(s[pos])) % length  # 向右数 s[pos] 格，越界则回卷
    return pos == 0  # 恰好走完 length 步后回到起点


def solve() -> None:
    m = int(sys.stdin.buffer.read())
    n = m + 1
    while n <= MAX_RUNAROUND and not is_runaround(n):  # 超过上界就不存在更大的循环数
        n += 1
    print(n)


if __name__ == "__main__":
    solve()
