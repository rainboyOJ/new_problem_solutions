key = input()
ciphertext = input()
plaintext = []

for index, encrypted in enumerate(ciphertext):
    shift = ord(key[index % len(key)].lower()) - ord("a")
    base = ord("A") if encrypted.isupper() else ord("a")
    plaintext.append(chr((ord(encrypted) - base - shift) % 26 + base))

print("".join(plaintext))
