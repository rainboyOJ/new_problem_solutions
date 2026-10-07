#!/usr/bin/env python3
import random


def calc_check(digits):
    s = sum((i + 1) * int(d) for i, d in enumerate(digits))
    mod = s % 11
    return "X" if mod == 10 else str(mod)


def main():
    random.seed()
    digits = "".join(str(random.randint(0, 9)) for _ in range(9))
    check = calc_check(digits)
    isbn = f"{digits[0]}-{digits[1:4]}-{digits[4:9]}-{check}"
    if random.randint(0, 1):
        pos = len(isbn) - 1
        wrong = random.choice("0123456789X")
        while wrong == check:
            wrong = random.choice("0123456789X")
        isbn = isbn[:pos] + wrong
    print(isbn)


if __name__ == "__main__":
    main()
