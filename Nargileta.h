#ifndef UNTITLED_HEAD_H
#define UNTITLED_HEAD_H

struct Node {
    int number;
    char *name[10];
    int penalty;
    int bonus;
    struct Node *next;
};
 int smoking_time = 0;


struct Queue{
   struct Node *front, *rear;
};


struct Node* newNode();

struct Queue *createQueue();

void enQueue(struct Queue *q);

struct Node *deQueue(struct Queue *q);

void displayList(struct Queue *q);

void addPenalty(struct Queue *q);

void addBonus(struct Queue *q);

double StopTime(int a, double b);

void* displayTime(double ts);

void *timeIsUp(struct Node *pointer, struct Queue *q);


#endif //UNTITLED_HEAD_H
