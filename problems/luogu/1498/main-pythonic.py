n = int(input())

picture = [
    " /\\ ",
    "/__\\",
]

for _ in range(2, n + 1):
    height = len(picture)
    top = [" " * height + line + " " * height for line in picture]
    bottom = [line + line for line in picture]
    picture = top + bottom

for line in picture:
    print(line.rstrip())
