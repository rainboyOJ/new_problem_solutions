ciphertext = input().strip()
plaintext = input().strip()
message = input().strip()

cipher_to_plain = {}
plain_to_cipher = {}
is_valid = True

for cipher, plain in zip(ciphertext, plaintext):
    if cipher_to_plain.get(cipher, plain) != plain or plain_to_cipher.get(plain, cipher) != cipher:
        is_valid = False
        break
    cipher_to_plain[cipher] = plain
    plain_to_cipher[plain] = cipher

if not is_valid or len(cipher_to_plain) != 26:
    print("Failed")
else:
    print("".join(cipher_to_plain[character] for character in message))
