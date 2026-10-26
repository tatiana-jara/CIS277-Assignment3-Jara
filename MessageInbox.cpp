#include "MessageInbox.h"
#include <stdexcept>

MessageInbox::MessageInbox(std::size_t maxTextBytes)
    : head(nullptr),
      tail(nullptr),
      count(0),
      usedBytes(0),
      maxBytes(maxTextBytes) 
{

    if (maxTextBytes == 0) 
    {
        throw std::invalid_argument("Invalid budget");
    }
}

MessageInbox::~MessageInbox() 
{
    clear();
}

bool MessageInbox::receive(
    std::size_t id,
    const std::string& sender,
    const std::string& text) 
{

    if (id == 0 || sender.empty() || text.empty()) 
    {
        return false;
    }

    if (text.size() > remainingTextBytes()) 
    {
        return false;
    }

    Node* current = head;

    while (current != nullptr) 
    {
        if (current->message.id == id) 
        {
            return false;
        }
        current = current->next;
    }

    Node* node = new Node
    {
        TextMessage{id, sender, text, false},
        nullptr
    };

    if (head == nullptr) 
    {
        head = node;
        tail = node;
    } 
    else 
    {
        tail->next = node;
        tail = node;
    }

    count++;
    usedBytes += text.size();

    return true;
}

bool MessageInbox::read(
    std::size_t id,
    TextMessage& result) 
{

    Node* current = head;

    while (current != nullptr) 
    {
        if (current->message.id == id) 
        {
            TextMessage copy = current->message;
            copy.isRead = true;

            result = copy;
            current->message.isRead = true;

            return true;
        }

        current = current->next;
    }

    return false;
}

bool MessageInbox::erase(std::size_t id) 
{
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) 
    {
        if (current->message.id == id) 
        {
            if (previous == nullptr) 
            {
                head = current->next;
            } 
            else 
            {
                previous->next = current->next;
            }
            if (current == tail) 
            {
                tail = previous;
            }

            usedBytes -= current->message.text.size();
            count--;

            delete current;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

std::vector<TextMessage> MessageInbox::messages() const 
{
    std::vector<TextMessage> result;

    Node* current = head;

    while (current != nullptr) 
    {
        result.push_back(current->message);
        current = current->next;
    }

    return result;
}

void MessageInbox::clear() 
{
    while (head != nullptr) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    count = 0;
    usedBytes = 0;
}

std::size_t MessageInbox::messageCount() const 
{
    return count;
}

std::size_t MessageInbox::usedTextBytes() const 
{
    return usedBytes;
}

std::size_t MessageInbox::remainingTextBytes() const 
{
    return maxBytes - usedBytes;
}
