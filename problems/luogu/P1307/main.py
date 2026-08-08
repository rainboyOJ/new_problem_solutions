text = input().strip()

negative = text.startswith("-")
digits = text[1:] if negative else text

answer = int(digits[::-1])
if negative:
    answer = -answer

print(answer)
