#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    # 暴力是对「涂色过程」做状态搜索，只能跑很短的串，所以长度限制在 1..7。
    # 轮换几种字母表，兼顾「大量重复字符」和「几乎全不同字符」两类极端。
    n = random.randint(1, 7)
    alphabet = random.choice(["A", "AB", "ABC"])
    print("".join(random.choice(alphabet) for _ in range(n)))


if __name__ == "__main__":
    main()
