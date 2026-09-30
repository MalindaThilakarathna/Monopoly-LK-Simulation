# MONOPOLY-LK: Sri Lankan Economic & Board Simulation

An autonomous multi-agent economic simulation game developed in C, modeling a 40-square Monopoly board integrated with Sri Lankan macroeconomic mechanisms, commercial banking, dynamic insurance policies, and regional market shifts.

Developed as the individual course project for **SCS 1301: Data Structures and Program Design using C** at the **University of Colombo School of Computing (UCSC)**.

---

## 🌟 Key Features

### 1. Autonomous AI Player Decision Engines
The simulation runs up to 500 rounds completely autonomously without human intervention, featuring four distinct investor profiles:
* **Aggressive Investor:** High-risk, rapid monopoly acquisition, aggressive auction bidding (up to 120% valuation), and fast building/hotel construction.
* **Conservative Banker:** Low-risk, maintains high cash reserves (≥ 50%), avoids debt, prioritizes railways/utilities, and secures comprehensive insurance.
* **Risk Taker:** Leverages maximum borrowing capacity, bids aggressively in auctions, and rapidly upgrades properties.
* **Opportunistic Trader:** Evaluates projected returns against borrowing costs, timing investments around economic cycles and government policies.

### 2. Sri Lankan Financial & Economic Mechanics
* **Commercial Banking (Bank of Ceylon):** Secured collateral loans (up to 75% mortgage value), compound interest accumulation, loan-locking, and foreclosure procedures.
* **Insurance System:** Policies from Sri Lanka Insurance & Ceylinco Insurance (Basic, Comprehensive, and Business Interruption) covering disasters like fires, floods, and riots.
* **Macroeconomic Fluctuation:** Dynamic inflation/deflation (-3% to +12%), property depreciation over time, and regular maintenance requirements.
* **Event Decks:** 20 National Event Cards and Regional Development Cards (e.g., Southern Tourism Boom, Port City Expansion, Tea Export Boom).

---

## 📁 Project Structure

```text
├── types.h        # Enums, structs, and core data types
├── board.h/c      # Board initialization and movement logic
├── player.h/c     # Autonomous player decision-making algorithms
├── finance.h/c    # Banking, loans, insurance, depreciation, and taxation
├── event.h/c      # National/Regional events and government regulations
├── game.h/c       # Main game loop, simulation engine, and state management
├── main.c         # Program entry point and execution setup
├── .gitignore     # Git ignore rules
└── README.md      # Project documentation