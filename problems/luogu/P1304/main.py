def build_prime_table(limit):
    is_prime = [True] * (limit + 1)
    is_prime[0] = False
    is_prime[1] = False

    for x in range(2, limit + 1):
        if is_prime[x]:
            for multiple in range(x * x, limit + 1, x):
                is_prime[multiple] = False

    return is_prime


n = int(input())
is_prime = build_prime_table(n)

for even in range(4, n + 1, 2):
    for first in range(2, even):
        second = even - first
        if is_prime[first] and is_prime[second]:
            print(f"{even}={first}+{second}")
            break
