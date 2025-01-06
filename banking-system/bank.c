
/**
 * This thing took hours to make  and debugbruh so i gotta put my name here + i code on a phone my fingers hurts off
 * Author: Pratik12350 on Github
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h> // For  windowss
#else
#include <termios.h>
#endif

#define MAX_ACCOUNTS 10
#define MAX_TXNS 30

typedef struct {
  int id;
  char type; // TXN DEPOSIT (+) / TXN WITHDRAWL (-)
  float amount;
  float bal;
  int date[3];
} Txn;

typedef struct {
  int id;
  char holder[40];
  float bal;
  Txn txn[MAX_TXNS]; // not gonna make it too complex ;
  int txnCount;
  char password[16];
} Account;

void clearScreen();
void waitForM();
void saveAccount(Account *acc, int *accCount);
void loadAccounts(Account *acc, int *accCount);
void createAccount(Account *accs, int *accCount);
void sendMoney(Account *accs, int *accCount);
void depositMoney(Account *accs, int *accCount);
void withdrawMoney(Account *accs, int *accCount);
void checkBalance(Account *accs, int *accCount);
void showTransactions(Account *accs, int *accCount);

int main(int argc, char *argv[]) {
  Account accs[MAX_ACCOUNTS];
  int accCount = 0;
  loadAccounts(accs, &accCount);

  int optionSelected;
  do {
    clearScreen();
    printf("WELCOME TO BANK OF GAYS 💅🏻🗣️\n\n");
    printf("1. Create account\n");
    printf("2. Check balance\n");
    printf("3. Deposit money\n");
    printf("4. Withdraw money\n");
    printf("5. Send money\n");
    printf("6. Show transactions\n");
    printf("7. Exit\n");
    printf("\n");
    printf("Accounts loaded: %d\n", accCount);
    printf("Select option: ");
    scanf("%d", &optionSelected);

    while (getchar() != '\n')
      ;

    switch (optionSelected) {
    case 1:
      createAccount(accs, &accCount);
      break;
    case 2:
      checkBalance(accs, &accCount);
      break;
    case 3:
      depositMoney(accs, &accCount);
      break;
    case 4:
      withdrawMoney(accs, &accCount);
      break;
    case 5:
      sendMoney(accs, &accCount);
      break;
    case 6:
      showTransactions(accs, &accCount);
      break;
    case 7:
      clearScreen();
      printf("Bank is closing! Bye bye hoomans!\n");
      break;
    default:
      printf("Invalid option!\n");
    }

    if (optionSelected == 7) {
      exit(0);
    }
  } while (optionSelected != 7);
  return 0;
}

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif /* ifdef _WIN32 */
}

void waitForM() {
  int input;

  printf("\nPress 'M' to go back to the main menu... ");

#ifdef _WIN32
  do {
    input = _getch();
  } while (input != 'M' && input != 'm');
#else

  // only God knows wtf i did here but it works so i am not gonna touch it.
  struct termios oldt, newt;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  do {
    input = getchar();
  } while (input != 'M' && input != 'm');

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void saveAccount(Account *accs, int *accCount) {
  FILE *fptr = fopen("accounts.dat", "wb");
  if (!fptr) {
    printf("Failed to open data file!\n");
    return;
  }

  fwrite(accCount, sizeof(int), 1, fptr);
  fwrite(accs, sizeof(Account), *accCount, fptr);

  fclose(fptr);
  // printf("[ INFO ] - Account saved!\n");
}

void loadAccounts(Account *accs, int *accCount) {
  FILE *fptr = fopen("accounts.dat", "rb");
  if (!fptr) {
    printf("Failed to open data file!\n");
    *accCount = 0;
    return;
  }

  fread(accCount, sizeof(int), 1, fptr);
  fread(accs, sizeof(Account), *accCount, fptr);

  fclose(fptr);
  printf("[ INFO ] - Accounts loaded!\n");
}

void checkBalance(Account *accs, int *accCount) {
  int accID;
  char password[16];

  printf("\nEnter account ID: ");
  scanf("%d", &accID);

  if (accID <= 0 || accID > *accCount) {
    printf("Invalid account ID!");
    waitForM();
    return;
  }

  while (getchar() != '\n')
    ;
  printf("Enter your password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  int accIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == accID && strcmp(accs[i].password, password) == 0) {
      accIndex = i;
      break;
    }
  }

  if (accIndex == -1) {
    printf("ID or Password is incorrect.");
    waitForM();
    return;
  }

  printf("\nHolder's name: %s\n", accs[accIndex].holder);
  printf("Current balance: %.2f\n", accs[accIndex].bal);
  waitForM();
  return;
}

