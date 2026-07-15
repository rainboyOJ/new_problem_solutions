import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    heights = data[1:1 + n]
    heights.sort()

    left = 0
    right = n - 1
    current = 0
    answer = 0

    while left <= right:
        diff = heights[right] - current
        answer += diff * diff
        current = heights[right]
        right -= 1

        if left > right:
            break

        diff = heights[left] - current
        answer += diff * diff
        current = heights[left]
        left += 1

    print(answer)


if __name__ == "__main__":
    main()
