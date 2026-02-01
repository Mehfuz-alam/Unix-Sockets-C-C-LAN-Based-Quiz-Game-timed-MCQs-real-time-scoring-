# Network Programming Course – Project Proposal

## Project Title
**LAN-Based Quiz Game (Timed MCQs, Real-Time Scoring)**

---

## Group Details
- **Group Leader:** Mehfuz Alam, 211724, mehfuz.211724@ncit.edu.np  
- **Member 2:** Subash Magar, 211735, subash.211735@ncit.edu.np  
- **Member 3:** Ashok Bhujel, 211705, ashok.211705@ncit.edu.np  

---

## Project Overview
The proposed project is a **multi-player LAN-based quiz game** implemented using **Unix sockets in C**. The server hosts multiple-choice questions (MCQs), manages timers for fairness, and maintains real-time scoring. Clients connect over the LAN, submit answers, and receive a leaderboard once the timer expires.

This project demonstrates fundamental networking concepts taught in the course, including TCP sockets, I/O multiplexing, server-side control, and basic client-server security.

---

## Objectives
1. Implement a **TCP client-server architecture** using Unix sockets.  
2. Handle **multiple clients** simultaneously with `select()` for I/O multiplexing.  
3. Provide **timed MCQs** with a server-controlled timer.  
4. Maintain **real-time scoring** and broadcast a leaderboard to clients.  
5. Ensure **server-side authority** to prevent client manipulation of scores.  
6. Demonstrate **basic networking concepts** for educational evaluation.

---

## Scope & Limitations
- **Scope:** Single-question quiz with multiple clients; real-time scoring; console-based interaction.  
- **Limitations:** No GUI; currently supports 1 question only; server and clients must be on the same LAN.

---

## Technical Approach

### Server
- Create a TCP socket on port 8080  
- Accept multiple client connections (max 5)  
- Start quiz timer when the first client connects  
- Receive answers, validate them, and update scores  
- Broadcast final leaderboard when timer expires  

### Client
- Connect to the server over LAN  
- Receive the quiz question  
- Submit answer  
- Receive final score and leaderboard  

---

## Tools & Platform
- **Programming Language:** C  
- **Sockets:** Unix TCP sockets  
- **Compiler:** GCC  
- **Platform:** Linux / macOS / GitHub Codespaces  

---

## Expected Deliverables
1. **Complete source code:** `server.c` and `client.c`  
2. **README.md:** Build instructions, usage, project description  
3. **Demo:** Terminal-based demonstration with at least one client  
4. **Presentation:** Explanation of networking concepts and project workflow  

---

## Timeline
- **Proposal Submission:** February 5, 2026  
- **Development & Testing:** February 6–12, 2026  
- **Final Submission & Demo:** [Date to be announced]  

---

## References
- Beej’s Guide to Network Programming (TCP Sockets)  
- Unix Socket Programming Documentation  
- Class notes & Network Programming lectures
