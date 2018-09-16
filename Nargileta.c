#include <stdio.h>
#include <string.h>
#include "Nargileta.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

time_t start;
time_t curr;
time_t stop;

double diff = 0;
int flagStop = 0;
double ts = 0;
int *ptr = NULL;

int main() {
    int broi;
    char option = 0;


    printf("\n\tSmoking time in seconds: ");
    if (scanf("%d", &smoking_time) != 1) {
        printf("\tThis is not a number\n\n\n");
        exit(1);
    }
    struct Queue *q = createQueue();

    do {
        system("cls");
        printf("\n\t1. Add people\n");
        printf("\t2. Edit penalty\n");
        printf("\t3. Edit bonus\n");
        printf("\t4. Stop timer\n");
        printf("\t5. Display list and time\n\n");
        printf("\t6. Exit\n\n\n");

        if (option < '1' || option > '5') {
            printf("\tEnter your choice : ");
            fflush(stdin);
        } else {
            printf("\tEnter your choice : ");
        }

        scanf("%c", &option);
        fflush(stdin);
        system("cls");

        switch (option) {
            case '1':
                printf("\n\tHow many people want to add?  \t ");
                if (scanf("%d", &broi) != 1) {
                    printf("\tThis is not a number\n\n\n");
                    exit(1);
                }
                system("cls");
                for (int i = 0; i < broi; i++) {
                    enQueue(q);
                    time(&start);
                }
                break;
            case '2':
                addPenalty(q);
                break;
            case '3':
                addBonus(q);
                break;
            case '4':
                ts = StopTime(flagStop,ts);
                flagStop = 1;
                displayTime(ts);
                system("pause");
                break;
            case '5':
                displayList(q);
                system("pause");
                break;
        }
    } while (option != '6');
    return 0;
}



struct Node* newNode() {
    struct Node *temp = (struct Node *) malloc(sizeof(struct Node));

    printf("\n\tAdd number: ");
    if (scanf("%d", &temp->number) != 1) {
        printf("Enter a number next time\n\n\n");
        exit(1);
    }

    printf("\tAdd name: ");
    scanf("%s", &temp->name);

    printf("\tAdd penalty: ");
    if (scanf("%d", &temp->penalty) != 1) {
        printf("Enter a number next time\n\n\n");
        exit(1);
    }

    printf("\tAdd bonus: ");
    if (scanf("%d", &temp->bonus) != 1) {
        printf("Enter a number next time\n\n\n");
        exit(1);
    }

    printf("\n");

    fflush(stdin);

    temp->next = NULL;
    return temp;
}

struct Queue *createQueue(){
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue *q){
    struct Node *temp = newNode();

    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node *deQueue(struct Queue *q){
    // If queue is empty, return NULL.
    if (q->front == NULL)
       return NULL;

    // Store previous front and move front one node ahead
    struct Node *temp = q->front;
    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}

void displayList(struct Queue *q) {
    struct Node *temp = q->front;
    struct Node *pointer = q->front;

        while (temp != NULL) {
            printf("\n\tPerson's number: %d \n", temp->number);
            printf("\tName: %s \n", &temp->name);
            printf("\tPenalty in seconds: %d \n", temp->penalty);
            printf("\tBonus in seconds: %d \n\n", temp->bonus);
            printf("\tTIME FOR SMOKING: %d seconds\n", smoking_time + temp->bonus - temp->penalty);
            printf("\t_____________________________\n");

            temp = temp->next;

            printf("\n");
        }


    displayTime(ts);
    timeIsUp(pointer,q);

}

void addPenalty(struct Queue *q) {
    int pers_number;
    int new_penalty;
    int flag = 0;

    printf("\n\tEnter person's number: ");
    if (scanf("%d", &pers_number) != 1) {
        printf("\tThis is not a number\n\n\n");
        exit(1);
    }

    struct Node *temp = q->front;

    while (temp != NULL) {
        if (pers_number == temp->number) {
            printf("\tEnter penalty in seconds: ");

            if (scanf("%d", &new_penalty) == 1) {
                temp->penalty += new_penalty;
                printf("\t\tSuccessfull!\n\n\n");
                flag = 1;
                system("pause");
                break;
            } else {
                printf("\tEnter a number! \n\n\n");
                system("pause");
            }
        }
        temp = temp->next;
    }
}

void addBonus(struct Queue *q) {
    int pers_number;
    int new_bonus;
    int flag = 0;

    printf("\n\tEnter person's number: ");
    if (scanf("%d", &pers_number) != 1) {
        printf("\tThis is not a number\n\n\n");
        exit(1);
    }

    struct Node *temp = q->front;;

    while (temp != NULL) {
        if (pers_number == temp->number) {
            printf("\tEnter bonus in seconds: ");

            if (scanf("%d", &new_bonus) == 1) {
                temp->bonus += new_bonus;
                printf("\t\tSuccessfull!\n\n\n");
                flag = 1;
                system("pause");
                break;
            } else {
                printf("\tEnter a number! \n\n\n");
                system("pause");
            }
        }
        temp = temp->next;
    }
}

void* displayTime(double ts){
    if(flagStop == 0){
        time(&curr);
        diff = difftime(curr, start);
        printf("\tTIME ELAPSED: %.0lf seconds\n",diff);
        printf("\t_________________________\n\n");
    }else if(flagStop == 1){
        printf("\tTIMER STOPPED AT: %.0lf seconds\n",ts);
        printf("\t_________________________\n\n");
    }
}

void *timeIsUp(struct Node *pointer, struct Queue *q){

    if(diff >= (pointer->bonus +smoking_time - pointer->penalty)){
        printf("\tTime is up, SWITCH\n\n");
        Beep(1000,1000);

        deQueue(q);
        printf("\n\tAdd the same person who was smoking until now or add another person to the back !\n");
        printf("\n\t If doesnt want to... press 'n' : ");

        char c = 0;
        if(c = getchar() != 'n'){
             enQueue(q);
        }

        time(&start);
    }
}

double StopTime(int flagStop, double ts){

    if(flagStop == 0){
        time(&stop);
        ts = difftime(stop,start);
        flagStop = 1;
    }
    return ts;
}
