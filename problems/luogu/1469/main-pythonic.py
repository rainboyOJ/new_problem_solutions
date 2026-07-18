import sys

def integers():
    number = 0
    reading = False
    for chunk in iter(lambda: sys.stdin.buffer.read(1 << 20), b""):
        for byte in chunk:
            if 48 <= byte <= 57:
                number = number * 10 + byte - 48
                reading = True
            elif reading:
                yield number
                number = 0
                reading = False
    if reading:
        yield number

def main():
    data = integers()
    n = next(data)
    answer = 0
    for _ in range(n):
        answer ^= next(data)
    print(answer)

if __name__ == "__main__":
    main()
