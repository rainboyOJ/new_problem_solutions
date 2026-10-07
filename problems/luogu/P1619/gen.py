#!/usr/bin/env python3
import random
import string


def mix_digits(num: str) -> str:
    symbols = "#@.-_abcXYZ"
    parts = []
    if random.randint(0, 1):
        parts.append(random.choice(symbols))
    for ch in num:
        parts.append(ch)
        if random.randint(0, 1):
            parts.append(random.choice(symbols))
    if random.randint(0, 1):
        parts.append(random.choice(symbols))
    return "".join(parts)


def make_case() -> str:
    typ = random.randint(1, 5)
    if typ == 1:
        value = random.randint(0, 500)
        return str(value)
    if typ == 2:
        value = random.randint(0, 500)
        return mix_digits(str(value))
    if typ == 3:
        value = random.randint(40000001, 99999999)
        return mix_digits(str(value))
    if typ == 4:
        value = random.randint(0, 500)
        return "-" + mix_digits(str(value))
    value = random.randint(0, 500)
    return "0" * random.randint(1, 4) + mix_digits(str(value))


def main():
    random.seed()
    n = random.randint(1, 20)
    for _ in range(n):
        print(make_case())
    print("halt")


if __name__ == "__main__":
    main()
