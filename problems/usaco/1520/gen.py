#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    print(n)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        difficulty = random.randint(0, 20)
        enjoyment = random.randint(0, 50)
        print(parent, difficulty, enjoyment)

    m = random.randint(1, 30)
    print(m)
    for _ in range(m):
        skill = random.randint(0, 20)
        courage = random.randint(0, 10)
        print(skill, courage)


if __name__ == "__main__":
    main()
