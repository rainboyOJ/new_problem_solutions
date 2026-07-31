#!/usr/bin/env python3
"""CSP201403B 的小规模窗口与点击随机生成器。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    window_count = random.randint(1, 10)
    click_count = random.randint(1, 10)
    print(window_count, click_count)
    for _ in range(window_count):
        left = random.randint(0, 20)
        bottom = random.randint(0, 20)
        right = random.randint(left + 1, 30)
        top = random.randint(bottom + 1, 30)
        print(left, bottom, right, top)
    for _ in range(click_count):
        print(random.randint(0, 30), random.randint(0, 30))


if __name__ == "__main__":
    main()
