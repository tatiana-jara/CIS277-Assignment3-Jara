#include "MessageInbox.h"
#include <iostream>

void showInbox(const MessageInbox& inbox) 
{
    std::cout << "\n--- INBOX ---\n";

    for (const TextMessage& msg : inbox.messages()) 
    {
        std::cout << "ID: " << msg.id << "\n";
        std::cout << "Sender: " << msg.sender << "\n";
        std::cout << "Text: " << msg.text << "\n";
        std::cout << "Read: "
                  << (msg.isRead ? "Yes" : "No")
                  << "\n\n";
    }

    std::cout << "Message count: "
              << inbox.messageCount() << "\n";

    std::cout << "Used bytes: "
              << inbox.usedTextBytes() << "\n";

    std::cout << "Remaining bytes: "
              << inbox.remainingTextBytes() << "\n";
}

int main() 
{
    MessageInbox inbox(20);

    std::cout << "CIS-277 Assignment 3\n";
    std::cout << "Text Message Inbox\n";

    std::cout << "\nReceive Maya: "
              << (inbox.receive(101, "Maya", "Hi!")
                  ? "Accepted" : "Rejected") << "\n";

    std::cout << "Receive Noah: "
              << (inbox.receive(102, "Noah", "Meet at 6")
                  ? "Accepted" : "Rejected") << "\n";

    showInbox(inbox);

    std::cout << "\nReceive Eli: "
              << (inbox.receive(103, "Eli", "Bring notes")
                  ? "Accepted" : "Rejected") << "\n";

    showInbox(inbox);

    TextMessage result{};

    if (inbox.read(101, result)) 
    {
        std::cout << "\nRead message 101: "
                  << result.text << "\n";
    }

    showInbox(inbox);

    std::cout << "\nDelete message 101: "
              << (inbox.erase(101)
                  ? "Success" : "Failed") << "\n";

    showInbox(inbox);

    std::cout << "\nReceive Eli again: "
              << (inbox.receive(103, "Eli", "Bring notes")
                  ? "Accepted" : "Rejected") << "\n";

    showInbox(inbox);

    inbox.clear();

    std::cout << "\nAfter clear:\n";
    showInbox(inbox);

    return 0;
}
