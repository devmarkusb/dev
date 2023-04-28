#ifndef ENTITIES_H_ix23478gnfyx28gf8gf
#define ENTITIES_H_ix23478gnfyx28gf8gf

#include "util/allthethings.h"

// Representations of the notions in C++:
//      species, value/object type -> type
//      entity, value/object -> object or value of type represented in memory
//      genus -> concept
// An entity belongs to a single species, which also provides rules for its construction or existence.

// abstract species
enum class Color {
    unknown,
    blue, // abstract entity
};

// abstract species
// value type; properly partial, as not all natural numbers can be represented; uniquely represented; unambiguous
struct NaturalNumber {
    // 13 is a well-formed datum, as it represents the interpretation 13 as abstract entity
    int data{}; // datum, representation

    static constexpr NaturalNumber _13() noexcept {
        // abstract entity, despite of a technical lifetime
        // value
        constexpr NaturalNumber _13{13};
        return _13;
    }
};

// abstract species
using Integer = int; // interpretion represented by some fixed number of bits using 2's complement big endian format

// abstract species
struct WholeNumber {};

// abstract genus, the last two species would share
// concept number

// concrete species
enum class Country {
    unknown,
    germany, // concrete entity
};

// concrete species
struct Person {
    // attribute eyeColor
    Color eyeColor{Color::unknown};
    NaturalNumber age{};

    static constexpr Person socrates() noexcept {
        constexpr Person socrates; // concrete entity
        return socrates;
    }
};

// concrete species
struct Cat {};

// concrete genus, the last two species would share
// concept creature

// function
inline NaturalNumber minAge(Person, Person) {
    throw ul::not_implemented{UL_LOCATION};
}

#endif
