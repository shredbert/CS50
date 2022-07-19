from cs50 import get_int


def main():
    height = get_height()
    print_blocks(height)


# Get height from user using CS50 -- requirement
def get_height():
    # Height must be between 1 & 8 -- re-prompt if not
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    return height


# Print blocks -- don't know how to do recursively unless triangle inverted
def print_blocks(height):
    for i in range(height):
        for j in range(height):
            if j < height - i - 1:
                print(" ", end="")
            else:
                print("#", end="")
        print()


if __name__ == "__main__":
    main()
