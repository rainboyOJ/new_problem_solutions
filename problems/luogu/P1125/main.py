from collections import Counter


def is_prime(x):
    if x < 2:
        return False
    divisor = 2
    while divisor * divisor <= x:
        if x % divisor == 0:
            return False
        divisor += 1
    return True


word = input().strip()
counter = Counter(word)
counts = counter.values()
difference = max(counts) - min(counts)

if is_prime(difference):
    print("Lucky Word")
    print(difference)
else:
    print("No Answer")
    print(0)
