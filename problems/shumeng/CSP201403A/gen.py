#!/usr/bin/env python3
"""CSP201403A 的不同非零整数随机生成器。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    count = random.randint(1, 80)
    values = random.sample([x for x in range(-1000, 1001) if x != 0], count)
    print(count)
    print(*values)


if __name__ == "__main__":
    main()
