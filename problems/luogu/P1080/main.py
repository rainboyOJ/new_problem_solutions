import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    king_left = data[1]

    ministers = []
    pos = 3
    for _ in range(n):
        left, right = data[pos], data[pos + 1]
        pos += 2
        ministers.append((left, right))

    ministers.sort(key=lambda item: item[0] * item[1])

    prefix = king_left
    answer = 0
    for left, right in ministers:
        coins = prefix // right
        if coins > answer:
            answer = coins
        prefix *= left

    print(answer)


if __name__ == "__main__":
    main()
