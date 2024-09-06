/**
 * @file queue.c
 * @author Arjun Pathak
 * @brief Generic Queue implementation
 *
 * This file contains the implementation of a generic queue interface declared
 * inside the queue.h file. To create a new generic queue instance, the initQueue()
 * functions has to be called by the user. This returns a new heap allocated queue
 * with the front and back of the queue initialized to the parameter passed in. The
 * caller must also call deleteQueue() in order to deallocate memory and avoid leaks.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/**
 * @brief A helper function to create a new queueNode
 *
 * The functions takes in a void pointer(value), creates a new QueueNode and assigns the
 * value to the node. The functions performs validation on the incoming value and does not
 * create a new node to hold a NULL pointer.
 *
 * @param[in] value The value that the node will hold
 * @param[out] node The new node that is created by the function
 */

static QueueNode *createQueueNode(void *value) {
    if (value == NULL) {
        return NULL;
    }
    QueueNode *node = malloc(sizeof(QueueNode));
    node->value = value;
    node->next = NULL;
}

/**
 * @brief Returns a new queue with a single node in it
 *
 * This function takes in a void *value and creates a new QueueNode with it. Then a new queue
 * is heap allocated and its front and back are initialized to the node that was just created.
 * The function will create a new node with its font and back assigned to NULL if a NULL pointer
 * is passed in as the value.
 *
 * @param[in] value The value held by the new Node in the queue
 * @param[out] queue The queue that is created by the function
 */

Queue *initQueue(void *value) {
    QueueNode *node = createQueueNode(value);
    Queue *queue = malloc(sizeof(Queue));
    
    if (value == NULL) {
        queue->front = NULL;
        queue->back = NULL;
    } else {
        queue->front = node;
        queue->back = node;
    }

    return queue;
}

/**
 * @brief This functions deletes the queue from the heap
 *
 * This function takes in a QueueNode and deallocates memory from it. The function will only clear the
 * node itself, not the location where its value field points to, the caller must make sure
 * to do that to avoid memory leaks.
 *
 * @param[in] node The node to be deleted
 */

static void deleteQueueNode(QueueNode *node) {
    if (node == NULL) {
        return;
    }
    free(node);
}

/**
 * @brief This functions deletes the entire queue from the heap
 *
 * This function calls the deleteQueueNode() helper function for all Queue Nodes starting from the
 * front of the queue. For more information on how the deletion of each node happens, read the
 * description of the deleteQueueNode() function.
 *
 * @param queue The queue to be deallocated
 */

void deleteQueue(Queue *queue) {
    if (queue == NULL) {
        return;
    }
    QueueNode *itr = queue->front;

    while (itr != NULL) {
        QueueNode *temp = itr;
        itr = itr->next;

       deleteQueueNode(temp); 
    }
    free(queue);
    queue = NULL;
}

/**
 * @brief This function prepends a new node to a queue
 *
 * This function takes in a queue and adds a new node to its end. The queue is validated for NULL
 * pointer and the back pointer of the queue is also adjusted accordingly. If the queue does not contain any
 * value, the node is added to the queue as its only node.
 *
 * @param[in] queue The queue to which the value will be added
 * @param[in] value The value of the new node to be added
 */

void addToQueue(Queue *queue, void *value) {
    if (queue == NULL) {
        return;
    }
    QueueNode *node = createQueueNode(value);

    if (queue->back == NULL && queue->front == NULL) {
        queue->back = node;
        queue->front = node;
        return;
    }
    queue->back->next = node;
    queue->back = node;
}

/**
 * @brief This function is used to remove a value from the back of the queue
 *
 * This function takes in a queue and removes the item at its front. The memory of the old font is
 * deallocated. The function does not return the value that was just deleted, in order to obtain the
 * value, the user must retrieve it from the front before calling this function.
 *
 * @param[in] queue A pointer to the queue structure
 */

void removeFromQueue(Queue *queue) {
    if (queue == NULL || queue->front == NULL) {
        return;
    }
    QueueNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    deleteQueueNode(temp);
}

/**
 * @brief A function to test the Queue implementation
 */

void testQueue() {
    Queue *queue = initQueue(NULL);
    assert(queue->front == NULL);
    assert(queue->back == NULL);
    printf("successfully created a new empty queue\n");

    deleteQueue(queue);
    printf("successfully deallocated the queue\n");
    
    int a = 100;
    queue = initQueue(&a);
    assert(*(int *)queue->front->value == 100);
    assert(*(int *)queue->back->value == 100);
    printf("successfully initialized a non-empty queue\n");

    int b = 200;
    addToQueue(queue, &b);
    assert(*(int *)queue->front->value == 100);
    assert(*(int *)queue->back->value == 200);
    printf("successfully added a new node to the queue\n");

    removeFromQueue(queue);
    assert(*(int *)queue->front->value == 200);
    assert(*(int *)queue->back->value == 200);
    printf("successfully removed an element from the queue\n");

    removeFromQueue(queue);
    assert(queue->front == NULL);
    assert(queue->back == NULL);
    printf("successfully removed from an empty queue\n");

    addToQueue(queue, &a);
    addToQueue(queue, &b);
    assert(*(int *)queue->front->value == 100);
    assert(*(int *)queue->back->value == 200);
    printf("succesfully added to an empty queue\n");

    deleteQueue(queue);
    printf("successfully deleted a non-empty queue\n");
}
