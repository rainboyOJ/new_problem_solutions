#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    print(n)
    for _ in range(n):
        need = random.randint(1, 30)
        deadline = random.randint(1, 120)
        print(need, deadline)


if __name__ == "__main__":
    main()
