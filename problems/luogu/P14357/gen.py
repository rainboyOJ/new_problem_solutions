#!/usr/bin/env python3
import random
import string


def main():
    length = random.randint(1, 18)
    chars = []
    has_non_zero = False

    for _ in range(length):
        if random.randint(0, 2) == 0:
            ch = random.choice(string.ascii_lowercase)
        else:
            ch = random.choice("0123456789")
            if ch != "0":
                has_non_zero = True
        chars.append(ch)

    if not has_non_zero:
        pos = random.randrange(length)
        chars[pos] = random.choice("123456789")

    print("".join(chars))


if __name__ == "__main__":
    main()
