[Object-oriented Programming in 7 minutes | Mosh](https://www.youtube.com/watch?v=pTB0EiLXUC8)

# Concepts

There are 4 core concepts in OOP:
 - Encapsulation
 - Abstraction
 - Inheritance
 - Polymorphism

In procedural code the program contains functions and variables in memory. This sometimes results in spghetti independency between functions.

## Encapsulation

In OOP objects contain properties (variables) and methods (functions). They are grouped together when the methods rely on and modify the variables.

For example the browser has a local storage object which contains properties and methods.

Another example:
```javascript
let employee = {
  baseSalary: 30_000,
  overtime: 10,
  rate: 20,
  getWage: function() {
    return this.baseSalary + (this.overtime * this.rate)
  }
};

employee.getWage();
```

Here employee contains properties (`baseSalary`, `overtime` & `rate`) and the method `getWage`.

## Abstraction

Abstraction hides certain properties and methods from outside of a class. This makes the interface of an object simpler. It also reduces the impact of change so changes to private attributes doesn't break a codebase.

## Inheritence

Inheritence reduces code duplication. This is part of the don't repeat yourself (DRY) methodology. When multiple classes contain the same properties and methods, a base/abstract class is inherited by child classes to reduce code redundancy.

## Polymorphism

Sometimes it is necessary to group similar objects together, or to treat a child object as a base object. Polymorphism means that an object of a certain type can have many forms (child classes), based on a parent class.

# Advantages

**Encapsulation** Reduces codebase complexity & increases reusability of code.

**Abstraction** Reduces interface complexity for objects by isolating private attributes.

**Inheritence** Reduces code redundancy (DRY methodology).

**Polymorphism** Treats objects more generically (on base class) to group together similar functionality.

