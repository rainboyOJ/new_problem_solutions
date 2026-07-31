#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    total = random.randint(1, 100)
    factors = [x for x in range(1, total + 1) if total % x == 0]
    n = random.choice(factors)
    m = total // n
    operation_count = random.randint(1, 100)
    print(n, m, operation_count)
    for i in range(n):
        print(*[random.randint(-1000, 1000) for _ in range(m)])

    for _ in range(operation_count):
        type = random.randint(1, 3)
        if type == 1:
            new_n = random.choice(factors)
            print(1, new_n, total // new_n)
            n = new_n
            m = total // new_n
        elif type == 2:
            print(2, 0, 0)
            n, m = m, n
        else:
            print(3, random.randrange(n), random.randrange(m))


if __name__ == "__main__":
    main()
