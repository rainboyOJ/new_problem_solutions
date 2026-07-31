#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 6)
    m = random.randint(1, 12)
    basic = []
    piece = []
    for _ in range(n):
        basic.append(random.randint(1, 5))
        piece.append(random.randint(1, 5))

    goods = []
    for _ in range(m):
        goods.append((random.randint(20, 100), random.randrange(n)))
    total_profit = 0
    for value, warehouse in goods:
        total_profit += value - piece[warehouse]
    for warehouse in set(item[1] for item in goods):
        total_profit -= basic[warehouse]
    target = random.randint(1, max(1, total_profit))

    print(n, m, target)
    for i in range(n): print(basic[i], piece[i])
    for value, warehouse in goods: print(value, warehouse)


if __name__ == "__main__":
    main()
