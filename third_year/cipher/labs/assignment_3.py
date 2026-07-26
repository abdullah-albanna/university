(
    lambda text: print(
        list(
            map(
                lambda key: "".join(
                    map(
                        lambda c: chr(
                            ((ord(c) - (65 if c.isupper() else 97) - key) % 26)
                            + (65 if c.isupper() else 97)
                        )
                        if c.isalpha()
                        else c,
                        text,
                    )
                ),
                range(1, 26),
            )
        )
    )
)(input("Enter the text: "))
