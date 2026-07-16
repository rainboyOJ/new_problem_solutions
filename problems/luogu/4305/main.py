import sys


def main():
    data = sys.stdin.buffer.read().split()
    test_cases = int(data[0])
    pos = 1
    answer = []

    for _ in range(test_cases):
        n = int(data[pos])
        pos += 1
        values = data[pos:pos + n]
        pos += n
        answer.append(b" ".join(dict.fromkeys(values)))

    sys.stdout.buffer.write(b"\n".join(answer))


if __name__ == "__main__":
    main()
