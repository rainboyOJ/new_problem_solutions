#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:08
# update_at: 2026-10-09 01:12

import sys

# 下标 0 占位空串；下标 1..7 依次是 Monday..Sunday（首字母大写，拼写逐字对齐题面）
WEEK_NAME = (
    "", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
)


def solve() -> None:
    """读入表示星期几的数字，落在闭区间 [1, 7] 输出英文名，否则输出 input error!。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)  # 无输入：None，静默退出，与 C++ 侧 cin 读取失败的行为一致
    if n is None:
        return
    if 1 <= n <= 7:
        name = WEEK_NAME[n]
    else:
        # 必须先判后查：Python 的负下标会从尾部取值，n = -1 直接查表会误得 Sunday
        name = "input error!"  # 题面要求的提示：全小写 + 感叹号
    print(name)


if __name__ == "__main__":
    solve()
