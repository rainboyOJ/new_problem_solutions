import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    position = {count: i for i, count in enumerate(data[1:n + 1], 1)}
    q = data[n + 1]
    queries = data[n + 2:n + 2 + q]
    print("\n".join(str(position.get(count, 0)) for count in queries))


if __name__ == "__main__":
    main()
