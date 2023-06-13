# Elements of Programming

Glossary, examples and experiments supporting the study of the book
'Elements of Programming' by Stepanov.

## Glossary

Abstract entity: is an individual thing that is eternal and unchangeable.
Ex: 5, blue

Abstract genus: describes different abstract species that are similar in some respect.
Ex: algebraic group, being arithmetic, number

Abstract procedure: a procedure parameterized by types and constant values with
requirements on these parameters.
Represented in C++ as a template function or function object template with
requires clause.
Ex: adding two numbers

Abstract species: describes common properties of essentially equivalent abstract entities.
Ex: integers

Ambiguous value type: if a value of the type has more than one interpretation.
Ex: just 2 digits to be interpreted as a year (23 meaning 1923 or 2023?)

Arity(F): type attribute of the number of inputs of a functional procedure F. 

Assignment: is a procedure taking two objects of the same type, making the first
object equal to the second without modifying the second.

Attribute: assigns an abstract entity to a concrete entity in the form of some
property, measurement or quality.
Ex: age of a person

Codomain of a functional procedure: type of its output.

Codomain(F): type function mapping functional procedure F to the type of its result.

Computational basis, efficient, effective: finite set of procedures that enable the
construction of any other procedure for the (value/object) type.
We strive for efficiency (the basis being at least as efficient as any other) and
expressiveness (the basis allowing convenient usage).

Concept: a collection of requirements on types, expressed as syntactic and semantic
properties. Concepts represents genera as types represent species as values represent entities.

Concrete entity: individual thing that comes into and out of existence in space and time.
Ex: objects in a computer game

Concrete genus: describes different concrete species that are similar in some respect.
Ex: mammals

Concrete species: set of attributes of essentially equivalent concrete entities.
Ex: humans

Constructor: procedure turning memory locations into an object. 

Copied object (a copy): if it has the same state as another one.

Copy constructor: procedure taking an additional argument of the same type and
constructing a new object equal to it.

Datum: a finite sequence of 0s and 1s.

Default constructor: procedure taking no arguments and leaving the object in a
partially formed state.

Definition space: for a functional procedure is that subset of values for its inputs
to which it is intended to be applied. 

Destructor: procedure causing the end of an object's existence.

Domain of a homogeneous functional procedure: type of its inputs.

Entity: abstract or concrete entity.

Equal objects: if and only if their states (values) are equal.

Equal representations: weaker form than behaviorally equal, just equal data.

Equal values (behaviorally equal): if they represent the same abstract entity.

Equality: a procedure returning true if and only if the two objects passed are of the
same type and are equal.

Equational reasoning: is substituting equals for equals.

Function / function arguments, result: a rule associating one or more abstract entities from
corresponding species, called arguments, with another abstract entity from another
species, called result.

FunctionalProcedure: a type concept corresponding to the definition of a functional
procedure.

Functional procedure: a regular procedure defined on regular types with one or more
direct inputs and a single output that is returned as the result of the procedure.

Homogeneous functional procedure: one whose inputs are of the same type entirely.

Identity: determines sameness of a thing changing over time.

Identity token: unique value expressing the identity of an object, computed from the
value of the object and its resources.

Implementation of functions on abstract entities: as functions on values by computers.

InputType(F, i): i'th input type of functional procedure F.

Interpretion of a datum: an entity corresponding to a datum.

Load: obtain content of an address.

Model: a concept is modeled by types, or a type is a model for a concept, if the
concepts requirements are satisfied for these types. Written C(T_0,...,T_{n-1}).

Object: representation of a concrete entity as a value in memory.
For C++ synonymous to value.

Object type: a pattern for storing and modifying values in memory.
For C++ synonymous to value type.

Partially formed state of an object: if the object can be assigned to
(left hand side) or destructed.
If the object is not also well-formed nothing else is defined.

pointer(T): type constructor from type T to pointer of type T.

Precondition: properties of particular objects.

Procedure: sequence of instructions that modify the state of some objects or
construct or destroy them.

Procedure input/output, direct/indirect passings, local/global/own state: obvious notions
for objects dealt with.

Refinement: A concept C' refines a concept C, if whenever C' is satisfied for a set
of types, C is also satisfied for these types. 

Memory, address, content, lengths: a set of words (values), each with an address and
a content. Addresses are values of fixed address length, contents are values of fixed
word length.
Ex: Bytes in RAM accessed by e.g. 4-Byte addresses

Properly partial or total object type: iff its value type is properly partial or total.

Properly partial or total value type: if its values represent a proper subset of the
abstract entities in the corresponding species, otherwise it is total.

Regular: a type concept corresponding to the definition of a regular type.

Regular function: if and only if a substitution of an argument by an equal value
yields an equal result.
Ex: non-regular would be a function yielding the numerator of a rational number
(1/2, 2/4 same numbers but different numerator)

Regular procedure: if and only if a substitution of inputs by equal objects
results in equal output objects.

Regular type: if its basis includes equality, assignment, destructor,
default constructor, copy constructor, total ordering, and underlying type.

Representation of a entity: a datum corresponding to a particular entity.

Representationally equal values: if their data are identical sequences of 0s and 1s.

Requires clause: expression built up from constant values, concrete types, formal
parameters, applications of type attributes and type functions, equality on values
and types, concepts, and logical connectives. 

Resources: owned by object to hold its state in memory. Not necessarily contiguous in memory,
opposed to the value being represented as a datum, a contiguous sequence of 0s and 1s. 

Result space for a functional procedure: set of all values from its codomain returned
for inputs from its definition space. 

Snapshot: is a complete collection of the attributes of a concrete entity in a particular
point of time.

Species: abstract or concrete species.

Starting address: unique address from where all resources of an object can be reached.
There is a starting address for every object.

State of object: value of some value type, represented as data in memory. 

Store: change content of an address.

Total ordering: ?

Total object type: see properly partial.

Total value type: see properly partial.

Type: short for value type.

Type attribute: a mapping from a type to a value describing some characteristic of the type.
Ex: sizeof in C++

Type concept: a concept defined on one type.

Type constructor: mechanism for creating a new type from existing types.
Notation for n-ary type constructor C applied to types T_0,...,T_{n-1} is
C_{T_0,...,T_{n-1}}. Example pair_{T_0,T_1}, or analogously for struct's. 

Type function (occasionally indexed): a mapping from a type to an affiliated type.
So this is mapping between concepts (as domain and codomain).
Indexed e.g. when referring to the i'th member of a structure type.

Unambiguous: negation of ambiguous.

Underlying type: Ch. 12 (later)

Uniquely represented object type: iff its value type is uniquely represented.

Uniquely represented value type: if and only if at most one value corresponds to each
abstract entity.
Ex: non-unique would be a number as truth value, any non-zero meaning true.

Value: is the combination of representation (datum) and interpretion (entity).

Value type: a correspondence between a species and a set of datums.

Weakening: a concept C weakens a concept C', whenever C' refines C.

Well-formed datum w.r.t. a value type: if and only if that datum represents an abstract entity.

Well-formed object: iff its state is well-formed. 


## Excercises

1.1 don't see anything to do