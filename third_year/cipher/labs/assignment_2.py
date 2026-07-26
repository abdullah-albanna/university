while True:
    mode = input("1 - Encryption\n2 - Decryption\n\nChoose a mode: ")

    if mode == "no":
        break
    elif mode in ("1", "2"):
        print(
            (
                lambda mode: "".join(
                    map(
                        lambda c: chr(
                            (
                                (
                                    ord(c)
                                    - (65 if c.isupper() else 97)
                                    + (23 if mode == "1" else -23)
                                )
                                % 26
                            )
                            + (65 if c.isupper() else 97)
                        )
                        if c.isalpha()
                        else c,
                        input("Enter the text: "),
                    )
                )
            )(input("\n1 - Encryption\n2 - Decryption\n\nChoose a mode: "))
        )
    else:
        continue
