def main():
    # Handle no input
    while True:
        name = input("What is your name? ")
        if name:
            break

    # Printing name with formatting for conciseness
    print(f"hello, {name}")


if __name__ == "__main__":
    main()
