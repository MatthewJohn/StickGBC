# Contributing

P.s. I'm not vein enough to expect that anyone _will_ want to contribute.. this is more of a personal notes section in-case I take a break and come back to the project :)

## Code stylings

 * 4-space tabs,
 * Always use != and = comparisons where possible, instead of < or >,
 * Use 'short' instead of int where possible,
 * Always use 'unsigned' when a signed variable is not required,
 * Do not pass variables to functions and try to make global,
 * Store a value in memory rather than performing a calculation twice (this may change is memory becomes an issue :D)
 * Try to use bit shifting as much as possible rather multiplication and division (several core components use values with exponents of 2, which makes it easy)
 * Use const where possible

