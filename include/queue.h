/**
 * @file queue.h
 * @author Arjun Pathak
 * @brief This file contains the functions delcarations for the Queue and QueueNode structres
 *
 * This file contains the functions associated with the custom Queue implementation which will be
 * used primarily for BFS in Trie like structures. The implementation stores void pointers to
 * values. The caller must take care of casting the data back and forth. The queue structure is
 * composed of a series of nodes, chained together by next pointers. It is more space efficient and
 * stable than an array based implementation, although a little less cache friendly.
 */

/**
 * @struct QueueNode
 * @brief The structure of a single Queue Node
 *
 * @var QueueNode::value
 * Member value is void pointer to the value that is stored in the queue node.
 * @var QueueNode::next
 * Member next stores the address of the next queue node in line.
 */

struct QueueNode{
    void *value;
    struct QueueNode *next;
};
typedef struct QueueNode QueueNode;

/**
 * @struct Queue
 * @brief The structure that holds pointers to the front and the back of the queue.
 *
 * @var Queue::front
 * Member front points to the front node of the queue.
 * @var Queue::back
 * Member back points to the back of the queue.
 */

struct Queue {
    QueueNode *front;
    QueueNode *back;
};
typedef struct Queue Queue;


/**
 * @brief Returns a new queue with a single node in it
 *
 * @param[in] value The value held by the new Node in the queue
 * @param[out] queue The queue that is created by the function
 */

Queue *initQueue(void *value);


/**
 * @brief This functions deletes the entire queue from the heap
 *
 * @param queue The queue to be deallocated
 */

void deleteQueue(Queue *queue);

/**
 * @brief This function prepends a new node to a queue
 *
 * @param[in] queue The queue to which the value will be added
 * @param[in] value The value of the new node to be added
 */

void addToQueue(Queue *queue, void *value);

/**
 * @brief This function is used to remove a value from the back of the queue
 *
 * @param[in] queue A pointer to the queue structure
 */

void removeFromQueue(Queue *queue);
