def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
        except ValueError:
            pass

height = get_height()

for i in range(1, height + 1):
    spaces = height - i
    hashes = i
    print(" " * spaces + "#" * hashes)