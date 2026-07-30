mode, repeat_count, direction = map(int, input().split())
text = input().strip()
answer = []

for index, character in enumerate(text):
    if character != "-" or index == 0 or index == len(text) - 1:
        answer.append(character)
        continue

    left, right = text[index - 1], text[index + 1]
    same_kind = (left.islower() and right.islower()) or (left.isdigit() and right.isdigit())
    if not same_kind or left >= right:
        answer.append("-")
        continue

    middle = []
    for code in range(ord(left) + 1, ord(right)):
        character_to_fill = chr(code)
        if mode == 2:
            character_to_fill = character_to_fill.upper()
        elif mode == 3:
            character_to_fill = "*"
        middle.append(character_to_fill * repeat_count)

    expanded = "".join(middle)
    answer.append(expanded if direction == 1 else expanded[::-1])

print("".join(answer))
