typedef struct {
    volatile int lock;
		int owner;
		char *name;
} spinlock_t;


