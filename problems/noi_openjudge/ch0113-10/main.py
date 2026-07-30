left, right = sorted(map(int, input().split()))
is_prime = [True] * (right + 1)
is_prime[0] = False
if right >= 1:
    is_prime[1] = False

for number in range(2, int(right**0.5) + 1):
    if is_prime[number]:
        for multiple in range(number * number, right + 1, number):
            is_prime[multiple] = False

print(sum(is_prime[left : right + 1]))
