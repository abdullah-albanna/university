posts = {}  
accounts = []  
current_account = ""
is_logged_in = False

while True:
    choice = input("> ").strip().lower()
    
    if choice == "signup":
        username = input("Enter your username: ").strip()
        exists = False

        for account in accounts:
            if account[0] == username:
                print(f"{username} already exists")
                exists = True
                break

        if exists:
            continue

        password = input("Enter your password: ").strip()
        accounts.append((username, password))
        print("Signup successful!")
    
    elif choice == "login":
        username = input("Enter your username: ").strip()
        found = False
        for account in accounts:
            if account[0] == username:
                found = True
                password = input("Enter your password: ").strip()
                if account[1] == password:
                    is_logged_in = True 
                    current_account = username
                    print(f"Welcome, {username}!")
                else:
                    print("Incorrect password")
                break

        if not found:
            print(f"{username} does not exist")
    
    elif choice == "logout":
        if is_logged_in:
            print(f"Goodbye, {current_account}")
            is_logged_in = False
            current_account = ""
        else:
            print("No user is currently logged in.")
    
    elif choice == "add":
        if is_logged_in:
            title = input("Enter the post's title: ").strip()
            content = input("Enter the content: ").strip()
            posts[title] = (content, current_account)
            print("Post added successfully!")
        else:
            print("You must be logged in, type 'help' for more info.")
    
    elif choice == "list":
        if posts:
            for title, (content, author) in posts.items():
                print(f"Title: {title} (by {author})")
                print(f"\tContent: {content}")
        else:
            print("No posts available.")
    
    elif choice == "delete":
        if is_logged_in:
            title = input("Enter the title of the post to delete: ").strip()
            if title in posts:
                if posts[title][1] == current_account:
                    posts.pop(title)
                    print("Post deleted successfully!")
                else:
                    print("You cannot delete a post that isn't yours.")
            else:
                print("Post not found.")
        else:
            print("You must be logged in to delete a post.")
    
    elif choice == "help":
        print("Available commands:")
        print("  signup -> register a new account")
        print("  login  -> log in to your account")
        print("  logout -> log out of your account")
        print("  add    -> add a new post (requires login)")
        print("  list   -> list all posts")
        print("  delete -> delete one of your posts (requires login)")
        print("  help   -> show this help screen")
        print("  quit   -> exit the application")
    
    elif choice == "quit":
        print("Exiting the application")
        break
    
    else:
        print("Invalid choice, type 'help' for more info")
