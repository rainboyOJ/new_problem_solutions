inorder = input().strip()
preorder = input().strip()


def postorder(infix, prefix):
    if not infix:
        return ""
    root = prefix[0]
    middle = infix.index(root)
    return (
        postorder(infix[:middle], prefix[1:middle + 1])
        + postorder(infix[middle + 1:], prefix[middle + 1:])
        + root
    )


print(postorder(inorder, preorder))
