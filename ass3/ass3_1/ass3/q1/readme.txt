
Modified Dining Philosophers Problem
--------------------------------------

a.1:
Strict ordering of resource requests

To maintain strict ordering and parallelism following approack is taken:
Philospher 0 and 2 can eat in parallel
Philospher 1 and 3 can eat in parallel
Philospher 4 can then eat
This way there is no need of semaphore and deadlock can be avoided.

a.2:
Utilization of semaphores to access the resources.

Forks are implemented as semaphores. Hence, only one philospher can
hold the fork. But, this may lead to deadlock. Hence, following approch
it taken for deadlock avoidance:

Odd no. of philospher will always pick left fork first.
Even no. of philospher will always pick the right for first.

b.1:
a system that also has two sauce bowls

Here, bowls are implemented as counting semaphores.
To avoid the deadlock, following approach is taken:

First the forks are taken by the philospher. Once the philosper
has both the forks then only the philospher can take the bowl.

As at max only 2 philosphers can have both the forks, accessing the bowl
will not cause deadlock.

b.2:
a system that also has two sauce bowls

Here, bowls are implemented as shared memory but forks are implemented as semaphores.
Again to avoid the deadlock first access to forks are given and then the count on bowl memory 
is verified and given the access to the philospher.
