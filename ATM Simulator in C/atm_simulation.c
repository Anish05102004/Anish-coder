#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100
#define PIN 1234  // Default PIN

// Structure for transaction
typedef struct {
    char type[20];
    float amount;
    char receiver[30];
    char datetime[30];
} Transaction;

float balance = 1000.0;
Transaction history[MAX_TRANSACTIONS];
int history_count = 0;

// Function to get current date and time as string
void get_current_datetime(char* buffer, int size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%d-%m-%Y %H:%M:%S", t);
}

// Record transaction
void record_transaction(const char* type, float amount, const char* receiver) {
    if (history_count < MAX_TRANSACTIONS) {
        strcpy(history[history_count].type, type);
        history[history_count].amount = amount;
        if (receiver != NULL)
            strcpy(history[history_count].receiver, receiver);
        else
            strcpy(history[history_count].receiver, "-");

        get_current_datetime(history[history_count].datetime, sizeof(history[history_count].datetime));
        history_count++;
    }
}

// Authenticate user by PIN
int authenticate() {
    int entered_pin, attempt = 0;

    while (attempt < 3) {
        printf("Enter your 4-digit PIN: ");
        scanf("%d", &entered_pin);

        if (entered_pin == PIN) {
            printf("Login successful.\n");
            return 1;
        } else {
            printf("Incorrect PIN. Try again.\n");
            attempt++;
        }
    }

    printf("Too many failed attempts. Access denied.\n");
    return 0;
}

// Check balance
void check_balance() {
    printf("Current Balance: %.2f Rupees\n", balance);
    record_transaction("Check Balance", balance, NULL);  // Log actual balance
}

// Deposit money
void deposit_money() {
    float amount;
    printf("Enter amount to deposit (in Rupees): ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Deposit successful: %.2f Rupees added.\n", amount);
        record_transaction("Deposit", amount, NULL);
    } else {
        printf("Invalid amount entered.\n");
    }
}

// Withdraw money
void withdraw_money() {
    float amount;
    printf("Enter amount to withdraw (in Rupees): ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Withdrawal successful: %.2f Rupees withdrawn.\n", amount);
        record_transaction("Withdraw", amount, NULL);
    } else {
        printf("Invalid amount or insufficient balance.\n");
    }
}

// Transfer money
void transfer_money() {
    float amount;
    char receiver[30];

    printf("Enter recipient account number: ");
    scanf("%s", receiver);

    printf("Enter amount to transfer (in Rupees): ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        printf("Transfer successful: %.2f Rupees sent to %s.\n", amount, receiver);
        record_transaction("Transfer", amount, receiver);
    } else {
        printf("Invalid amount or insufficient balance.\n");
    }
}

// View transaction history
void view_history() {
    printf("\nTransaction History:\n");
    printf("------------------------------------------------------------\n");

    if (history_count == 0) {
        printf("No transactions available.\n");
    } else {
        for (int i = 0; i < history_count; i++) {
            printf("%d. %s - %.2f Rupees", i + 1, history[i].type, history[i].amount);
            if (strcmp(history[i].receiver, "-") != 0)
                printf(" to %s", history[i].receiver);
            printf(" on %s\n", history[i].datetime);
        }
    }

    printf("------------------------------------------------------------\n");
}

// Display menu
void display_menu() {
    printf("\nATM MENU:\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Transfer\n");
    printf("5. View Transaction History\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    int choice;

    printf("Welcome to the ATM Simulator\n");

    if (!authenticate()) {
        return 0;
    }

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: check_balance(); break;
            case 2: deposit_money(); break;
            case 3: withdraw_money(); break;
            case 4: transfer_money(); break;
            case 5: view_history(); break;
            case 6: printf("Thank you for using the ATM. Goodbye.\n"); break;
            default: printf("Invalid choice. Please select a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}



//cd "C:\Users\anish\OneDrive\Desktop\ATM Simulator in C"
//gcc atm_simulation.c -o atm_simulation
//.\atm_simulation
