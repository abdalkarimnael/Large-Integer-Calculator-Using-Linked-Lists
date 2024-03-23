/////////Project 1 DS --- Name:Abdalkarim Eiss --- ID: 1200015 ---- Section: 1
///CALCULATOR for large integers
////////Note: In the input file the numbers divided by new line. This program is writen in Clion.
////////Libraries
#include <stdio.h>
#include <malloc.h>
#include "stdlib.h"
#include "math.h"

struct node;
typedef struct node *ptr;  ///to create an alias name
struct node {  //////Define the structure of the node
    int digit;   /////////For each digit in the number
    ptr next;     /////Pointer to the next node
    ptr previous; /////Pointer to the previous node
};
typedef ptr LinkedList; ///to create an alias name
typedef ptr pos; ///to create an alias name

///insert function
void insert(LinkedList L, int x) {
    LinkedList newNode = (LinkedList) malloc(sizeof(struct node));
    pos t;
    if (L != NULL && newNode != NULL) {
        for (t = L; t->next != NULL; t = t->next); //////////////check and move cursor
        newNode->next = t->next;
        t->next = newNode;
        newNode->previous = t;
        newNode->digit = x;
    }
}

////To check if the list is empty or not
int isEmpty(LinkedList L) {
    return (L->next == NULL);
}

/////Function to Print the list
/*void printList(LinkedList L) {
    if (L != NULL) {
        for (int i = 0; i <= 2; i++) {
            printf("-\t-\t-\t-\t");
        }
        printf("\n");
        printf("|||<--| | <-->");
        pos t = L->next;
        while (t != NULL) {
            printf(" | %d | <--> ", t->digit);
            t = t->next;
        }
        printf("|||\n");
    }
}*/

void printList(LinkedList L) {
    if (L != NULL) {
        for (int i = 0; i <= 2; i++) {
            printf("-\t-\t-\t-\t");
        }
        printf("\n");
        pos t = L->next;
        while (t != NULL) {
            printf("%d", t->digit);
            t = t->next;
        }
        printf("\n");
    }
}
///Insert after header
void insertAfterHeader(LinkedList L, int sum) {
    LinkedList newNode = (LinkedList) malloc(sizeof(struct node));
    pos t = L;
    if (L != NULL && newNode != NULL) {
        newNode->next = t->next;
        t->next = newNode;
        newNode->previous = t;
        newNode->digit = sum;
    }
}

///Function to check the number of digits after addition
int NumOfDigits(int x) {
    int counter = 0; /// Counter (the number of digits)
    while (x != 0) {
        x = x / 10;
        counter++;
    }
    if (counter == 2) {
        return 1;
    } else {
        return 0;
    }

}

//////Function to get the size of list
int getSize(LinkedList L) {
    pos t;
    int counter = 0;
    if (L != NULL) {
        for (t = L->next; t != NULL; t = t->next) {
            counter++;
        }
        return counter;
    } else {
        return 0;
    }
}

///////Addition function ---Perfect
void addition(LinkedList L1, LinkedList L2, LinkedList sum) {
    pos t1, t2; ///Pointers in two lists
    int result;///To set the result
    int firstdig; ///To set the first digit ---- from right
    int seconddig; ///To set the second digit ---- from right
    if (L1 != NULL && L2 != NULL) {
        for (t1 = L1; t1->next != NULL; t1 = t1->next); //////////////check and move cursor
        for (t2 = L2; t2->next != NULL; t2 = t2->next); //////////////check and move cursor
        while (t1 != L1 && t2 != L2) {

            result = t1->digit + t2->digit;
            int special; ///Special int to check the

            if (NumOfDigits(result) == 1) {

                firstdig = result % 10; ////To get the first digit
                seconddig = result / 10; ///To get the second digit
                ///To check if two digits and with another number from the previous number
                if (special == 1) {
                    insertAfterHeader(sum, firstdig + seconddig);
                } else {
                    insertAfterHeader(sum, firstdig);
                }
                special = 1; /////////////////To label the two digits
            }
                /////To check if two digits and in the last digit for sum
            else if (special == 1) {
                if (t1->previous == L1 && t2->previous == L2) {
                    insertAfterHeader(sum, 1);
                } else {
                    insertAfterHeader(sum, t1->digit + t2->digit + seconddig);
                }
                special = 0;  ////Update the specail
            } else {
                insertAfterHeader(sum, t1->digit + t2->digit);
            }
            t1 = t1->previous;
            t2 = t2->previous;
            /////To add the last carry into the sum list  ///////////////////
            if ((NumOfDigits(result) == 1) && t1 == L1 && t2 == L2) {
                insertAfterHeader(sum, seconddig);
            }
        }
    } else {
        printf("\nThere is an error in the addition operation!!\n");
    }
}

