import sys
from array import array

MOD = 666623333

def primes_up_to(limit):
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

def main():
    left, right = map(int, sys.stdin.buffer.read().split())
    remaining = array("Q", range(left, right + 1))
    phi = array("Q", remaining)

    for prime in primes_up_to(int(right ** 0.5)):
        start = (left + prime - 1) // prime * prime
        for value in range(start, right + 1, prime):
            index = value - left
            phi[index] = phi[index] // prime * (prime - 1)
            while remaining[index] % prime == 0:
                remaining[index] //= prime

    for index, factor in enumerate(remaining):
        if factor > 1:
            phi[index] = phi[index] // factor * (factor - 1)

    answer = sum(value - phi[index] for index, value in enumerate(range(left, right + 1)))
    print(answer % MOD)

if __name__ == "__main__":
    main()
