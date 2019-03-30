## PostTask

//src/base/task/post_task.h

This is the interface to post tasks.

To post a simple one-off task with default traits:
    PostTask(FROM_HERE, BindOnce(...));

To post a high priority one-off task to respond to a user interaction:
    PostTaskWithTraits(
        FROM_HERE,
        {TaskPriority::USER_BLOCKING},
        BindOnce(...));

To post tasks that must run in sequence with default traits:
    scoped_refptr<SequencedTaskRunner> task_runner =
        CreateSequencedTaskRunnerWithTraits(TaskTraits());
    task_runner->PostTask(FROM_HERE, BindOnce(...));
    task_runner->PostTask(FROM_HERE, BindOnce(...));

To post tasks that may block, must run in sequence and can be skipped on
shutdown:
    scoped_refptr<SequencedTaskRunner> task_runner =
        CreateSequencedTaskRunnerWithTraits(
            {MayBlock(), TaskShutdownBehavior::SKIP_ON_SHUTDOWN});
    task_runner->PostTask(FROM_HERE, BindOnce(...));
    task_runner->PostTask(FROM_HERE, BindOnce(...));

The default traits apply to tasks that:
    (1) don't block (ref. MayBlock() and WithBaseSyncPrimitives()),
    (2) prefer inheriting the current priority to specifying their own, and
    (3) can either block shutdown or be skipped on shutdown
        (implementation is free to choose a fitting default).
Explicit traits must be specified for tasks for which these loose
requirements are not sufficient.

Tasks posted with only traits defined in base/task/task_traits.h run on
threads owned by the registered TaskScheduler (i.e. not on the main thread).
An embedder (e.g. Chrome) can define additional traits to make tasks run on
threads of their choosing. TODO(https://crbug.com/863341): Make this a
reality.

Tasks posted with the same traits will be scheduled in the order they were
posted. IMPORTANT: Please note however that, unless the traits imply a
single thread or sequence, this doesn't guarantee any *execution ordering*
for tasks posted in a given order (being scheduled first doesn't mean it will
run first -- could run in parallel or have its physical thread preempted).

Prerequisite: A TaskScheduler must have been registered for the current
process via TaskScheduler::SetInstance() before the functions below are
valid. This is typically done during the initialization phase in each
process. If your code is not running in that phase, you most likely don't
have to worry about this. You will encounter DCHECKs or nullptr dereferences
if this is violated. For tests, prefer base::test::ScopedTaskEnvironment.
