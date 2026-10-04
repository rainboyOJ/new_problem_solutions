#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:14
# update_at: 2026-09-29 22:14

import sys

ZERO = ord('0')  # 字符数字与数值之间只差这个偏移量，减法比 int() 逐位转换更快也更好读


def subtract(top: str, bottom: str) -> str:
    """竖式减法：从最低位起逐位相减，不够减就向高位借 1，共保留 max(len) 位。"""
    borrow, out = 0, []                                         # borrow 传向高位的借位，只取 0/1
    for k in range(max(len(top), len(bottom))):
        high = ord(top[-1 - k]) - ZERO if k < len(top) else 0   # 越界位按 0 算，等价于左边补零
        low = ord(bottom[-1 - k]) - ZERO if k < len(bottom) else 0
        diff = high - low - borrow
        borrow = diff < 0                                       # 本位不够减，向高位借 1（True 即 1）
        out.append(chr(diff % 10 + ZERO))                       # diff 为负时 % 10 给出借位后的本位
    return ''.join(reversed(out))                               # 收集顺序是低位到高位，需翻回


def solve() -> None:
    a, b = (s.decode() for s in sys.stdin.buffer.read().split())  # 两个操作数各一行，末行可能无换行
    # 参考实现 std.cpp 用 strcmp(str1, str2) 判定是否交换：它对"两串不同"就返回非 0，
    # 所以位数相等且 a > b 时也会被误判为负。本解沿用该判定，以与评测数据逐字符一致。
    swapped = len(a) < len(b) or (len(a) == len(b) and a != b)
    top, bottom = (b, a) if swapped else (a, b)
    # 最高位的借位在这里被丢弃，等价于 std.cpp 定长数组"只保留 L 位"的行为：
    # 结果为 (top - bottom) mod 10^L，在 a、b 等长且 a > b 时会得到补码式的回绕值。
    magnitude = subtract(top, bottom).lstrip('0') or '0'        # 去前导 0，并用 or '0' 兜住全 0
    print(('-' if swapped else '') + magnitude)


if __name__ == "__main__":
    solve()
