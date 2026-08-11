#!/usr/bin/env python3
import random
import string


def random_word():
    base = ''.join(random.choice(string.ascii_lowercase + string.digits) for _ in range(random.randint(1, 12)))
    pat = random.choice(["", "shuki", "daishuki", "kirai", "shukikirai", "daishukikirai"])
    if not pat:
        return base
    pos = random.randint(0, len(base))
    return base[:pos] + pat + base[pos:]


def main():
    random.seed()
    n = random.randint(1, 30)
    s = random.randint(-20, 20)
    print(n, s)
    for _ in range(n):
        print(random_word())


if __name__ == "__main__":
    main()
