left, right = map(int, input().split())
is_prime = [True] * 100_001
is_prime[0] = False
if right >= 1:
    is_prime[1] = False
for number in range(2, int(100_000**0.5) + 1):
    if is_prime[number]:
        for multiple in range(number * number, 100_001, number):
            is_prime[multiple] = False

answers = [
    number
    for number in range(left, right + 1)
    if is_prime[number] and is_prime[int(str(number)[::-1])]
]
print(",".join(map(str, answers)) if answers else "No")
