#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(0, 30)
    m = random.randint(0, 30)
    values = list(range(1, 200))
    random.shuffle(values)
    a = values[:n]
    b = values[n:n + m]

    # 随机把一部分 a 中的数放进 b，保证有交集和无交集情况都能出现。
    for x in a:
        if m > 0 and random.random() < 0.35:
            b[random.randrange(m)] = x

    # 保证第二行内部不重复。
    seen = set()
    fixed_b = []
    pool = [x for x in range(1, 300) if x not in seen]
    for x in b:
        if x in seen:
            y = random.choice([v for v in pool if v not in seen])
            x = y
        seen.add(x)
        fixed_b.append(x)
    b = fixed_b

    print(n, m)
    print(" ".join(map(str, a)))
    print(" ".join(map(str, b)))


if __name__ == "__main__":
    main()
