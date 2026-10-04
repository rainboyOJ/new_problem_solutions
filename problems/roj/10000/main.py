#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:20
# update_at: 2026-10-02 17:20

import sys

EMPTY = "(Null)"  # 某一部分为空时的占位输出


def solve() -> None:
    # 题面保证密码不含空格等空白字符，第一个 token 就是整个字符串
    data = iter(sys.stdin.buffer.read().split())
    s = next(data).decode()

    # 四部分按题面顺序分桶；逐字符 append，桶内自然保持原串的相对顺序
    lower: list[str] = []
    upper: list[str] = []
    digit: list[str] = []
    other: list[str] = []
    for ch in s:
        if "a" <= ch <= "z":
            lower.append(ch)     # 第一部分：小写英文字母
        elif "A" <= ch <= "Z":
            upper.append(ch)     # 第二部分：大写英文字母
        elif "0" <= ch <= "9":
            digit.append(ch)     # 第三部分：数字
        else:
            other.append(ch)     # 第四部分：其余特殊字符

    parts = (lower, upper, digit, other)
    level = sum(map(bool, parts))  # 每个非空部分让密码等级 +1
    out = [f"password level:{level}"]
    out += ["".join(part) if part else EMPTY for part in parts]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
