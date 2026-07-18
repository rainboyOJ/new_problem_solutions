import sys
from array import array

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    test_count, divisor = data[:2]
    queries = list(zip(data[2::2], data[3::2]))[:test_count]
    max_n = max(n for n, _ in queries)
    max_m = min(max_n, max(m for _, m in queries))
    width = max_m + 1

    prefix = array("I", [0]) * ((max_n + 1) * width)
    combination = [0] * width
    combination[0] = 1 % divisor

    for n in range(max_n + 1):
        if n:
            for m in range(min(n, max_m), 0, -1):
                combination[m] = (combination[m] + combination[m - 1]) % divisor
        row = n * width
        previous_row = row - width
        for m in range(width):
            bad = int(m <= n and combination[m] == 0)
            up = prefix[previous_row + m] if n else 0
            left = prefix[row + m - 1] if m else 0
            diagonal = prefix[previous_row + m - 1] if n and m else 0
            prefix[row + m] = up + left - diagonal + bad

    answer = (str(prefix[n * width + min(n, m, max_m)]) for n, m in queries)
    print("\n".join(answer))

if __name__ == "__main__":
    main()
