#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    n = random.randint(1, 15)
    a = sorted(random.sample(range(-20, 21), n))
    t = random.randint(-25, 25)
    print(n, t)
    print(*a)

if __name__ == "__main__":
    main()
