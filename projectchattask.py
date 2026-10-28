def chattask():
    print("Hello! I am your assistant. Type 'bye' to exit.\n")
    while True:
        user = input("You: ").lower()
        if user == "hello":
            print("Bot: Hi there! How can I assist you today?")
        elif user == "how are you":
            print("Bot: I am fine! How can I help you?")
        elif user == "your name":
            print("Bot: I am a simple chatbot created to assist you.")
        elif user == "help":
            print("Bot: I can answer basic questions like 'hello', 'how are you'")
        elif user == "bye":
            print("Bot: Goodbye! Have a great day! ")
            break
        else:
            print("Bot: Sorry, I don't understand that.")
chattask()