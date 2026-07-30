term_count = int(input())
total = 0.0

for denominator in range(1, term_count + 1):
    sign = 1 if denominator % 2 else -1
    total += sign / denominator

print(f"{total:.4f}")
