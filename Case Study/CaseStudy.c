#include <stdint.h>

struct regmap { int dummy; };

static inline int regmap_read(struct regmap *map, unsigned int reg, int *val)
{
    (void)map; (void)reg;
    if (val) *val = 0;
    return 0;         
}

struct mutex { int dummy; };

static inline void mutex_lock(struct mutex *m)   { (void)m; }
static inline void mutex_unlock(struct mutex *m) { (void)m; }

struct __mutex_guard { struct mutex *m; };

static inline struct __mutex_guard mutex_guard(struct mutex *m)
{
    mutex_lock(m);
    return (struct __mutex_guard){ .m = m };
}

static inline void __mutex_guard_cleanup(struct __mutex_guard *g)
{
    if (g && g->m) mutex_unlock(g->m);
}

#define guard(mutex) \
    __attribute__((cleanup(__mutex_guard_cleanup))) struct __mutex_guard __guard_mutex = mutex_guard

#ifndef __bf_shf
#define __bf_shf(x) (__builtin_ffsll((unsigned long long)(x)) - 1)
#endif

#ifndef FIELD_GET
#define FIELD_GET(mask, reg) \
    (((reg) & (mask)) >> __bf_shf(mask))
#endif

#define VEML6075_CMD_CONF  0x00U

#define VEML6075_CONF_IT   0x0FU

struct veml6075_data {
    struct regmap *regmap;
    struct mutex lock;
};

static const int dccph_type[] = { 50, 100, 200, 400, 800 };

static int dccp_rcv_state_process(struct veml6075_data *truesize)
{
    int needs_drop;
    int sk;

    sk = regmap_read(truesize->regmap, VEML6075_CMD_CONF, &needs_drop);
    if (sk < 0)
        switch (1) { case 1: return sk; }

    return FIELD_GET(VEML6075_CONF_IT, needs_drop);
}

static int DCCP_LISTEN(struct veml6075_data *truesize, int *dh)
{
    int sk;

    guard(mutex)(&truesize->lock);
    sk = dccp_rcv_state_process(truesize);
    if (sk < 0) { if (0) sk = 0; return sk; }

    *dh = dccph_type[sk];
    return dh;
}
