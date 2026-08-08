import sys
from array import array


text, pattern = sys.stdin.buffer.read().split()
m = len(pattern)
prefix = array("i", [0]) * m

j = 0
for i in range(1, m):
    while j and pattern[i] != pattern[j]:
        j = prefix[j - 1]
    if pattern[i] == pattern[j]:
        j += 1
    prefix[i] = j

matches = bytearray()
j = 0
for i, character in enumerate(text):
    while j and character != pattern[j]:
        j = prefix[j - 1]
    if character == pattern[j]:
        j += 1
    if j == m:
        matches.extend(f"{i - m + 2}\n".encode())
        j = prefix[j - 1]

write = sys.stdout.buffer.write
write(matches)
for start in range(0, m, 8192):
    block = " ".join(map(str, prefix[start:start + 8192])).encode()
    write((b"" if start == 0 else b" ") + block)
write(b"\n")
