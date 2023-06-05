#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isEmpty(Queue* queue) {
    return queue->front == -1;
}

bool isFull(Queue* queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void enqueue(Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Error: Queue overflow\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->data[queue->rear] = value;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue underflow\n");
        return -1; // Valor de erro, você pode modificar conforme necessário
    }

    int value = queue->data[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    return value;
}

int front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty\n");
        return -1; // Valor de erro, você pode modificar conforme necessário
    }
    return queue->data[queue->front];
}

int rear(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty\n");
        return -1; // Valor de erro, você pode modificar conforme necessário
    }
    return queue->data[queue->rear];
}

void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    int current = queue->front;
    while (current != queue->rear) {
        printf("%d ", queue->data[current]);
        current = (current + 1) % MAX_SIZE;
    }
    printf("%d\n", queue->data[current]);
}

void destroyQueue(Queue* queue) {
    free(queue);
}

int main() {
    Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printQueue(queue);

    int frontValue = front(queue);
    printf("Front element: %d\n", frontValue);

    int rearValue = rear(queue);
    printf("Rear element: %d\n", rearValue);

    int dequeued = dequeue(queue);
    printf("Dequeued element: %d\n", dequeued);

    printQueue(queue);

    destroyQueue(queue);

    return 0;
}
