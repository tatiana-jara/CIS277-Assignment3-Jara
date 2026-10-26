# CIS-277 Assignment 3: Text Messages and Dynamic Memory

## Student

Tatiana Jara

## Design

- My plan is to build a simple text-message inbox using a singly linked list.
- Each node will store one TextMessage and a pointer to the next node.
- I will maintain head and tail pointers to keep track of the first and last messages.
- Before accepting a message, I will check its ID, sender, text, and available storage space.
- I will use new to allocate nodes and delete to release memory when messages are removed.
- I will also maintain counters for the number of messages and the number of text bytes used.

## How to Compile

This program uses C++23.

To compile the main program:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp MessageInbox.cpp -o message_inbox
```

To run the professor's public validator:

```bash
python3 validate.py --compiler g++-14
```

## How to Run


On Windows, run:

```powershell
.\message_inbox.exe
```

On Linux or macOS, run:

```bash
./message_inbox
```

The program demonstrates a text-message inbox with a 20-byte storage limit.

It receives messages, marks a message as read, deletes a message, and reuses the available storage.

The demonstration uses the messages from Maya, Noah, and Eli.

## Tests and Results

## Analysis Questions

## AI Use
