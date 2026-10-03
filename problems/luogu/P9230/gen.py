#!/usr/bin/env python3
"""P9230 数据生成器：输入只有一个字符，代表题目编号（A 或 B）。

题面是填空问题，合法输入只有 "A" 和 "B" 两种，所以生成器的任务就是让对拍
覆盖到这两条完全不同的分支。做法是：

* 随机种子固定（SEED），保证同一台机器、同一次数下的随机序列可复现；
* 用 /tmp 里的一个计数器在连续运行之间交替输出 A / B，
  这样对拍循环里的若干次运行会同时覆盖 A 题和 B 题，
  而不是每次都生成同一个字符；
* 也支持 `python3 gen.py A` / `python3 gen.py B` 手工指定边界用例。
"""
import os
import random
import sys

SEED = 20231002          # 固定随机种子，保证随机部分可复现
COUNTER_PATH = "/tmp/P9230-gen-count"


def next_counter() -> int:
    """读取并递增运行计数器，让连续运行生成不同的题目编号。"""
    value = 0
    try:
        with open(COUNTER_PATH, "r", encoding="utf-8") as fin:
            value = int(fin.read().strip() or "0")
    except (OSError, ValueError):
        value = 0
    try:
        with open(COUNTER_PATH, "w", encoding="utf-8") as fout:
            fout.write(str(value + 1))
    except OSError:
        pass
    return value


def main():
    random.seed(SEED)
    random.random()  # 保留一次随机调用，随机种子仍然参与决定序列起点

    if len(sys.argv) > 1 and sys.argv[1].strip().upper() in ("A", "B"):
        print(sys.argv[1].strip().upper())
        return

    run_index = next_counter()
    if run_index % 2 == 0:
        print("A")
    else:
        print("B")


if __name__ == "__main__":
    main()
