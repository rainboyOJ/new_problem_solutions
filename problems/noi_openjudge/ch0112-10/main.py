limit = int(input())
is_prime = [True] * (limit + 1)
if limit >= 0:
    is_prime[0] = False
if limit >= 1:
    is_prime[1] = False

for number in range(2, int(limit**0.5) + 1):
    if is_prime[number]:
        is_prime[number * number : limit + 1 : number] = [False] * len(
            range(number * number, limit + 1, number)
        )

pairs = [(number, number + 2) for number in range(2, limit - 1) if is_prime[number] and is_prime[number + 2]]
if pairs:
    for first, second in pairs:
        print(first, second)
else:
    print("empty")
