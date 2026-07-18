import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    limit = data[0]
    n = data[1]
    prices = data[2:2 + n]

    prices.sort()
    left = 0
    right = n - 1
    answer = 0

    while left <= right:
        if prices[left] + prices[right] <= limit:
            left += 1
        right -= 1
        answer += 1

    print(answer)

if __name__ == "__main__":
    main()
