prices = [28.9, 32.7, 45.6, 78.0, 35.0, 86.2, 27.8, 43.0, 56.0, 65.0]
counts = map(int, input().split())
total = sum(price * count for price, count in zip(prices, counts))
print(f"{total:.1f}")
