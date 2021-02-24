#ifndef _CS_H_
#define _CS_H_

struct lock {
	u32 primask;
};

#define LOCK_INIT (struct lock) {}

static inline void critical_section_init(struct lock *lock)
{
}

static inline void critical_section_enter(struct lock *lock)
{
	u32 tmp;
	asm volatile (
		"mrs	%0, PRIMASK\n\t"
		"cpsid	i\n\t"
		: "=r" (tmp) );
	lock->primask = tmp;
}

static inline void critical_section_exit(struct lock *lock)
{
	asm volatile (
		"msr	PRIMASK, %0\n\t"
		: : "r" (lock->primask) );
}

#endif
