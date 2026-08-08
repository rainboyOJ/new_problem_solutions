import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, x = data[0], data[1]
    candies = data[2:2 + n]

    answer = 0
    for i in range(1, n):
        extra = candies[i - 1] + candies[i] - x
        if extra <= 0:
            continue

        eat = min(extra, candies[i])
        candies[i] -= eat
        answer += eat

        extra -= eat
        if extra > 0:
            candies[i - 1] -= extra
            answer += extra

    print(answer)


if __name__ == "__main__":
    main()