///Subtraction function ---Perfect
void sub(LinkedList L1, LinkedList L2, LinkedList Sub) {
    pos t1, t2;
    int result;
    if (L1 != NULL && L2 != NULL) {
        for (t1 = L1; t1->next != NULL; t1 = t1->next); //////////////check and move cursor
        for (t2 = L2; t2->next != NULL; t2 = t2->next); //////////////check and move cursor
        while (t1 != L1 && t2 != L2) {
            ////To check the validity between the two digits
            if ((t1->digit < t2->digit) && (t1->previous != L1 && t2->previous != L2)) {
                /////add 10 tom the number (borrowing)
                t1->digit = t1->digit + 10;
                /////sub 1 from the previous digit
                t1->previous->digit = t1->previous->digit - 1;
                result = t1->digit - t2->digit; ////To put the result of each sub operation
                insertAfterHeader(Sub, result);
            }
                /////Normal case
            else {
                result = t1->digit - t2->digit; ////To put the result of each sub operation
                insertAfterHeader(Sub, result);
            }
            ////UPDATE the cursor location
            t1 = t1->previous;
            t2 = t2->previous;
        }
    } else {
        printf("\nThere is an error in the subtraction operation!!\n");
    }
}

///////Delete from the list
void delete(LinkedList L) {
    pos t;
    if (L != NULL) {
        for (t = L; t->next != NULL; t = t->next);
        if (t->previous != NULL) {
            t->previous->next = NULL;
        } else {
            ////// If the deleted node was the only one node
            L = NULL;
        }
        free(t);
    }
}

//////////To get the greater number
int greater(LinkedList L1, LinkedList L2) {
    while (L1 != NULL && L2 != NULL) {
        if (L1->digit > L2->digit) {
            return 1;
        } else if (L1->digit < L2->digit) {
            return -1;
        }
        L1 = L1->next;
        L2 = L2->next;
    }
    if (L1 == NULL && L2 != NULL) {
        return -1; //// Second number is greater
    } else if (L1 != NULL && L2 == NULL) {
        return 1; //// First number is greater
    }

    // Both numbers are equal
    return 0;
}

//////To convert the number to minus
void ConvertOpposite(LinkedList L) {
    pos t = L->next;
    while (t != NULL) {
        t->digit = 0 - t->digit;
        t = t->next;
    }
}

