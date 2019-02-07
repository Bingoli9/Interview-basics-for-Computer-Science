## hardware_concurrency

public static member function

static unsigned hardware_concurrency() noexcept;

Used for detecting hardware concurrency and return the number of hardware thread contexts.

The interpretation of this value is system and implementation-specific, and may not be exact, but just an approximation.

Note that this does not need to match the actual number of processors ot cores available in the system: A system can support multiple threads per processing unit, or restrice the access to its resources to the program.

If this value is not computable or well defined, the function returns 0.



