#include "core/core.h"

/*
 * acquires a spinlock
 * spins until free
 * and steals it
 */
int slock(int *lk) {
	/*
	 * we do a pause to clear cpu pipeline
	 * since these test-and-set instructions clog it up
	 */
	while(stry(lk))
		pause();
}

/*
 * releases a spinlock
 * just sets its value
 */
int srele(int *lk) {
	*lk = 0;
}
