# Elements of Programming

Glossary, examples and experiments supporting the study of the book
'Elements of Programming' by Stepanov.

## Glossary

Abstract entity: is an individual thing that is eternal and unchangeable.

Abstract genus: describes different abstract species that are similar in some respect.

Abstract species: describes common properties of essentially equivalent abstract entities. 

Ambiguous value type: if a value of the type has more than one interpretation.

Assignment: is a procedure taking two objects of the same type, making the first
object equal to the second without modifying the second.

Attribute: assigns an abstract entity to a conrete entity in the form of some
property, measurement or quality.

Computational basis, efficient, effective: finite set of procedures that enable the
construction of any other procedure for the (value/object) type.
We strive for efficiency (the basis being at least as efficient as any other) and
expressiveness (the basis allowing convenient usage).

Concrete entity: individual thing that comes into and out of existence in space and time.

Concrete genus: describes different concrete species that are similar in some respect.

Concrete species: set of attributes of essentially equivalent concrete entities.

Constructor: procedure turning memory locations into an object. 

Copy constructor: procedure taking an additional argument of the same type and
constructing a new object equal to it.

Datum: a finite sequence of 0s and 1s.

Default constructor: procedure taking no arguments and leaving the object in a
partially formed state. 

Destructor: procedure causing the end of an object's existence.

Entity: abstract or concrete entity.

Equal objects: if and only if they have their states are equal.

Equal values (behaviorally equal): if they represent the same abstract entity.

Equality procedure: returning true if and only if the two objects passed are of the
same type and are equal.

Equational reasoning: is substituting equals for equals.

Function / function arguments, result: a rule associating one or more abstract entities from
corresponding species, called arguments, with another abstract entity from another
species, called result.

Identity: determines sameness of a thing changing over time.

Interpretion of a datum: an entity corresponding to a datum.

Load: obtain content of an address.

Object: representation of a concrete entity as a value in memory.
For C++ synonymous to value.

Object type: a pattern for storing and modifying values in memory.
For C++ synonymous to value type.

Partially formed state of an object: if the object can be assigned to
(left hand side) or destructed.
If the object is not also well formed nothing else is defined.

Procedure: sequence of instructions that modify the state of some objects or
construct or destroy them.

Procedure input/output, direct/indirect passings, local/global/own state: obvious notions
for objects dealt with.

Memory, address, content, lengths: a set of words (number pairs), each with an address and
a content. Addresses are values of fixed address length, content values of fixed
word length. 

Properly partial or total value type: if it's values represent a proper subset of the
abstract entities in the corresponding species, otherwise it is total.

Regular function: if and only a substitution of an argument by an equal value
yields an equal result.

Regular type: if its basis includes equality, assignment, destructor,
default constructor, copy constructor, total ordering, and underlying type.

Representation of a entity: a datum corresponding to a particular entity.

Representationally equal values: if their datums are identical sequences of 0s and 1s.

Resources: owned by object to hold its state in memory. The is a starting address
for every object.

Snapshot: is a complete collection of the attributes of a conrete entity in a particular
point of time.

Species: abstract or concrete species.

State of object: value of some value type. 

Store: change content of an address.

Total ordering: ?

Total value type: see properly partial.

Unambiguous: negation of ambiguous.

Underlying type: Ch. 12 (later)

Uniquely represented value type: if and only if at most one value corresponds to each
abstract entity.

Value: is the combination of representation and interpretion.

Value type: a correspondence between a species and a set of datums.

Well formed datum: if and only if that datum represents an abstract entity.