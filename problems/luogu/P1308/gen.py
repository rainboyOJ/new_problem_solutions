#!/usr/bin/env python3
import random
import string


def rand_word(min_len=1, max_len=6):
    letters = string.ascii_letters
    length = random.randint(min_len, max_len)
    return "".join(random.choice(letters) for _ in range(length))


def main():
    random.seed()

    target = rand_word(1, 5)
    n = random.randint(1, 12)
    words = []
    for _ in range(n):
        t = random.randint(1, 5)
        if t == 1:
            words.append(target)
        elif t == 2:
            words.append(target.upper())
        elif t == 3:
            words.append(target + random.choice(string.ascii_letters))
        else:
            words.append(rand_word(1, 6))

    print(target)
    print(" ".join(words))


if __name__ == "__main__":
    main()
