text = input().strip().upper()
parts = []
count = 1

for index in range(1, len(text) + 1):
    if index < len(text) and text[index] == text[index - 1]:
        count += 1
    else:
        parts.append(f"({text[index - 1]},{count})")
        count = 1

print("".join(parts))
