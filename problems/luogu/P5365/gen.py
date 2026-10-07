#!/usr/bin/env python3
import random


def main() -> None:
    random.seed()

    N = random.randint(1, 6)
    M = random.randint(1, 300)
    print(N, M)
    print(*[random.randint(1, 5) for _ in range(N)])
    print(*[random.randint(1, 20) for _ in range(N)])


if __name__ == "__main__":
    main()
