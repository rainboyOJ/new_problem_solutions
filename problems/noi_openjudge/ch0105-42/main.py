height_text, width_text, character, filled_text = input().split()
height = int(height_text)
width = int(width_text)
filled = filled_text == "1"

for row in range(height):
    is_border = row == 0 or row == height - 1
    if filled or is_border:
        print(character * width)
    else:
        print(character + " " * (width - 2) + character)
