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

## Tests and Results

I compiled and ran my `main.cpp` program to verify the required 20-byte message inbox example.

| Test | Expected Result | Actual Result | Status |
|---|---|---|---|
| Receive Maya | Accepted, 3 bytes used | Accepted, 3 bytes used | PASS |
| Receive Noah | Accepted, 12 bytes used | Accepted, 12 bytes used | PASS |
| Receive Eli | Rejected, 12 bytes used | Rejected, 12 bytes used | PASS |
| Read Maya | Read: Yes, 12 bytes used | Read: Yes, 12 bytes used | PASS |
| Delete Maya | 9 bytes used, 11 remaining | 9 bytes used, 11 remaining | PASS |
| Receive Eli again | Accepted, 20 bytes used | Accepted, 20 bytes used | PASS |
| Clear inbox | 0 messages, 0 bytes used | 0 messages, 0 bytes used | PASS |

**Public Validator:** PASS — GitHub Actions, Assignment 3 Preflight.

**Main Program:** All seven demonstration steps produced the expected results.

**Memory Checking:** The public validator passed on GitHub Actions. A separate memory sanitizer check was not performed.

## Analysis Questions


### Question 1: Which pointers change when the first, last, or only message is deleted? Include diagrams.

When the first message is deleted, head moves to the next node.

Before:
head -> [101] -> [102] -> nullptr
                    ^
                   tail

After deleting 101:
head -> [102] -> nullptr
         ^
        tail

When the last message is deleted, the previous node becomes the new tail, and its next pointer is nullptr.

Before:
head -> [101] -> [102] -> nullptr
                    ^
                   tail

After deleting 102:
head -> [101] -> nullptr
         ^
        tail

When the only message is deleted, both head and tail become nullptr.

Before:
head, tail -> [101] -> nullptr

After:
head = nullptr
tail = nullptr

### Question 2: Why does reading leave storage budget unchanged while deleting makes room?

Reading changes the isRead flag but does not remove the message. Therefore, the text still uses storage.
Deleting removes the node and releases its text bytes, making space for another message.

### Question 3: What does the byte counter measure, and which actual memory costs are excluded?

The byte counter measures the total number of bytes used by stored message texts.
It does not count sender names, node pointers, string capacity, or memory allocation overhead.

### Question 4: Why does receive take O(n) search work even though appending takes O(1) link changes? Account for string copying too.

Appending a node using tail takes O(1) pointer changes.
However, receive must search the linked list to check for duplicate IDs. This search takes O(n) in the worst case.
Copying the sender and text also requires time depending on their lengths.

### Question 5: What goes wrong if nodes remain allocated after destruction, or two inbox objects share ownership of the same chain?

If allocated nodes are not deleted, memory leaks occur.
If two inbox objects own the same nodes, both might try to delete them, causing undefined behavior.
Deleting copy operations prevents two MessageInbox objects from accidentally sharing the same node chain.


## AI Use

I used ChatGPT to help me understand the assignment requirements.
ChatGPT helped me understand singly linked lists, head and tail pointers, and how new and delete are used for dynamic memory management.
To verify my work, I ran the main program and compared the results with the expected values. I also used the instructor's public validator, which passed on GitHub Actions.
I learned more about how head and tail pointers work and why dynamically allocated nodes must be deleted to avoid memory leaks.
