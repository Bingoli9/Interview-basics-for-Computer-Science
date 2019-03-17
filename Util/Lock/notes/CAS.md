## CAS

CAS： Compare and swap; Used for update a variable atomically.

drawback:

- CPU overhead

  In the case of high concurrency, if many threads repeatedly try to update a variable, but the update is not successful, the loop will be repeated, which will put a lot of pressure on the CPU.

- ABA problem.
