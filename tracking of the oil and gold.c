#include <stdio.h>
#include <stdlib.h>

struct Trade {
    int id;
    char name[20];
    float buyPrice;
    float sellPrice;
    int quantity;
    float profit;
    struct Trade *next;
};

struct Trade *head = NULL;

static void discardInputLine(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int readInt(const char *prompt, int *value) {
    printf("%s", prompt);

    if (scanf("%d", value) != 1) {
        printf("Invalid input. Please enter a whole number.\n");
        discardInputLine();
        return 0;
    }

    discardInputLine();
    return 1;
}

static int readFloat(const char *prompt, float *value) {
    printf("%s", prompt);

    if (scanf("%f", value) != 1) {
        printf("Invalid input. Please enter a number.\n");
        discardInputLine();
        return 0;
    }

    discardInputLine();
    return 1;
}

void addTrade(void) {
    struct Trade *newTrade = malloc(sizeof(struct Trade));

    if (newTrade == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    if (!readInt("\nEnter Trade ID: ", &newTrade->id)) {
        free(newTrade);
        return;
    }

    printf("Enter Asset (Gold/Oil): ");
    if (scanf("%19s", newTrade->name) != 1) {
        printf("Could not read the asset name.\n");
        discardInputLine();
        free(newTrade);
        return;
    }
    discardInputLine();

    if (!readFloat("Enter Buy Price: ", &newTrade->buyPrice)) {
        free(newTrade);
        return;
    }

    if (!readFloat("Enter Sell Price: ", &newTrade->sellPrice)) {
        free(newTrade);
        return;
    }

    if (!readInt("Enter Quantity: ", &newTrade->quantity)) {
        free(newTrade);
        return;
    }

    newTrade->profit =
        (newTrade->sellPrice - newTrade->buyPrice) * newTrade->quantity;

    newTrade->next = head;
    head = newTrade;

    printf("\nTrade added successfully!\n");
}

void displayTrades(void) {
    struct Trade *temp = head;

    if (temp == NULL) {
        printf("\nNo trading records found.\n");
        return;
    }

    printf("\n------ TRADING RECORDS ------\n");

    while (temp != NULL) {
        printf("\nTrade ID: %d", temp->id);
        printf("\nAsset: %s", temp->name);
        printf("\nBuy Price: %.2f", temp->buyPrice);
        printf("\nSell Price: %.2f", temp->sellPrice);
        printf("\nQuantity: %d", temp->quantity);
        printf("\nProfit/Loss: %.2f\n", temp->profit);

        temp = temp->next;
    }
}

void searchTrade(void) {
    int id;
    struct Trade *temp = head;

    if (!readInt("\nEnter Trade ID to search: ", &id)) {
        return;
    }

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nTrade Found!\n");
            printf("Asset: %s\n", temp->name);
            printf("Profit/Loss: %.2f\n", temp->profit);
            return;
        }

        temp = temp->next;
    }

    printf("\nTrade not found!\n");
}

void totalProfit(void) {
    struct Trade *temp = head;
    float total = 0.0f;

    while (temp != NULL) {
        total += temp->profit;
        temp = temp->next;
    }

    printf("\nTotal Profit/Loss: %.2f\n", total);
}

void freeTrades(void) {
    struct Trade *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int choice;

    do {
        printf("\n===== GOLD AND OIL TRADING TRACKER =====\n");
        printf("1. Add Trade\n");
        printf("2. Display Trades\n");
        printf("3. Search Trade\n");
        printf("4. Total Profit/Loss\n");
        printf("5. Exit\n");

        if (!readInt("Enter your choice: ", &choice)) {
            if (feof(stdin)) {
                break;
            }
            continue;
        }

        switch (choice) {
            case 1:
                addTrade();
                break;

            case 2:
                displayTrades();
                break;

            case 3:
                searchTrade();
                break;

            case 4:
                totalProfit();
                break;

            case 5:
                printf("\nThank you for using the tracker!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 5);

    freeTrades();
    return 0;
}