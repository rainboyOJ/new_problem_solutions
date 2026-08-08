x = int(input())

match x:
    case 1:
        word = "apple"
    case _:
        word = "apples"

print(f"Today, I ate {x} {word}.", end="")
