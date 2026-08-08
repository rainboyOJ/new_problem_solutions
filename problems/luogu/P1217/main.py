from math import isqrt


def is_prime(x):
    if x < 2:
        return False
    if x == 2:
        return True
    if x % 2 == 0:
        return False

    for d in range(3, isqrt(x) + 1, 2):
        if x % d == 0:
            return False
    return True


def make_odd_palindrome(seed):
    text = str(seed)
    return int(text + text[-2::-1])


a, b = map(int, input().split())

answer = []

for x in range(1, 10):
    if a <= x <= b and is_prime(x):
        answer.append(str(x))

if a <= 11 <= b:
    answer.append("11")

for seed in range(10, 10000):
    value = make_odd_palindrome(seed)
    if value > b:
        break
    if value >= a and is_prime(value):
        answer.append(str(value))

print("\n".join(answer))