void attachDate(Txn *txn) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  txn->date[0] = tm.tm_mday;
  txn->date[1] = tm.tm_mon + 1;
  txn->date[2] = tm.tm_year + 1900;
}

void createAccount(Account *accs, int *accCount) {
  if (*accCount >= MAX_ACCOUNTS) {
    printf("[ ERROR ] – Too many accounts");
    waitForM();
    return;
  }
  int id = *accCount + 1;
  char holder[40];
  char password[16];
  float balance;
  int txnCount = 0;

  while (getchar() != '\n')
    ;
  printf("Enter your name: ");
  fgets(holder, sizeof(holder), stdin);
  holder[strcspn(holder, "\n")] = '\0';

  printf("Enter balance: ");
  scanf("%f", &balance);

  while (getchar() != '\n')
    ;
  printf("Create your password: ");
  fgets(password, sizeof(password),
        stdin); // no big security things because its a small project
  password[strcspn(password, "\n")] = '\0';

  Txn txn;

  txn.id = 0;
  txn.bal = balance;
  txn.type = '+';
  txn.amount = balance;
  attachDate(&txn);

  Account acc;
  acc.id = id;
  strcpy(acc.holder, holder);
  strcpy(acc.password, password);
  acc.bal = balance;
  acc.txnCount = txnCount;
  acc.txn[0] = txn;

  accs[*accCount] = acc;
  (*accCount)++;

  saveAccount(accs, accCount);

  printf("[ INFO ] - Account with ID %d created successfully\n", acc.id);
  waitForM();
  return;
}

void sendMoney(Account *accs, int *accCount) {
  int recvAccID, amount;
  int senderAccID;
  char password[16];

  printf("\nEnter YOUR account ID: ");
  scanf("%d", &senderAccID);

  if (senderAccID > *accCount || senderAccID <= 0) {
    printf("Invalid account ID!");
    waitForM();
    return;
  }

  while (getchar() != '\n')
    ;
  printf("Enter your password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  int senderAccIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == senderAccID && strcmp(accs[i].password, password) == 0) {
      senderAccIndex = i;
      break;
    }
  }

  if (senderAccIndex == -1) {
    printf("ID or Password is incorrect.");
    waitForM();
    return;
  }

  printf("\nEnter receiver's account ID: ");
  scanf("%d", &recvAccID);

  if (recvAccID > *accCount) {
    printf("Invalid account ID!");
    waitForM();
    return;
  }

  printf("Enter amount you want to deposit: ");
  scanf("%d", &amount);

  if (amount > 100000) {
    printf("Amount too big. Please deposit in small chunks.");
    waitForM();
    return;
  }

  if (accs[senderAccIndex].bal < amount) {
    printf("Not enough balance.\n");
    waitForM();
    return;
  }

  int recvAccIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == recvAccID) {
      recvAccIndex = i;
      break;
    }
  }

  if (recvAccIndex == -1) {
    printf("Account not found.");
    waitForM();
    return;
  }

  Txn recvTxn;

  recvTxn.id = accs[recvAccIndex].txnCount + 1;
  recvTxn.type = '+';
  recvTxn.amount = amount;
  recvTxn.bal = accs[recvAccIndex].bal + amount;
  attachDate(&recvTxn);

  Txn txn;

  txn.id = accs[senderAccIndex].txnCount + 1;
  txn.type = '-';
  txn.amount = amount;
  txn.bal = accs[senderAccIndex].bal - amount;
  attachDate(&txn);

  accs[recvAccIndex].bal += amount;
  accs[recvAccIndex].txn[accs[recvAccIndex].txnCount] = recvTxn;
  accs[recvAccIndex].txnCount++;

  accs[senderAccIndex].bal -= amount;
  accs[senderAccIndex].txn[accs[senderAccIndex].txnCount] = txn;
  accs[senderAccIndex].txnCount++;

  saveAccount(accs, accCount);
  printf("Rs. %d has been sent to %s's account.", amount,
         accs[recvAccIndex].holder);
  waitForM();
  return;
}

