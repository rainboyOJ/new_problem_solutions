import sys
from math import gcd

def prime_table(limit):
    sieve = bytearray(b"\x01") * (limit + 1)
    if limit >= 0:
        sieve[0] = 0
    if limit >= 1:
        sieve[1] = 0
    for prime in range(2, int(limit ** 0.5) + 1):
        if sieve[prime]:
            start = prime * prime
            sieve[start::prime] = b"\x00" * ((limit - start) // prime + 1)
    return [number for number in range(2, limit + 1) if sieve[number]]

def factorize(number, primes):
    factors = []
    for prime in primes:
        if prime * prime > number:
            break
        if number % prime == 0:
            exponent = 0
            while number % prime == 0:
                number //= prime
                exponent += 1
            factors.append((prime, exponent))
    if number > 1:
        factors.append((number, 1))
    return factors

def divisors_of(number, primes):
    divisors = [1]
    for prime, exponent in factorize(number, primes):
        original = divisors[:]
        power = 1
        for _ in range(exponent):
            power *= prime
            divisors.extend(value * power for value in original)
    return divisors

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    cases = [tuple(data[pos:pos + 4]) for pos in range(1, len(data), 4)]
    primes = prime_table(int(max(case[3] for case in cases) ** 0.5))
    answer = []
    for a0, a1, b0, b1 in cases:
        count = sum(
            gcd(value, a0) == a1 and value // gcd(value, b0) * b0 == b1
            for value in divisors_of(b1, primes)
        )
        answer.append(str(count))
    print("\n".join(answer))

if __name__ == "__main__":
    main()
