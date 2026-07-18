import sys

def factorize(number, multiplier):
    factors = []
    prime = 2
    while prime * prime <= number:
        if number % prime == 0:
            exponent = 0
            while number % prime == 0:
                number //= prime
                exponent += 1
            factors.append((prime, exponent * multiplier))
        prime += 1
    if number > 1:
        factors.append((number, multiplier))
    return factors

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    base, exponent = data[1:3]
    factors = factorize(base, exponent)
    if not factors:
        print(0)
        return

    answer = None
    for cell in data[3:3 + n]:
        required_time = 0
        for prime, required in factors:
            available = 0
            value = cell
            while value % prime == 0:
                value //= prime
                available += 1
            if available == 0:
                break
            required_time = max(required_time, (required + available - 1) // available)
        else:
            answer = required_time if answer is None else min(answer, required_time)

    print(-1 if answer is None else answer)

if __name__ == "__main__":
    main()
