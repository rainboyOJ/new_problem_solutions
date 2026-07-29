#!/usr/bin/env python3
import random

def main() -> None:
    random.seed()
    k = random.randint(1, 8)
    candidates = random.sample(range(2, 21), k)
    target = random.randint(1, 30)
    print(k, target)
    print(*candidates)

if __name__ == "__main__":
    main()
