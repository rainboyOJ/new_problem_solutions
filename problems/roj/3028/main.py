#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:03
# update_at: 2026-10-01 11:03

import sys

DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"  # 62 个数位，下标即权值
VALUE = {ch: v for v, ch in enumerate(DIGITS)}


def divide(digits: list[int], base: int, divisor: int) -> tuple[list[int], int]:
    """对源进制数位表做一次长除法，返回 (商的高位到低位, 余数)。

    手算长除法：把下落进位 rem 与当前位拼成 x = rem*base + a，商位取 x // divisor。
    rem < divisor ≤ 62 且 base ≤ 62，所以 x < 3900，C++ 里用 int 也不会溢出。
    """
    quotient: list[int] = []
    rem = 0
    for a in digits:
        x = rem * base + a
        digit = x // divisor
        if quotient or digit:  # 忽略前导零；商为空说明已经除尽
            quotient.append(digit)
        rem = x % divisor
    return quotient, rem


def convert(digits: list[int], base: int, target: int) -> str:
    """把源进制数位表写成目标进制字符串：反复除 target，余数就是低位到高位。"""
    out: list[str] = []
    while digits:
        digits, rem = divide(digits, base, target)
        out.append(DIGITS[rem])  # 余数必落在 [0, target)，正是目标进制的一位
    return "".join(reversed(out)) or "0"  # 商被除空说明原数是 0


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    out: list[str] = []
    T = int(data[0])
    for i in range(T):
        src, dst, raw = data[3 * i + 1 : 3 * i + 4]  # 第 i 组的三列
        src, dst = int(src), int(dst)
        digits = [VALUE[chr(ch)] for ch in raw]  # 输入数自己就是源进制的数位表
        out += [f"{src} {raw.decode()}", f"{dst} {convert(digits, src, dst)}", ""]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
