def encrypt(character: str) -> str:
    if "a" <= character <= "y" or "A" <= character <= "Y":
        return chr(ord(character) + 1)
    if character == "z":
        return "a"
    if character == "Z":
        return "A"
    return character


print("".join(encrypt(character) for character in input()))
