isbn = input()

digits = [int(ch) for ch in isbn if ch.isdigit()]
total = sum(digits[i] * (i + 1) for i in range(9))
mod = total % 11
correct = "X" if mod == 10 else str(mod)

if isbn[-1] == correct:
    print("Right", end="")
else:
    print(isbn[:-1] + correct, end="")
