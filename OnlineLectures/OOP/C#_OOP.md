[C# tutorial for beginners - video 31+](https://www.youtube.com/watch?v=9V5B3dNoVIA&list=PLZPZq0r_RZOPNy28FDBys3GVP2LiaIyP_&index=31)

# Classes

A bundle of related, organised code.

```csharp
static class Messages {
  public static void Hello() {
    Console.WriteLine("Hello! Welcome to the program");
  }

  public static void Waiting() {
    Console.WriteLine("I am waiting for something");
  }

  public static void Bye() {
    Console.WriteLine("Bye! Thanks for visiting");
  }
}
```

`static` makes the method a class method (rather than an object method).

`public` makes the class method accessable outside the class

```csharp
// With static for Messages
Messages.Hello();

// Without static for Messages
Messages messages = new Messages();
messages.Hello();
```

# Objects

An object is an instance of a class. Classes are therefore the blueprint of an object before it is instantiated.

Objects have:
 - fields/ properties (what the class has or characteristics)
 - methods (what the class can do or actions)

```csharp
class Human {
  // insecure use getters and setters instead
  public String name;
  public int age;

  // constructor
  public Human(String name, int age) {
    this.name = name;
    this.age = age;
  }

  void Eat() {
    Console.WriteLine(name + " is eating");
  }

  void Sleep() { 
    Console.WriteLine(name + " is sleeping");
  }
}

class Program {
  static void main(string[] args) {
    // No more manual field asignment
    // Human human1 = new Human(); 
    // human1.name = "Rick";
    // human1.ags = 65;

    Human human1 = new Human("Rick", 65);

    human1.Eat();
    human1.Sleep();
    
    // No more manual field asignment
    // Human human2 = new Human();
    // human2.name = "Morty";
    // human2.ags = 16;

    Human human2 = new Human("Morty", 16);

    human2.Eat();
    human2.Sleep();
    
    Console.ReadKey();
  }
}
```

# The static Modifier

Static makes something a class property rather than an object's property, so all objects have access to the same variable.

```csharp
class Car {
  String model;

  // Making this variable static means that numberOfCars belongs to the class Car not any single Car object. Car objects do share this variable though.
  public static int numberOfCars;

  public Car(String model) {
    this.model = model;
    numberOfCars++;
  }

  public static void StartRace() {
    Console.WriteLine("Race has started!");
  }
}

class Program {
  static void main(string[] args) {
    Car car1 = new Car("Mustang");
    Car car2 = new Car("Corvette");

    Console.WriteLine(Car.numberOfCars); // should be 2
    Car.StartRace();

    Console.ReadKey();
  }
}  
```

In addition `static` applied to a class removes it's ability to be instatiated, meaning it effectively becomes a namespace with it's own internal state.

# Overloading

Overloaded methods **need** a unique signature (method name + parameter types) in order to be valid.

```csharp
class Program {
  static void main(string[] args) {
    Pizza pizza1 = new Pizza(
      "stuffed crust", 
      "tomato", 
      "mozzarella", 
      "pepperoni"
    );

    Console.ReadKey();
  }
}

class Pizza {
  String bread;
  String sauce;
  String cheese;
  String topping;

  public Pizza(String bread, String sauce, String cheese, String topping) {
    this.bread = bread;
    this.sauce = sauce;
    this.cheese = cheese;
    this.topping = topping; 
  }

  public Pizza(String bread, String sauce, String cheese) {
    this.bread = bread;
    this.sauce = sauce;
    this.cheese = cheese;
  }

  public Pizza(String bread, String sauce) {
    this.bread = bread;
    this.sauce = sauce;
  }

  
}
```

# Inheritance

One or more child classer recieving fields/ methods from a parent class. Inheritance removes code reduplication for shared functionality.

The `abstract` keyword implies that a class is used purely for inheritence and is incomplete somehow. This means abstract classes shouldn't be instatiated as a base class.

 
```csharp
class Program {
  static void main(string[] args) {
    Car car = new Car;
    Bisicle bisicle = new Bisicle;
    Boat boat = new Boat;

    // Impossible, Vehical is abstract so can't be instatiated.
    Vehicle vehicle = new vehicle;
    
    Console.ReadKey();
  }
}

abstract class Vehicle {
  public int speed = 0;
  public void go() {
    Console.WriteLine("This vehicle is moving!");
  }
}

class Car : Vehicle {
  public int wheels = 4;
}

class Bicycle : Vehicle {
  public int wheels = 2;
}

 class Boat : Vehicle {
  public int wheels = 0;
}
```


