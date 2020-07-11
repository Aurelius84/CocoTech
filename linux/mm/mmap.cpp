/*
* 内存映射不仅时物理内存和虚拟内存之间的映射
* 还包括文件中的内容映射到虚拟内存空间，这样
* 访问内存空间就能访问到文件里面的数据
* 申请小块内存用brk，大内存块用mmap
*/

struct mm_struct
{
  struct vm_area_struct *mmap; /*list of VMAs */
  //...
};

struct vm_area_struct
{
    struct
    {
      struct rb_node rb;
      unsigned long rb_subtree_last;
    }shared;

    struct list_head anon_vma_chain;
    struct anon_vma *anon_vma;

    const struct vm_operations_struct *vm_ops;
    unsigned long vm_pgoff;
    struct file *vm_file;
    void *vm_private_data;
};

/*
* 在linux中，每个打开的文件都有一个struct file结构
* 里面有一个file_operations，用来表示和这个文件的操作
*/
const struct file_operations ext4_file_operations = {
// ....
.mmap = exe4_file_mmap
.get_unmapped_area = thp_get_unmapped_area,
};

// note : 用户缺页异常
// 一旦开始访问虚拟内存的某个地址，如果发现，并没有对应的
// 物理页，那就会触发缺页中断，调用do_page_fault.

dotraplinkage void notrace do_page_fault(struct pt_regs *regs, unsigned long error_code)
{
  unsigned long address = read_cr2();
  //...
  __do_page_fault(regs, error_code, address);
  //...
}

static noinline void __do_page_fault(struct pt_regs *regs, unsigned long error_code, unsigned long address)
{
  struct vm_area_struct *vma;
  struct task_struct *tsk;
  struct mm_struct *mm;

  tsk = current;
  mm = tsk->mm;

  // 先判断缺页中断是否发生在内核
  // 如果发生在内核则调用vmalloc_fault
  // 在内核里面，vmalloc区域需要内核页表映射到物理页
  if(unlikely(fault_in_kernel_space(address)))
  {
    if (vmalloc_fault(address) >= 0) return;
  }
  // ...
  // 在用户空间中，定位到那个地址所在的区域vm_area_struct
  vma = find_vma(mm, address);
  // ...
  fault = handle_mm_fault(vma, address, flags);
  // ..
}