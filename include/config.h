/**
 * See Copyright Notice in picrin.h
 */

#ifndef CONFIG_H__
#define CONFIG_H__

/* switch normal VM and direct threaded VM */
#define PIC_DIRECT_THREADED_VM 1

/* switch internal value representation */
/* #define PIC_NAN_BOXING 1 */

/* enable readline module */
#define PIC_ENABLE_READLINE 1

/* treat false value as none */
#define PIC_NONE_IS_FALSE 1

/* initial memory size (to be dynamically extended if necessary) */
#define PIC_ARENA_SIZE 100
#define PIC_HEAP_PAGE_SIZE (10000)
#define PIC_STACK_SIZE 1024
#define PIC_RESCUE_SIZE 30
#define PIC_GLOBALS_SIZE 1024
#define PIC_MACROS_SIZE 1024
#define PIC_SYM_POOL_SIZE 128
#define PIC_IREP_SIZE 8
#define PIC_POOL_SIZE 8
#define PIC_ISEQ_SIZE 1024

/* enable all debug flags */
/* #define DEBUG 1 */

#if DEBUG
# define GC_STRESS 0
# define VM_DEBUG 1
# define GC_DEBUG 1
# define GC_DEBUG_DETAIL 0
#endif

#endif
