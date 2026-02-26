# LAN-Based Quiz Game (Timed MCQs, Real-Time Scoring)

## Overview
This project implements a **LAN-based quiz game** using **Unix sockets in C**. It demonstrates core networking concepts including **TCP sockets**, **I/O multiplexing with `select()`**, **server-side timers**, and **real-time scoring**. Multiple clients can connect simultaneously, receive timed multiple-choice questions (MCQs), and see a real-time leaderboard after the timer expires.

This project is built for **educational purposes** as part of the Network Programming course at Nepal College of Information Technology, Nepal.

---

## Features
- **Unix Sockets (C)**: Uses POSIX TCP sockets (`socket`, `bind`, `listen`, `accept`, `send`, `recv`)
- **Multiple Clients**: Handles up to 5 concurrent players using `select()` for I/O multiplexing
- **Timed MCQs**: Each question has a fixed time limit (server-controlled)
- **Real-Time Scoring**: Scores are updated immediately and a leaderboard is broadcast after the timer
- **Server Authority**: All scoring logic resides on the server for correctness
- **Simple & Console-Based**: Runs entirely in terminal; no GUI required

---

## Project Structure
quiz_game/

│── server.c # Server program

│── client.c # Client program

│── questions.txt # Optional: quiz questions

│── README.md # This file


---

## Requirements
- GCC compiler
- Unix-like system (Linux, macOS, or GitHub Codespaces)
- Network access within the LAN

---

## Compilation

Open a terminal in the `quiz_game/` directory and run:

```bash
gcc server.c -o server
gcc client.c -o client


Running the Project

Start the server (Terminal 1):

./server


Server waits for clients and starts the quiz when the first client connects.

Connect a client (Terminal 2, 3, etc.):

./client


The client receives the question, enters the answer (A/B/C/D), and sees the final leaderboard after the timer expires.

Important: This project is not HTTP-based; ignore any GitHub Codespaces browser errors (502). Run in terminal only.

How It Works

Server:

Opens a TCP socket on port 8080

Accepts multiple clients (max 5)

Sends the question to each connected client

Starts timer when the first client connects

Receives answers and updates scores

Broadcasts leaderboard when time is up

Client:

Connects to server’s TCP port

Receives question and options

Submits answer

Receives final score and leaderboard

Example

Server Terminal:

Quiz Server running on port 8080
Quiz started
Time up! Sending leaderboard...


Client Terminal:

Q1: What is the capital of Nepal?
A) Pokhara
B) Kathmandu
C) Lalitpur
D) Biratnagar

Your answer (A/B/C/D): B

--- Leaderboard ---
Player1 : 10

Key Concepts Demonstrated

TCP Socket Programming: Reliable connection-oriented communication

I/O Multiplexing: Handling multiple clients with select()

Server-Side Timer: Fair timed MCQ implementation

Real-Time Score Management: Server maintains authoritative leaderboard

Basic Security: Clients cannot alter scores; server validates all input

Future Improvements

Load multiple questions from a file

Support threaded clients (pthread) for scalability

Extend leaderboard to multiple rounds

Optional GUI using GTK or Qt

Authors

Group Leader: [Mehfuz Alam, 211724, mehfuz.211724@ncit.edu.np]

Member 2: [Subash Magar, 211735, subash.211735@ncit.edu.np] 

Member 3: [Ashok Bhujel, 211705, ashok.211705@ncit.edu.np] 
