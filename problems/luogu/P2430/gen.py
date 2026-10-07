#!/usr/bin/env python3
import random


def main():
    random.seed()

    wky_skill = random.randint(1, 5)
    ratio = random.randint(2, 5)
    wang_skill = wky_skill * ratio

    m = random.randint(1, 16)
    n = random.randint(1, 6)
    topic_time = [random.randint(1, 10) for _ in range(n)]

    problems = []
    total_cost = 0
    for _ in range(m):
        p = random.randint(1, n)
        q = random.randint(1, 30)
        problems.append((p, q))
        total_cost += topic_time[p - 1] * ratio

    limit_time = random.randint(1, max(1, min(120, total_cost)))

    print(wky_skill, wang_skill)
    print(m, n)
    print(*topic_time)
    for p, q in problems:
        print(p, q)
    print(limit_time)


if __name__ == "__main__":
    main()
