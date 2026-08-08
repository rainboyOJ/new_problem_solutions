#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(1, 10)
    k = random.randint(0, 4)
    print(n, k)
    gestures = ["H", "P", "S"]
    for _ in range(n):
        print(random.choice(gestures))


if __name__ == "__main__":
    main()
