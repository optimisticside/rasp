#include "lib.h"

/*
 * memory area strucure
 * formed into a linked lists to keep track
 * of free memory spaces
 */
struct memarea {
	int	m_size;			/* current size */
	char	*m_end;			/* end address */
	struct	memhead *m_head;	/* first memory block */
	struct	memhead *m_tail;	/* last memory block */
	struct	memhead *m_next;	/* next map */
} *mhead, *mtail;

/*
 * memory header structure
 * for each allocation we put a tag at the beginning of it
 * this is so we don't need to keep track of size manually
 */
struct memhead {
	struct	memhead *h_next;	/* next header */
	struct	memarea *h_area;	/* memory area */
	int	h_size;			/* size */
};

/*
 * allocate n bytes of memory
 * find first map with enough space
 * then add header to linked list
 * and update size of area
 */
char *malloc(int size)
{
	struct memhead *mh;
	struct memarea *ma = mhead;
	int n = size + sizeof(struct memhead);

	while (ma != NULL) {
		if (ma->m_size >= n) {
			if (ma->m_tail != NULL) {
				mh = ma->m_tail - n;
				ma->m_tail->h_next = mh;
			} else {
				mh = ma->end - n;
				ma->m_tail = mh;
			}
			if (ma->m_head == NULL)
				ma->m_head = mh;
			ma->m_size -= n;
			mh->m_area = ma;
			mh->m_size = n;
			return mh + sizeof(struct memhead);
		}
		ma = ma->m_next;
	}
	return 0;
}

/*
 * free a block of memory
 * find area associated with it
 * then remove header from linked list
 * and update size
 */
int free(char *ptr) {
	struct memhead *mh = ptr - sizeof(struct memhead);
	struct memarea *ma, *wk, *pv = NULL;

	if (mh != NULL) {
		ma = mh->h_area;

		/*
		 * we can't use an indirect pointer
		 * since we have to update ma->m_tail
		 * with the previous node
		 */
		wk = ma->m_head;
		while (*wk != mh) {
			pv = wk;
			wk = wk->h_next;
		}
		if (pv != NULL)
			pv->h_next = wk->h_next;
		else
			ma->m_head = wk->h_next;
		if (ma->m_tail == mh)
			ma->m_tail = pv;
	}
}

/*
 * reallocate a block of memory
 * allocate new block of size n
 * copy data over
 * free current block
 */
char *realloc(char *ptr, int size) {
	struct memhead *mh = ptr - sizeof(struct memhead);
	char *nw = 0;

	if (mh != NULL) {
		nw = malloc(size);
		memcpy(ptr, nw, mh->h_size);
		free(ptr);
	}
	return nw;
}