///Mul
///////////////Function for multiplication operation
void mul(LinkedList L1, LinkedList L2, LinkedList Mul) {
    pos t1, t2;
    ///struct node* array[100];
    ///pos t3;
    ///To set the result of multiplication
    LinkedList Res1 = (LinkedList) malloc(sizeof(struct node));
    Res1->next = NULL;
    Res1->previous = NULL;
    ///To set the result of multiplication
    LinkedList Res2 = (LinkedList) malloc(sizeof(struct node));
    Res2->next = NULL;
    Res2->previous = NULL;
    //////  pos t3=Mul; ///////For mul operation
    int result; ///To put the result
    int special = 0;
    int fDigit; ////For L1
    int sDigit;/////For L2
    if (L1 != NULL && L2 != NULL) {
        for (t1 = L1; t1->next != NULL; t1 = t1->next); //////////////check and move cursor
        for (t2 = L2; t2->next != NULL; t2 = t2->next); //////////////check and move cursor
        //////should Pin t2 and move t1
        while (t1 != L1 && t2 != L2) {
            result = t2->digit * t1->digit;
            if (special == 1) {
                insertAfterHeader(Res2, result);
            } else {
                insertAfterHeader(Res1, result);
            }
            t1 = t1->previous;
            if (t1 == L1) {
                for (t1 = L1; t1->next != NULL; t1 = t1->next); //////////////check and move cursor
                t2 = t2->previous;
                special = 1;
            }
        }
        int size1 = getSize(L1) + getSize(L2) - getSize(Res1); /////////size for zeros on the left
        ///For zeros
        for (int i = 0; i < size1; i++) {
            insertAfterHeader(Res1, 0);
        }
        ///For zero
        insert(Res2, 0); /////Before number
        int size2 = getSize(L1) + getSize(L2) - getSize(Res2); /////////size for zeros on the left
        ///For zeros
        for (int i = 0; i < size2; i++) {
            insertAfterHeader(Res2, 0);
        }

        pos t3, t4; /////cursors
        for (t3 = Res1; t3->next != NULL; t3 = t3->next); //////////////check and move cursor
        for (t4 = Res2; t4->next != NULL; t4 = t4->next); //////////////check and move cursor
        int sum;
        int carry = 0;
        int S = getSize(Res2) - 1; ////Size of Result 1 to put on the loop
        ///printList(Res1);
        ///printList(Res2);
        addition(Res1, Res2, Mul);  ////Add the results

    }
}

/////////////////////Function for division operation
void Div(LinkedList L1, LinkedList L2, LinkedList remainder, LinkedList Ddiv) {
    pos t1, t2; ////Cursors
    t1 = L1->next;
    t2 = L2->next;  //////divisor
    LinkedList resOfMul = (LinkedList) malloc(sizeof(struct node));
    resOfMul->previous = NULL;
    resOfMul->next = NULL;
    ////Variables, because we need to get the Divisor
    int SizeOfDivisor = getSize(L2);
    int divisor;
    int resDivisor = 0;///To extract the divisor as integer
    if (L1 != NULL && L2 != NULL) {
        ////To get the Divisor
        while (t2 != NULL) {
            divisor = t2->digit * pow(10, SizeOfDivisor - 1); ////divisor______|```````
            resDivisor += divisor;
            SizeOfDivisor--;
            t2 = t2->next;
        }
        int result; ////////To put the result of division
        while (t1 != NULL) {
            result = t1->digit / divisor;
            insert(Ddiv, result);
            ////sub(Ddiv, remainder, )
            mul(Ddiv, L2, remainder);
            sub(L1, remainder, resOfMul);
            t1 = t1->next;
        }
        printList(resOfMul);

    } else {
        printf("\nSorry, There is an problem\n");
    }
}

////SaveToFile
void Save(LinkedList L, FILE *file) {
    if (L != NULL) {
        pos t = L->next;
        /////To check if the number is minus or not
        if (t->digit < 0) {
            fprintf(file, "-");
            ConvertOpposite(L);
        }
        while (t != NULL) {
            fprintf(file, "%d", t->digit);
            t = t->next;
        }
        fprintf(file, "\n");
    }
}

