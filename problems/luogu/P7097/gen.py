#!/usr/bin/env python3
import random


def main():
    subtask_id = 0
    n = random.randint(0, 6)
    m = random.randint(0, 10)
    w = random.randint(1, 5)
    print(subtask_id)
    print(n, m, w)
    ks = [random.randint(1, 100) for _ in range(m)]
    ps = [random.randint(1, 8) for _ in range(m)]
    if m == 0:
        print()
        print()
    else:
        print(*ks)
        print(*ps)
    xa = random.randint(1, 10) * 100000
    xb = random.randint(1, 10) * 100000
    da = random.randint(1, 100)
    diff = random.randint(1, 100)
    if random.randint(0, 1) == 0:
        db = da + diff
    else:
        db = da - diff
        if db <= 0:
            db = da + diff
    print(xa, xb, da, db)


if __name__ == "__main__":
    main()
