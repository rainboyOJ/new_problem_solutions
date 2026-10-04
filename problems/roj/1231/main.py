#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:43
# update_at: 2026-09-30 00:51

import sys
from collections.abc import Iterable


def smallest_after_deleting(digits: str, k: int) -> str:
    """删掉 digits 中的 k 位（保持原有顺序），返回能得到的最小数字串。

    单调栈：按输出位从左往右定，每位取当前窗口里最靠左的最小值。扫到 digit 时，
    栈顶比它大就说明栈顶占着的槽位应该让给它（把更小的数位提到前面只会更小），
    弹出栈顶即花掉一次删除额度；弹不动了再压栈，于是栈内始终非降。
    每个数位最多进出栈各一次。
    """
    stack: list[str] = []
    for digit in digits:
        while k and stack and stack[-1] > digit:  # 严格大于：相等时保留更靠左的那位
            stack.pop()
            k -= 1
        stack.append(digit)
    return ''.join(stack[:len(stack) - k])  # 额度没用完说明栈已非降，剩余删除只能砍末尾


def solve() -> None:
    """逐组读入 n 与 k，输出删除 k 位后最小的新整数。"""
    data: Iterable[bytes] = iter(sys.stdin.buffer.read().split())
    cases = int(next(data))
    out: list[str] = []
    for _ in range(cases):
        digits, k = next(data).decode(), int(next(data))  # n 保持字符串，转 int 会丢位数
        out.append(smallest_after_deleting(digits, k))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
