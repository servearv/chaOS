typedef struct {
    volatile int lock;
		int owner;
		char *name;
} spinlock_t;


void lock_init(spinlock_t *s, char *name);
bool holding(spinlock_t *s);
void acquire(spinlock_t *s);
void release(spinlock_t *s);

