#!/usr/bin/env python3
import random


def main():
    random.seed()

    m = random.randint(1, 40)
    n = random.randint(1, 40)
    schools = [random.randint(0, 200) for _ in range(m)]
    students = [random.randint(0, 200) for _ in range(n)]

    print(m, n)
    print(" ".join(map(str, schools)))
    print(" ".join(map(str, students)))


if __name__ == "__main__":
    main()
