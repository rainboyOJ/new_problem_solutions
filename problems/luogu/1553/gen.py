#!/usr/bin/env python3
import random


def number(length):
    if length == 1:
        return str(random.randint(0, 9))
    return str(random.randint(1, 9)) + "".join(str(random.randint(0, 9)) for _ in range(length - 1))


def main():
    random.seed()
    typ = random.randint(0, 3)
    if typ == 0:
        print(number(random.randint(1, 12)))
    elif typ == 1:
        print(number(random.randint(1, 6)) + "." + number(random.randint(1, 6)))
    elif typ == 2:
        print(number(random.randint(1, 6)) + "/" + number(random.randint(1, 6)))
    else:
        print(number(random.randint(1, 12)) + "%")


if __name__ == "__main__":
    main()
