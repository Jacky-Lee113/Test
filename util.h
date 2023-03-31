
/* Process status */ 
#define UNINITIALIZED   0
#define INITIALIZED     1
#define READY           2
#define RUNNING         3
#define SUSPENDED       4
#define TERMINATED      5

#define RESERVED_MEMORY 64  // Reserved memory
#define TOTAL_MEMORY    1024  // Total memory within system

/* this is the main queue. 
 * All process first come to this queue and the its 
 * dispatched to other queues according to its priority */
struct pcb* input_queue = NULL;
struct pcb* priority = NULL; // Pointer that points to the queue holding the real time processes that still need to be be completed
struct pcb* secondary = NULL;  // Pointer that points to the queue that holds processes that still need to be started
struct pcb* priority_one_queue = NULL;  // Pointer to priority one queue
struct pcb* priority_two_queue = NULL;  // Pointer to priority two queue
struct pcb* priority_three_queue = NULL;  // Pointer to priority three queue
struct pcb* current_process = NULL; // Pointer that points to current process
struct pcb* process = NULL; // Pointer that is used when creating a new process
struct mem_struct* memory = NULL;  // Pointer that points to main memeory block
struct mem_struct* reserved_memory = NULL; // Pointer that points to the reserved memory block
struct resources* rsrcs = NULL; // Pointer that points to the number of system resources currently held

unsigned int timer = 0; // Timer

struct mem_struct {
  unsigned int offset;    // Location of mem struct
  unsigned int size;  // Size of the mem struct in mbytes
  int allocated;  // Allocation of memstruct in current process
  struct mem_struct* prev;   // Pointer that points to previous mem struct
  struct mem_struct* next;   // Pointer that points to next mem struct
};
