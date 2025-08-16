Kernel Module

1) To input command line argument, module_param is defined.
2) From the input process first pid is obtained using simple_strtoul().
3) From the pid, task_struct is obtained using find_get_pid and pid_task.
4) This task_struct is used to get the required values.

Command to load the compiled module:
insmod ./hello.ko param=make
