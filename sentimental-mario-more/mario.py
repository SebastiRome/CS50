while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            for line in range(0, height):
                print(" " * ((height - 1) - line), end="")
                print("#" * (line + 1), end="")
                print("  ", end="")
                print("#" * (line + 1), end="")
                print()
            break
        else:
            print("Invalid input. Sould be an integer between 0 and 9")
    except ValueError:
        print("Invalid input. Sould be an integer between 0 and 9")