/////MAIN
int main() {
    //////////////////////  LOADING...
    /////////////////////////////////// WELCOME
    //////////////////////////////////////////////////////  TO the system
    ////List 1
    ////Header for the first list
    LinkedList L1 = (LinkedList) malloc(sizeof(struct node));
    L1->previous = NULL;
    L1->next = NULL;
    /////List 2
    /////Header for List2
    LinkedList L2 = (LinkedList) malloc(sizeof(struct node));
    L2->previous = NULL;
    L2->next = NULL;
    ///To set the result of addition
    LinkedList sum = (LinkedList) malloc(sizeof(struct node));
    sum->next = NULL;
    sum->previous = NULL;
    ///To set the result of subtraction
    LinkedList Sub = (LinkedList) malloc(sizeof(struct node));
    Sub->next = NULL;
    Sub->previous = NULL;
    ///To set the result of multiplication
    LinkedList Mul = (LinkedList) malloc(sizeof(struct node));
    Mul->next = NULL;
    Mul->previous = NULL;
    ///To set the result of division
    LinkedList Ddiv = (LinkedList) malloc(sizeof(struct node));
    Ddiv->next = NULL;
    Ddiv->previous = NULL;
    /////////To set the remainder of division
    LinkedList remainder = (LinkedList) malloc(sizeof(struct node));
    remainder->next = NULL;
    remainder->previous = NULL;
    //////
    FILE *file; ////to open the file as file on read mode
    FILE *out; ///To open a file to save the result on it on write mode
    char InfileName[50]; ///Input file name
    char OutfileName[50]; ///Output file name
    int IntDigit; ///To set the digit that read
    char e = '.'; /////for the loop
    int choice; ////To get the choice from user
    char Isread = 'n'; ////To check if the file is read or not
    int DifSize;////To put the size difference between two numbers
    int sizeOne;////size for the first list
    int sizeTwo;//////size for the second list
    char num1;
    char num2;
    int sign = 1; ////To use to convert to minus
    /////Instructions for user
    printf("\t\t------------------------------\n");
    printf("\t\t\b\b\bWELCOME TO THE LONG INTEGERS CALCULATOR SYSTEM\n");
    printf("\t\t------------------------------\n");
    printf("\t\t\t\t\t\tCreated by: A.N.A\n");
    //////for loop for the menu and system
    while (e != 'q') {
        /////Menu for the user
        printf("\nWhat do you need from the menu? \n\t1.Read from the file.\n\t2.Make Addition operation.");
        printf("\n\t3.Make Subtraction operation.\n\t4.Make Multiplication operation.\n\t5.Make Division operation.");
        printf("\n\t6.Save all operations that you have done to the output file.\n\t7.Exit.\n\tEnter: ");
        scanf("%d", &choice); ////To read the choice from user
        int counter = 0; //////counter for minus
        switch (choice) {
            case 1:  /////For read choice
                if (Isread == 'n') {
                    printf("\nPlease enter the input file name: ");
                    scanf("%s", InfileName);
                    file = fopen(InfileName, "r");
                    if (file == NULL) {
                        printf("\nThere is an error!!\n");
                        fclose(file);
                    } else {
                        Isread = 'y'; ////////To label the file as a read file
                        char charDig;  ////To store the integer that read
                        /////Loop to read from the file char by char
                        while ((charDig = fgetc(file)) != EOF) {
                            IntDigit = atoi(&charDig);   ////Convert from string to integer
                            if (charDig == '-') {
                                continue;
                            }
                            //////Special chr to specify the new line location
                            char prev;
                            if (charDig == '\n') {
                                prev = '\n';
                                continue;  ///If there is new line continue
                            } else {
                                if (prev == '\n') {
                                    insert(L2, IntDigit);
                                } else {
                                    insert(L1, IntDigit);
                                }
                            }

                        }
                        sizeOne = getSize(L1);
                        sizeTwo = getSize(L2);
                        DifSize = abs(sizeOne - sizeTwo);
                        ////reset
                        while (L1->next != NULL) {
                            delete(L1);
                        }
                        while (L2->next != NULL) {
                            delete(L2);
                        }
                    }
                    fclose(file);
                    //////////////////////////////////////////////////////////////////////Read again
                    file = fopen(InfileName, "r");
                    if (file == NULL) {
                        printf("\nThe file doesn't exist!!\n");
                        fclose(file);
                    } else {
                        char charDig;  ////To store the integer that read
                        char prev = '.'; ////Initialize with random char
                        /////Loop to read from the file char by char
                        while ((charDig = fgetc(file)) != EOF) {
                            /// if (atoi(&charDig) > 0 && atoi(&charDig) < 9) {
                            IntDigit = atoi(&charDig);   ////Convert from string to integer
                            //////Special chr to specify the new line location
                            /////For minus
                            if (charDig == '-') {
                                counter++;
                                sign = -1;
                                continue;
                            }
                            /////To read the positive number if there is + on its head
                            if (charDig == '+') {
                                sign = 1;
                                continue;
                            }
                            if (charDig == '-' && prev != '\n') {
                                num1 = 'n';
                            }
                            if (charDig == '-' && prev == '\n') {
                                num2 = 'n';
                            }
                            if (charDig == '\n') {
                                sign = 1;
                                prev = '\n';
                                continue;  ///If there is new line continue
                            } else {
                                if (prev == '\n') {
                                    insert(L2, sign * IntDigit);
                                } else {
                                    insert(L1, sign * IntDigit);
                                }
                            }

                        }
                        printf("The first number:\n");
                        printList(L1);
                        printf("The second number:\n");
                        printList(L2);

                    }
                    fclose(file);
                } else {
                    printf("\nThis file is already read!!");
                }
                break;
            case 2:  ////For addition choice   //////////Perfect/////////////////
                if (isEmpty(L1) && isEmpty(L2)) {
                    printf("\nSorry, we cannot make the operation, read and load the numbers then make the operation!!");
                } else {
                    ////Call addition function to make add operation
                    addition(L1, L2, sum);
                    printList(sum);
                }
                break;

            case 3: ////For subtraction operation
                if (isEmpty(L1) && isEmpty(L2)) { ///If there is no data
                    printf("\nSorry, we cannot make the operation, read and load the numbers then make the operation!!");
                } else {
                    if (greater(L1, L2) == 1) { ///if L1>L2
                        ////Call sub function to make sub operation
                        sub(L1, L2, Sub);
                        printList(Sub);
                    } else if (greater(L1, L2) == -1) {///if L1<L2
                        sub(L2, L1, Sub);
                        ConvertOpposite(Sub);
                        printList(Sub);
                    } else {
                        sub(L1, L2, Sub);
                        printList(Sub);
                    }
                }
                break;
            case 4: ///////For multiplication
                if (isEmpty(L1) && isEmpty(L2)) {
                    printf("\nSorry, we cannot make the operation, read and load the numbers then make the operation!!");
                } else {
                    mul(L1, L2, Mul);
                    printList(Mul);
                }
                break;
            case 5: /////For division operation
                if (isEmpty(L1) && isEmpty(L2)) { ///If there is no data
                    printf("\nSorry, we cannot make the operation, read and load the numbers then make the operation!!");
                } else {
                    printf("\nRemainder, Result:\n");
                    Div(L1, L2, remainder, Ddiv);
                    printList(Ddiv);
                }
                break;
            case 6: //////To save to the output file
                printf("\nPlease enter the output file name: ");
                scanf("%s", OutfileName);
                out = fopen(OutfileName, "w");
                if (isEmpty(L1) && isEmpty(L2)) { ///If there is no data
                    printf("\nSorry, we cannot make the operation, read and load the numbers then make the operation after that save it!!");
                } else {
                    if (out == NULL) {
                        printf("\n\n\nNo file");
                        continue;
                    }
                    ////////////////////////To printf instructions for user and then the results
                    //////To save the addition result
                    if (sum->next != NULL) {
                        fprintf(out, "Addition result: ");
                        Save(sum, out);
                    } else {
                        fprintf(out, "Addition result: -----\n");
                    }
                    //////To save the subtraction result
                    if (Sub->next != NULL) {
                        fprintf(out, "Subtraction result: ");
                        Save(Sub, out);
                    } else {
                        fprintf(out, "Subtraction result: -----\n");
                    }
                    /////To save the multiplication result
                    if (Mul->next != NULL) {
                        fprintf(out, "Multiplication result: ");
                        Save(Mul, out);
                    } else {
                        fprintf(out, "Multiplication result: -----\n");
                    }
                    //////////To save the division result
                    if (Ddiv->next != NULL) {
                        fprintf(out, "Division result: ");
                        Save(Ddiv, out);
                    } else {
                        fprintf(out, "Division result: -----\n");
                    }
                    /////A message to the user about the save process
                    printf("\nSave Done\n");
                    ////To refresh the sum list to use in other operation
                    delete(sum);
                    ////To refresh the Sub list to use in other operation
                    delete(Sub);
                    ////To refresh the Mul list to use in other operation
                    delete(Mul);
                    ////To refresh the division list to use in other operation
                    delete(Ddiv);
                    fclose(out);
                }
                break;
            case 7: /////To exit from the system
                printf("\nWe are happy to serve you, thanks ^_^\n");
                exit(1);
                break;
            default:
                printf("\nSorry, this choice is not exist!!!");
                break;
        }

    }

    return 0;
}