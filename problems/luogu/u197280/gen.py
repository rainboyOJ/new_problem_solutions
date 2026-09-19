#!/usr/bin/env python3
"""小数据生成器：两行大写字母串，长度很短，方便 brute.cpp 做 2^n 枚举。"""
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    # 字母表取小一点，让两个串有较多公共字符，能真正考验 LCS 逻辑
    alphabet = "ABCD"[: random.randint(2, 4)]
    n = random.randint(1, 14)
    m = random.randint(1, 14)

    x = "".join(random.choice(alphabet) for _ in range(n))
    y = "".join(random.choice(alphabet) for _ in range(m))

    print(x)
    print(y)


if __name__ == "__main__":
    main()
