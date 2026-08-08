from itertools import product

n = int(input())

plans = [
    plan
    for plan in product(range(1, 4), repeat=10)
    if sum(plan) == n
]

print(len(plans))
for plan in plans:
    print(*plan)
