identifier = input().strip()
is_valid = not identifier[0].isdigit() and all(character.isalnum() or character == "_" for character in identifier)
print("yes" if is_valid else "no")
