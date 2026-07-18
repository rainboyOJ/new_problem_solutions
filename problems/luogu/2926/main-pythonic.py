import sys
from array import array

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    values = data[1:]
    maximum = max(values)
    frequency = array("I", [0]) * (maximum + 1)
    divisor_count = array("I", [0]) * (maximum + 1)

    for value in values:
        frequency[value] += 1
    for divisor in range(1, maximum + 1):
        count = frequency[divisor]
        if count:
            for multiple in range(divisor, maximum + 1, divisor):
                divisor_count[multiple] += count

    print("\n".join(str(divisor_count[value] - 1) for value in values))

if __name__ == "__main__":
    main()
