x = float(input())

if x < 5:
    value = -x + 2.5
elif x < 10:
    value = 2 - 1.5 * (x - 3) ** 2
else:
    value = x / 2 - 1.5

print(f"{value:.3f}")
