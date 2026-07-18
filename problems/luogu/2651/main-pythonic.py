import sys
from math import gcd

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    test_count = data[0]
    pos = 1
    answer = []

    for _ in range(test_count):
        n = data[pos]
        numbers = data[pos + 1:pos + n + 1]
        pos += n + 1
        denominator = numbers[1] // gcd(numbers[0], numbers[1])
        for factor in numbers[2:]:
            denominator //= gcd(denominator, factor)
        answer.append("Yes" if denominator == 1 else "No")

    print("\n".join(answer))

if __name__ == "__main__":
    main()
