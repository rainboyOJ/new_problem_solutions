text, position_text = input().split()
position = int(position_text)

length = len(text)
while length < position:
    length *= 2

while position > len(text):
    half = length // 2
    if position == half + 1:
        position = half
    elif position > half + 1:
        position = position - half - 1
    length = half

print(text[position - 1])
