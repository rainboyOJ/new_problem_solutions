import sys

def main():
    left, right = map(int, sys.stdin.buffer.read().split())
    limit = int(right ** 0.5)
    base_prime = bytearray(b"\x01") * (limit + 1)
    if limit >= 0:
        base_prime[0] = 0
    if limit >= 1:
        base_prime[1] = 0
    for prime in range(2, int(limit ** 0.5) + 1):
        if base_prime[prime]:
            start = prime * prime
            base_prime[start::prime] = b"\x00" * ((limit - start) // prime + 1)

    segment = bytearray(b"\x01") * (right - left + 1)
    for prime in range(2, limit + 1):
        if not base_prime[prime]:
            continue
        start = max(prime * prime, (left + prime - 1) // prime * prime)
        if start <= right:
            segment[start - left::prime] = b"\x00" * ((right - start) // prime + 1)
    if left == 1:
        segment[0] = 0
    print(sum(segment))

if __name__ == "__main__":
    main()
