#!/usr/bin/env python3
import random


def make_record(password):
    a = password[:]
    pos = random.randint(0, 4)
    delta = random.randint(1, 9)
    if pos < 4 and random.randint(0, 1) == 1:
        a[pos] = (a[pos] + delta) % 10
        a[pos + 1] = (a[pos + 1] + delta) % 10
    else:
        a[pos] = (a[pos] + delta) % 10
    return a


def main():
    random.seed()
    n = random.randint(1, 8)
    password = [random.randint(0, 9) for _ in range(5)]
    print(n)
    for _ in range(n):
        print(*make_record(password))


if __name__ == "__main__":
    main()
