from random import Random
import sys


rng = Random(int(sys.argv[1]) if len(sys.argv) > 1 else 4036)
alphabet = b"abc"
text = bytearray(rng.choice(alphabet) for _ in range(rng.randint(1, 12)))
initial = bytes(text)
operations = []

for _ in range(80):
    kind = rng.choice((b"Q", b"R", b"I"))
    if kind == b"Q":
        x = rng.randint(1, len(text))
        y = rng.randint(1, len(text))
        operations.append(b"Q %d %d" % (x, y))
    elif kind == b"R":
        x = rng.randint(1, len(text))
        char = rng.choice(alphabet)
        text[x - 1] = char
        operations.append(b"R %d %c" % (x, char))
    else:
        x = rng.randint(0, len(text))
        char = rng.choice(alphabet)
        text.insert(x, char)
        operations.append(b"I %d %c" % (x, char))

print(initial.decode())
print(len(operations))
for operation in operations:
    print(operation.decode())
