#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    n = random.randint(1, 200)
    alphabet = string.ascii_letters + string.digits
    pool = []

    base_count = random.randint(1, min(n, 60))
    for _ in range(base_count):
        length = random.randint(1, 30)
        text = "".join(random.choice(alphabet) for _ in range(length))
        pool.append(text)

    print(n)
    for _ in range(n):
        if random.randint(0, 99) < 55:
            print(random.choice(pool))
        else:
            length = random.randint(1, 30)
            print("".join(random.choice(alphabet) for _ in range(length)))


if __name__ == "__main__":
    main()
