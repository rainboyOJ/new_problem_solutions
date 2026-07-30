term_count = int(input())
numerator, denominator = 2, 1
total = 0.0

for _ in range(term_count):
    total += numerator / denominator
    numerator, denominator = numerator + denominator, numerator

print(f"{total:.4f}")
