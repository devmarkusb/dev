# Definitions

Commutative ring: ring with commutative multiplication.

Datum: a sequence of bits.

Euclidean domain E: integral domain with operations quotient and
remainder s.t. for b!=0 and all a: a=quotient(a,b)b+remainder(a,b)
holds and there is a non-negative norm ||x|| from E to natural
numbers with:
* ||a||=0 <=> a=0
* b!=0 => ||ab||>=||a||
* ||remainder(a,b)||<||b||

Field: integral domain with multiplicative inverses, i.e.
multiplication group instead of monoid.

Integral domain: commutative Ring with no zero divisors.

Object: collection of bits in memory containing a value of a given
value type.

Object type: uniform method of storing and retrieving values of a
given value type from a particular object when given its address.

Ring: semiring plus 'additive' inverses, i.e. 'additive' group instead
of monoid.

Semiring: 'additive' monoid together with 'multiplicative' monoid
together with distributivity. And 0!=1 and 0a=0.

Value: datum together with its interpretation.

Value type: set of values sharing a common interpretation.

Zero divisor: element x!=0 of a ring for which there is a y!=0
with xy=0.

# Excercises

## Failed

* 2.1 did many examples, got a feeling, but no
  general solution for n
* 3.4 just made all the observations but no chance of understanding
* 4.1 too hard
* 4.7 hard
* 5.1 hard
* 12.7 skip for now, seems difficult

## Notes

* 4.2 accomplished more hand-wavingly like gcm algorithm
* 9.3 accomplished only the following order: commutativity,
  distributivity, associativity (so, the latter not independently).
  Helpful was proving a'b=ab+b first.

