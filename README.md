# Crypto Trading Platform

## Overview
The Crypto Trading Platform is a console-based application that simulates a cryptocurrency exchange. Users can interact with the platform to place bids and asks, view market statistics, and manage their virtual wallets. This project demonstrates the practical application of various C++ concepts such as object-oriented programming, data structures, and file handling.

## Features
- **User Menu**: A menu-driven interface for ease of interaction.
- **Market Statistics**: View current market statistics including the number of asks, highest ask price, lowest ask price, and average ask price.
- **Trading Functionality**: Place buy (bid) and sell (ask) orders.
- **Wallet Management**: Display the current status of the user's wallet.
- **Timeframe Navigation**: Move to the next time frame to simulate market progression.


## Setup and Installation
1. **Clone the Repository**:
    ```sh
    git clone https://github.com/AryanSahu021/Crypto-Trading-Platform.git
    cd Crypto-Trading-Platform
    ```

2. **Build the Project**:
    Open the project in Visual Studio and build the solution:
    ```sh
    CryptoTradingPlatform.sln
    ```

## Usage
1. **Run the Application**:
    After building, run the executable:
    ```sh
    ./CryptoTradingPlatform
    ```

2. **Navigate the Menu**:
    - **Print Help**: Get information on how to use the platform.
    - **Print Exchange Stats**: View current market statistics.
    - **Place an Ask**: Enter details to place a sell order.
    - **Place a Bid**: Enter details to place a buy order.
    - **Print Wallet**: View the current status of your wallet.
    - **Go to Next Timeframe**: Advance the simulation and process orders.

## Example Interaction
```sh
Welcome!!
Choose from the following options:
1- Print Help
2- Print Exchange stats
3- Place an ask
4- Place a bid
5- Print Wallet
6- Go to next timeframe
============================
Type in 1-6