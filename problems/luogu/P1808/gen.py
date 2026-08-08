#!/usr/bin/env python3
import random
import string


def rand_word():
    n = random.randint(1, 6)
    return "".join(random.choice(string.ascii_uppercase) for _ in range(n))


def shuffle_word(s):
    arr = list(s)
    random.shuffle(arr)
    return "".join(arr)


def main():
    random.seed()
    n = random.randint(1, 12)
    words = []
    base = []
    for _ in range(random.randint(1, 4)):
        base.append(rand_word())

    for _ in range(n):
        if base and random.randint(1, 3) == 1:
            words.append(shuffle_word(random.choice(base)))
        else:
            words.append(rand_word())

    print(n)
    for s in words:
        print(s)


if __name__ == "__main__":
    main()
