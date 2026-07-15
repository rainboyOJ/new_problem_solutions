from functools import cmp_to_key
import sys


def compare(x, y):
    if x + y > y + x:
        return -1
    if x + y < y + x:
        return 1
    return 0


def main():
    tokens = sys.stdin.read().split()
    n = int(tokens[0])
    numbers = tokens[1:1 + n]
    numbers.sort(key=cmp_to_key(compare))
    print("".join(numbers))


if __name__ == "__main__":
    main()
