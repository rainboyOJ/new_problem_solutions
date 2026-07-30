text = input()
best_character = text[0]
best_length = 1
current_character = text[0]
current_length = 0

for character in text:
    if character == current_character:
        current_length += 1
    else:
        if current_length > best_length:
            best_character, best_length = current_character, current_length
        current_character, current_length = character, 1
if current_length > best_length:
    best_character, best_length = current_character, current_length

print(best_character, best_length)
