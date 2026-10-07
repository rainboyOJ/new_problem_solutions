#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    n = random.randint(5, 200)
    print(n)
    print("".join(random.choice(string.ascii_lowercase) for _ in range(n)))


if __name__ == "__main__":
    main()
