import sys


DIGITS = "0123456789ABCDEF"


def main():
    source_base, number, target_base = sys.stdin.buffer.read().split()
    value = int(number, int(source_base))
    base = int(target_base)

    if value == 0:
        print(0)
        return

    converted = []
    while value:
        value, remainder = divmod(value, base)
        converted.append(DIGITS[remainder])
    print("".join(reversed(converted)))


if __name__ == "__main__":
    main()
