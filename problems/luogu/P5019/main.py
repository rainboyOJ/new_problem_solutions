import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    depth = data[1:1 + n]

    answer = depth[0]
    for i in range(1, n):
        if depth[i] > depth[i - 1]:
            answer += depth[i] - depth[i - 1]

    print(answer)


if __name__ == "__main__":
    main()
