from functools import reduce


def name_value(name: str) -> int:
    return reduce(lambda value, ch: value * (ord(ch) - 64) % 47, name, 1)


print("GO" if name_value(input().strip()) == name_value(input().strip()) else "STAY")
