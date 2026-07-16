import sys
from array import array


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    values = data[1:]
    maximum = max(values)
    frequency = array("I", [0]) * (maximum + 1)
    for value in values:
        frequency[value] += 1

    answer = array("I", [0]) * (n + 1)
    for divisor in range(1, maximum + 1):
        count = 0
        for multiple in range(divisor, maximum + 1, divisor):
            count += frequency[multiple]
        if divisor > answer[count]:
            answer[count] = divisor

    for count in range(n - 1, 0, -1):
        answer[count] = max(answer[count], answer[count + 1])
    print("\n".join(map(str, answer[1:])))


if __name__ == "__main__":
    main()
