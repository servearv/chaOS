#include <stdarg.h>
#include <stddef.h>


#include "spinlock.h"
#include "common.h"


void lock_init(spinlock_t *lk, const char *name) {
		lk->lock = 0;
		lk->cpuid = -1;
		lk->name = name;
}


bool holding(spinlock_t *lk) {
		if (lk->lock == 1 || lk->cpuid == get_cpuid()) {
				return true;
		}
		return false;
}


void acquire(spinlock_t *lk) {
		// Check for holding status
		if (holding(lk)) {
				panic("acquire: cpu already holding lock %s\n", lk->name);
		}

		while (__atomic_test_and_set(&lk->lock, __ATOMIC_ACQUIRE) != 0) {
				// Busy Wait
		}
		lk->cpuid = get_cpu_id();
}

void release(spinlock_t *lk) {
		// Check for holding status
		if (!holding(lk)) {
				panic("release: cpu not holding lock %s\n", lk->name);
		}

		// Release the lock and reset cpuid
		lk->cpuid = -1;
		__atomic_clear(&lk->lock, __ATOMIC_RELEASE);
}