void withdrawMoney(Account *accs, int *accCount) {
  int accID, amount;
  char password[16];

  printf("\nEnter account ID: ");
  scanf("%d", &accID);

  if (accID <= 0 || accID > *accCount) {
    printf("Invalid account ID!");
    waitForM();
    return;
  }

  while (getchar() != '\n')
    ;
  printf("Enter your password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  int accIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == accID && strcmp(accs[i].password, password) == 0) {
      accIndex = i;
      break;
    }
  }

  if (accIndex == -1) {
    printf("ID or Password is incorrect.");
    waitForM();
    return;
  }

  printf("Enter amount you want to withdraw: ");
  scanf("%d", &amount);

  if (amount > 100000) {
    printf("Amount too big. Please withdraw in small chunks.");
    waitForM();
    return;
  }

  if (accs[accIndex].bal < amount) {
    printf("Not enough balance.\n");
    waitForM();
    return;
  }

  Txn txn;

  txn.id = accs[accIndex].txnCount + 1;
  txn.type = '-';
  txn.amount = amount;
  txn.bal = accs[accIndex].bal - amount;
  attachDate(&txn);

  accs[accIndex].bal -= amount;
  accs[accIndex].txn[accs[accIndex].txnCount + 1] = txn;

  saveAccount(accs, accCount);
  printf("Rs. %d has been withdrawn from %s's account.", amount,
         accs[accIndex].holder);
  waitForM();
  return;
}

void depositMoney(Account *accs, int *accCount) {
  int accID, amount;
  // char password[16];

  printf("\nEnter account ID: ");
  scanf("%d", &accID);

  if (accID <= 0 || accID > *accCount) {
    printf("Invalid account ID!");
    waitForM();
    return;
  }

  int accIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == accID) {
      accIndex = i;
      break;
    }
  }

  if (accIndex == -1) {
    printf("Account not found.");
    waitForM();
    return;
  }

  printf("Enter amount you want to deposit: ");
  scanf("%d", &amount);

  if (amount > 100000) {
    printf("Amount too big. Please deposit in small chunks.");
    waitForM();
    return;
  }

  Txn txn;

  txn.id = accs[accIndex].txnCount + 1;
  txn.type = '+';
  txn.amount = amount;
  txn.bal = accs[accIndex].bal + amount;
  attachDate(&txn);

  accs[accIndex].bal += amount;
  accs[accIndex].txn[accs[accIndex].txnCount + 1] = txn;

  saveAccount(accs, accCount);
  printf("Rs. %d has been deposited to %s's account.", amount,
         accs[accIndex].holder);
  waitForM();
  return;
}

void printTransactionDetails(Txn txn) {
  printf("\n=============================================\n");
  printf(" Transaction ID: %d\n", txn.id);
  printf(" Type: %-10c\n", txn.type);
  printf(" Amount: $%-10.2f\n", txn.amount);
  printf(" Balance After Transaction: $%-10.2f\n", txn.bal);
  printf(" Date: %02d/%02d/%04d\n", txn.date[0], txn.date[1], txn.date[2]);
  printf("=============================================\n");
}

void showTransactions(Account *accs, int *accCount) {
  int accID;
  char password[16];

  printf("\nEnter account ID: ");
  scanf("%d", &accID);

  if (accID <= 0 || accID > *accCount) {
    printf("[ERROR] Invalid account ID!\n");
    waitForM();
    return;
  }

  while (getchar() != '\n')
    ;

  printf("Enter your password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  int accIndex = -1;
  for (int i = 0; i < *accCount; i++) {
    if (accs[i].id == accID && strcmp(accs[i].password, password) == 0) {
      accIndex = i;
      break;
    }
  }

  if (accIndex == -1) {
    printf("[ERROR] Incorrect ID or password.\n");
    waitForM();
    return;
  }

  Account acc = accs[accIndex];

  clearScreen();
  printf("\n=============================================\n");
  printf(" Account ID: %d\n", acc.id);
  printf(" Account Holder: %s\n", acc.holder);
  printf("=============================================\n");

  /*
    for (int i = 0; i < acc.txnCount; i++) {
        printTransactionDetails(acc.txn[i]);
    printf("1");
    }*/

  int txnCounter = 0;
  do {
    printTransactionDetails(acc.txn[txnCounter]);
    txnCounter++;
  } while (txnCounter < acc.txnCount);

  waitForM();
}
