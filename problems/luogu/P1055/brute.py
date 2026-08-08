isbn = input()

digits = []
for ch in isbn:
    if ch.isdigit():
        digits.append(int(ch))

total = 0
for i in range(9):
    total += digits[i] * (i + 1)

mod = total % 11
correct = "X" if mod == 10 else str(mod)
print("Right" if isbn[-1] == correct else isbn[:-1] + correct, end="")
