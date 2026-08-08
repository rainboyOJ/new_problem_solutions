#!/usr/bin/env python3
import random
import string


def encrypt_rail(text: str, width: int) -> str:
    groups = []
    for i in range(0, len(text), width):
        groups.append(text[i:i + width])

    out = []
    for col in range(width):
        for group in groups:
            if col < len(group):
                out.append(group[col])
    return "".join(out)


def shift_char(ch: str, delta: int) -> str:
    if "A" <= ch <= "Z":
        return chr((ord(ch) - ord("A") + delta) % 26 + ord("A"))
    if "a" <= ch <= "z":
        return chr((ord(ch) - ord("a") + delta) % 26 + ord("a"))
    return ch


def encrypt_vigenere(text: str, key: str) -> str:
    out = []
    key_len = len(key)
    for i, ch in enumerate(text):
        shift = ord(key[i % key_len].upper()) - ord("A")
        out.append(shift_char(ch, shift))
    return "".join(out)


def encrypt_qwe(text: str) -> str:
    keyboard = "QWERTYUIOPASDFGHJKLZXCVBNM"
    out = []
    for ch in text:
        if "A" <= ch <= "Z":
            out.append(keyboard[ord(ch) - ord("A")])
        elif "a" <= ch <= "z":
            out.append(keyboard[ord(ch.upper()) - ord("A")].lower())
        else:
            out.append(ch)
    return "".join(out)


def main():
    random.seed()

    text_len = random.randint(1, 30)
    plain = "".join(random.choice(string.ascii_uppercase) for _ in range(text_len))

    n = random.randint(1, 6)
    ops = []

    cur = plain
    for _ in range(n):
        typ = random.randint(1, 3)
        if typ == 1:
            width = random.randint(1, max(1, len(cur)))
            ops.append((1, width))
            cur = encrypt_rail(cur, width)
        elif typ == 2:
            key_len = random.randint(1, 6)
            key = "".join(random.choice(string.ascii_uppercase) for _ in range(key_len))
            ops.append((2, key))
            cur = encrypt_vigenere(cur, key)
        else:
            ops.append((3, None))
            cur = encrypt_qwe(cur)

    print(n)
    print(cur)
    for typ, extra in ops:
        if typ == 1:
            print(1, extra)
        elif typ == 2:
            print(2, extra)
        else:
            print(3)


if __name__ == "__main__":
    main()
