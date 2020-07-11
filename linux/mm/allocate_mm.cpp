static struct kmem_cache *task_struct_cachep;

// Step 0:
// 在系统初始化时，task_struct_cachep会被kmem_cache_create创建
// 专门用于分配task_struct对象的缓存。缓存区每块大小刚好等于task_struct大小
// 即arch_task_struct_size
task_struct_cachep =
    kmem_cache_create("task_struct", arch_task_struct_size, align,
                      SLAB_PANIC | SLAB_NOTRACK | SLAN_ACCOUNT, NULL);

// Step 1:
// 调用此方法，在task_struct的缓冲区task_struct_cachep分配了一块内存
// 每次创建task_struct时，先到缓存里瞅瞅有没有直接可用的，没有再去内存里申请
static inline struct task_struct *alloc_task_struct_struct_node(int node)
{
  return kmem_cache_alloc_node(task_struct_cachep, GFP_KERNEL, node);
}

// Step 2:
// 当进程结束时，task_struct不用直接被销毁，而是放回到缓存中
static inline void free_task_struct(struct task_struct *tsk)
{
  kmem_cache_free(task_struct_cachep, tsk);
};

/*
* Question: 那kmem_cache是什么样的呢？
*/
struct kmem_cache
{
  // 在分配缓存块的时候，要分两种路径，快速通道和普通通道。
  // 这个是快速通道，优先从这里分配，如果没有则去普通通道分配
  struct kmem_cache_cpu __percpu *cpu_slab;

  unsigned long flags;
  unsigned long min_partial;
  int size; /* The size of an object including meta data */
  int object_size; /* The size of an object without meta data */
  int offset;      /* Free pointer offset. */
#ifdef CONFIG_SLUB_CPU_PARTIAL
  int cpu_partial; /* Number of per cpu partial objects to keep around */
#endif
  struct kmem_cache_order_object oo;
  struct kmem_cache_order_object max;
  struct kmem_cache_order_object min;

  gfp_t allocflags; /* gfp flags to use on each alloc */
  int refcount;     /* Refcount for slab cache destroy */
  void (*ctor)(void *);
  //....
  const char *name;
  // 操作系统管理的缓存不仅包括task_struct, 还有类似mm_struct, fs_struct等
  // 所有的缓存都会放到一个链表里
  struct list_head list;
  //....
  // 这个是普通通道，如果这里还没有可用的，那就只能去伙伴系统那里分配新的page了
  struct kmem_cache_node *node[MAX_NUMNODES];
};

/*
 * Question: 那kmem_cache_cpu是如何释放缓存块的？
 */
struct kmem_cache_cpu
{
  // 指向大内存块第一个空闲的项，这里面会有指针指向下一个空闲的项
  // 最终所有的空闲的项会形成一个链表
  void **freelist;
  unsigned long tid;
  struct page *page;  // 指向大内存块的第一个页
#ifdef CONFIG_SLUB_CPU_PARTIAL
  // 指向大内存块的第一个页，它里面部分内存被分配出去了
  // 部分是空的，是一个备用列表。当page满了，就会从这里找
  struct page *partial;
#endif
  // ....
};


struct kmem_cache_node
{
  spinlokc_t list_lock;
  //....
#ifdef CONFIG_SLUB
  unsigned long nr_partial;
  // 链表， 存放部分空闲的内存块，备用列表
  struct list_head partial;
  //....
#endif
};

/*
 * 分配过程：
 *   1. kmem_cache_alloc_node调用slab_alloc_node
 *   2. 对于快速通道，取出cpu_slab即kmem_cache_cpu的free_list,直接返回；
 *      如果没有空闲的，那就走普通通道，调用__slab_alloc
 *   3. 对普通通道，会受限尝试下kmem_cache_cpu的freelist，
 *      因为万一当前进程被中断，再次唤醒时，可能别人已经释放了一些缓存。
 *   3.2 先去kmem_cache_cpu里面的partial看下，最后才会调用new_slab_objects——根据node_id，
 *      找到kmem_cache_node，然后调用get_partial_node
 */