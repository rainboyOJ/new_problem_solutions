#!/usr/bin/env python3
import random


def main():
    random.seed()
    body = bytearray()
    raw = bytearray()

    def add_literal(value):
        length = len(value)
        if length <= 60:
            body.append((length - 1) << 2)
        else:
            body.append(60 << 2)
            body.extend((length - 1).to_bytes(1, "little"))
        body.extend(value)
        raw.extend(value)

    add_literal(bytearray(random.randrange(256) for _ in range(70)))
    for _ in range(12):
        offset = random.randint(1, min(len(raw), 65535))
        length = random.randint(1, 64)
        if random.randint(0, 1) == 0 and 4 <= length <= 11 and offset <= 2047:
            body.append(((offset >> 8) << 5) | ((length - 4) << 2) | 1)
            body.append(offset & 255)
        else:
            body.append(((length - 1) << 2) | 2)
            body.extend(offset.to_bytes(2, "little"))
        start = len(raw) - offset
        for i in range(length):
            raw.append(raw[start + i % offset])
    add_literal(bytearray(random.randrange(256) for _ in range(17)))

    length = len(raw)
    header = bytearray()
    while length >= 128:
        header.append((length & 127) | 128)
        length >>= 7
    header.append(length)
    compressed = header + body
    print(len(compressed))
    for i in range(0, len(compressed), 8):
        print(compressed[i:i + 8].hex())


if __name__ == "__main__":
    main()
