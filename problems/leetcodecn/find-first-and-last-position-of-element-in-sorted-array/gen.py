#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    n = random.randint(0, 15)
    lo = random.randint(-50, 50)
    hi = lo + random.randint(0, 50)
    a = sorted(random.choices(range(lo, hi + 1), k=n))
    t = random.choice(a) if n and random.random() < 0.7 else random.randint(lo - 20, hi + 20)
    print(n, t)
    if n:
        print(*a)

if __name__ == "__main__":
    main()
