import sys

gcd_value, lcm_value = map(int, sys.stdin.buffer.read().split())
if lcm_value % gcd_value:
    print(0)
else:
    quotient = lcm_value // gcd_value
    distinct_primes = 0
    prime = 2
    while prime * prime <= quotient:
        if quotient % prime == 0:
            distinct_primes += 1
            while quotient % prime == 0:
                quotient //= prime
        prime += 1
    if quotient > 1:
        distinct_primes += 1
    print(1 << distinct_primes)
