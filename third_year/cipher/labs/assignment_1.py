ARABIC = "ابتثجحخدذرزسشصضطظعغفقكلمنهوي"


print(
    (
        lambda mode: "".join(
            list(
                map(
                    (
                        lambda c: ARABIC[
                            (ARABIC.index(c) + (3 if mode == 1 else -3)) % 28
                        ]
                        if c in ARABIC
                        else c
                    ),
                    input("Enter the text: "),
                )
            )
        )
    )(int(input("1 - Encryption\n2 - Decryption\n\nChoose a mode: ")))
)
