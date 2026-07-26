POSSIBLE_KEYS: list[int] = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
print(
    (
        lambda key, mode: (exit(1) if print("\nERROR: Key is invalid", end="") else "")
        if key not in POSSIBLE_KEYS
        else "".join(
            list(
                map(
                    lambda char: chr(
                        (
                            (
                                (ord(char) - (ord("A") if char.isupper() else ord("a")))
                                * (
                                    key
                                    if mode == 2
                                    else (
                                        [
                                            k
                                            for k in POSSIBLE_KEYS
                                            if (key * k) % 26 == 1
                                        ][0]
                                    )
                                )
                            )
                            % 26
                        )
                        + (ord("A") if char.isupper() else ord("a"))
                    )
                    if char.isalpha()
                    else char,
                    input("Enter your text: "),
                )
            )
        )
    )(
        int(input("Enter the key: ")),
        int(input("\n1 - Encryption\n2 - Decryption\n\nChoose a mode: ")),
    )
)
