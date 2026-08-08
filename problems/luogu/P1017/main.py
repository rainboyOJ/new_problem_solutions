import sys


DIGITS = "0123456789ABCDEFGHIJ"


def main():
    original, base = map(int, sys.stdin.buffer.read().split())
    value = original
    converted = []

    if value == 0:
        converted.append("0")
    while value:
        remainder = value % (-base)
        value = (value - remainder) // base
        converted.append(DIGITS[remainder])

    print(f"{original}={''.join(reversed(converted))}(base{base})")


if __name__ == "__main__":
    main()
