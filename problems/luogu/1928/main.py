def parse(text, index):
    parts = []

    while index < len(text) and text[index] != "]":
        if text[index].isupper():
            parts.append(text[index])
            index += 1
        elif text[index] == "[":
            index += 1
            repeat = 0
            while text[index].isdigit():
                repeat = repeat * 10 + int(text[index])
                index += 1
            inner, index = parse(text, index)
            parts.append(inner * repeat)
        else:
            index += 1

    if index < len(text) and text[index] == "]":
        index += 1

    return "".join(parts), index


encoded = input().strip()
decoded, _ = parse(encoded, 0)
print(decoded)
