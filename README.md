# -A-Garbage-Collector
Dynamic memory (i.e. memory accessed via the malloc and free family of commands) is essential to many programs in the freedom, control, and interpretability it allows. Section 9.9 discusses 2 different types of management for dynamic memory: implicit allocators and explicit allocators.  This assignment focuses on the implicit allocator, perhaps better known as the garbage collector, where we don't need to explicitly free the unused memory. Intuitively, we want this tool to find the blocks (or chunks as we refer to them) that are not being used and return them to the process as free chunks.