import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    pos = 1
    finish = [0] * (n + 1)

    for _ in range(n):
        task, duration = data[pos], data[pos + 1]
        pos += 2
        earliest_start = 0
        while data[pos]:
            earliest_start = max(earliest_start, finish[data[pos]])
            pos += 1
        pos += 1
        finish[task] = earliest_start + duration

    print(max(finish))


if __name__ == "__main__":
    main()
