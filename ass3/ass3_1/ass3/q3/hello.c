#include<linux/init.h>
#include<linux/module.h>
#include <linux/moduleparam.h>

#include <linux/pid_namespace.h>


static char * proc = "make";
module_param(proc, charp,0660);

static int hello_init(void){
   
    char id[1024];
    pid_t pid;
    struct task_struct *task;

    printk(KERN_ALERT "TEST: Hello World\n");
    strcpy(id,proc);
    pid = simple_strtoul(id,NULL,0);
    task = pid_task(find_get_pid(pid),PIDTYPE_PID);

    printk(KERN_ALERT "PID = %d\n", task->pid);
    printk(KERN_ALERT "USER ID = %d\n", task->cred->uid.val);
    printk(KERN_ALERT "PROCESS GROUP ID = %d\n", pid_vnr(task_pgrp(task)));
    printk(KERN_ALERT "COMMAND PATH = %s\n", task->comm);
    
    return 0;
}
static void hello_exit(void){
    printk(KERN_ALERT "TEST: Good Bye\n");
}

MODULE_LICENSE("GPL"); 
module_init(hello_init);
module_exit(hello_exit);
