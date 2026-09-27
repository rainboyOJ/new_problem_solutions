#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else random.randrange(1 << 30)
    random.seed(seed)

    n = random.randint(1, 8)
    # 时间范围刻意取小一点，制造大量区间重叠，容易覆盖边界
    max_t = random.randint(1, 10)

    print(n)
    for _ in range(n):
        a = random.randint(1, max_t)
        b = random.randint(a, max_t)
        print(a, b)


if __name__ == "__main__":
    main()
