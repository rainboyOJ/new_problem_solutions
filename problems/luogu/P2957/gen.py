#!/usr/bin/env python3
import random
import string


def rand_word():
    n = random.randint(1, 12)
    return "".join(random.choice(string.ascii_lowercase) for _ in range(n))


def main():
    random.seed()
    print(rand_word())
    print(rand_word())


if __name__ == "__main__":
    main()
