import sys
from array import array


ODD_BLOCK_SIZE = 1 << 20


def small_primes(limit):
    sieve = bytearray(b"\x01") * (limit + 1)
    sieve[:2] = b"\x00\x00"
    for prime in range(2, int(limit ** 0.5) + 1):
        if sieve[prime]:
            start = prime * prime
            sieve[start::prime] = b"\x00" * ((limit - start) // prime + 1)
    return [number for number in range(3, limit + 1, 2) if sieve[number]]


def first_primes(limit, needed):
    primes = array("I", [2])
    base_primes = small_primes(int(limit ** 0.5))

    low = 3
    while low <= limit and len(primes) < needed:
        high = min(limit, low + 2 * ODD_BLOCK_SIZE - 2)
        if high % 2 == 0:
            high -= 1
        size = (high - low) // 2 + 1
        is_prime = bytearray(b"\x01") * size

        for prime in base_primes:
            if prime * prime > high:
                break
            start = max(prime * prime, (low + prime - 1) // prime * prime)
            if start % 2 == 0:
                start += prime
            index = (start - low) // 2
            is_prime[index::prime] = b"\x00" * ((size - 1 - index) // prime + 1)

        index = is_prime.find(1)
        while index != -1 and len(primes) < needed:
            primes.append(low + 2 * index)
            index = is_prime.find(1, index + 1)
        low = high + 2

    return primes


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    limit = data[0]
    queries = data[2:]
    primes = first_primes(limit, max(queries))
    print("\n".join(str(primes[index - 1]) for index in queries))


if __name__ == "__main__":
    main()
