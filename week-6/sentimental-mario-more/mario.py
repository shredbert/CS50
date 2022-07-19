from cs50 import get_int


def main():
    # Get input
    height = get_height()
    # Print blocks
    print_blocks(height)


def get_height():
    # Get height between 1 & 8 inclusive
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    return height


def print_blocks(height):
    # Print 2 inverse pyramids with 2 spaces between each
    for i in range(height):
        for j in range(height + i + 3):
            if (j < height - i - 1 or j > height + i + 2
                    or (j > height - 1 and j < height + 2)):
                print(" ", end="")
            else:
                print("#", end="")
        print()


if __name__ == "__main__":
    main()
