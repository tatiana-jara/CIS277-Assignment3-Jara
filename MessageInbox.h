
#ifndef MESSAGEINBOX_H
#define MESSAGEINBOX_H

#include <cstddef>
#include <string>
#include <vector>

struct TextMessage 
{
    std::size_t id;
    std::string sender;
    std::string text;
    bool isRead;
};

class MessageInbox 
{
private:
    struct Node 
    {
        TextMessage message;
        Node* next;
    };

    Node* head;
    Node* tail;

    std::size_t count;
    std::size_t usedBytes;
    std::size_t maxBytes;

public:
    explicit MessageInbox(std::size_t maxTextBytes);
    ~MessageInbox();

    MessageInbox(const MessageInbox&) = delete;
    MessageInbox& operator=(const MessageInbox&) = delete;

    bool receive(std::size_t id,
                 const std::string& sender,
                 const std::string& text);

    bool read(std::size_t id, TextMessage& result);
    bool erase(std::size_t id);

    std::vector<TextMessage> messages() const;

    void clear();

    std::size_t messageCount() const;
    std::size_t usedTextBytes() const;
    std::size_t remainingTextBytes() const;
};

#endif
