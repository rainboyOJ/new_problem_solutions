#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 20)
    q = random.randint(1, 20)
    alphabet_size = random.randint(2, 5)
    letters = [chr(ord("a") + i) for i in range(alphabet_size)]
    s = "".join(random.choice(letters) for _ in range(n))

    print(n, q)
    print(s)
    for _ in range(q):
        l = random.randint(1, n - 2)
        r = random.randint(l + 2, n)
        print(l, r)


if __name__ == "__main__":
    main()
