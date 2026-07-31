#!/usr/bin/env python3
import random
import os


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(2, 9)
    position = [0]
    for _ in range(1, n):
        position.append(position[-1] + random.randint(2, 6))
    print(n)
    print(*position)


if __name__ == "__main__":
    main()
