def decrypt(character: str) -> str:
    if "A" <= character <= "Z":
        return chr((ord(character) - ord("A") - 5) % 26 + ord("A"))
    return character


print("".join(decrypt(character) for character in input()))
