principal, payment, months = map(int, input().split())


def remaining_balance(rate):
    balance = principal
    for _ in range(months):
        balance = balance * (1 + rate) - payment
    return balance


left, right = 0.0, 3.0
for _ in range(100):
    middle = (left + right) / 2
    if remaining_balance(middle) <= 0:
        left = middle
    else:
        right = middle

print(f"{left * 100:.1f}")
