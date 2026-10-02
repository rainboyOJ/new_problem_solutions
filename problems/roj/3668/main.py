#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:43
# update_at: 2026-10-02 14:59

import sys

LIMIT = 12_000_000  # x ≤ 1e7，下一个合法数可能略超 1e7，多留余量

# banned[i] = 1 当且仅当 i 不能报出。
# 第一步：i 的十进制含数字 7 —— 按「第 place 位是 7」逐位打区间标记，
# 第 place 位为 7 的数恰好是 [base + 7*place, base + 8*place)，base 每 10*place 一轮。
banned = bytearray(LIMIT + 1)
place = 1
while place <= LIMIT:
    step = 10 * place
    for base in range(0, LIMIT + 1, step):
        lo = base + 7 * place
        if lo > LIMIT:
            break
        hi = min(base + 8 * place, LIMIT + 1)
        banned[lo:hi] = b'\x01' * (hi - lo)
    place *= 10

# 第二步：从小到大找出每个含 7 的 y，把 y 的所有倍数也标成禁报。
# 从小往大扫保证标 y 的倍数时，含 7 的更小因子早已处理过，不会漏。
pos = 0
while (pos := banned.find(1, pos + 1)) != -1:
    banned[pos::pos] = b'\x01' * (LIMIT // pos)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    T = int(next(data))
    out: list[str] = []
    for _ in range(T):
        x = int(next(data))
        # x 合法时，下一个合法数就是 banned 里 x 之后第一个 0 字节（C 速度的扫描）
        nxt = banned.find(0, x + 1)
        out.append(str(-1 if banned[x] else nxt))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
