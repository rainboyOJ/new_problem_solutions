from collections import Counter


def is_prime(x: int) -> bool:
    return x >= 2 and all(x % d for d in range(2, int(x**0.5) + 1))


counts = Counter(input().strip()).values()
difference = max(counts) - min(counts)
print("Lucky Word\n" + str(difference) if is_prime(difference) else "No Answer\n0", end="")
