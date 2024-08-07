# Snake

**NOTE: Unstable branch use snakev1 for gameplay right now**

A snake game trying to be reasonable. My main motive of writing this snake game is to test my programming skills.
What I tried to enforce throught the program:

-   Game Logic should not be mixed with viewing game
-   Instead of using MVC design, used Action Model View Architecture
-   Unidirectional data flow
-   Updating state function to be pure
-   Side effects like random fruit generation should be injected
-   Testability of each state of game (bcz side effect is injected)
-   Value semantics
-   No use of pointers
-   No inheritance
-   Polymorphic use with value semantics

## Screenshots

<img src="https://user-images.githubusercontent.com/26287448/157916040-fb58ae13-f1e8-4469-a72d-d31985309f73.png" alt = "Intro Screen" width=200> <img src="https://user-images.githubusercontent.com/26287448/157916059-9884628a-f2f2-42d9-a79f-ef0500c68700.png" alt = "Game Screen" width=200>

## Installation

    cmake -B build/
    cmake --build build
    build/src/snake

## Why such goals

I wanted the game to be highly testable... That's it.

(And maybe I used to hate my past codes... They were full of pointers)

### Game logic should not be mixed with viewing game

If game logic would be mixed with view of game, then ofcourse no tests can be automated. So, this was easy choice to make.

### Instead of using MVC design, use Action-Model-View Architecture + Unidirectional data flow

I realized with my past experience, I mess up a lot when data flow is cyclic.
Unidirectional data flow gives natural flow of data within application. And I
feel everything starts to look so elegant and reasonable.

And these feelings became concrete when I watched [Squaring the Circle](https://youtu.be/67MmJSw4bxo) cppcon talk from Juan Pedro Bolivar Puente.
He explained Action-Model-View architecture where all these three blocks were values not objects.

### Updating state function to be pure

So, the game has an obvious side effect, random fruit generation. I realized
that if I randomly generate the fruit while updating state, I can't predict
what is next state.

So, how I managed the situation was I injected the values that require side
effects from outside of update function e.g., next fruit location, current time.

Now, this next fruit location can be random or in tests we can just pass the test value.

### Testability of each state of program

When I was doing these hardwork, I really wanted these to be unit testable.

### Value semantics

Passing things around with moving values, etc gives a very composable
structure. The best thing about passing by value is that argument passed is
never dangling. No need to check that. And thus things are locally reasonable.
The Legendary Sean Parent gave a lot of talks on this.

f(x) ---> x = f(x)

Using references/pointers carelessly just starts to look worse.

If there is some input argument, that I just have to read, I passed it by const reference.

### No use of pointers

I have been in the pain of using shared_ptr, weak_ptr, unique_ptr, etc. And it hurts.
I really want to focus on business logic.

### No Inheritance

First time I heard it from Sean Parent. And I realized, as we start to use
inheritance for interface, we need to use pointers, dynamic memory allocations,
etc. And it looks bad I said that.

### Polymorphic use with value semantics

Well Sean Parent showed how type erasure can make inheritance an implementation
detail and achieve value semantics. But if the type hierarchy is closed, we can
use `std::variant` and there is no need for virtual function call or dynamic
memory allocation. So, I used that.

## Motivations

-   Value semantics + No inheritance (SEAN PARENT)
-   Polymorphic usecase with value semantics (SEAN PARENT)
-   Saperation of View and Model (My experience of writing bad programs)
-   Unidirectional data flow (My past pains, Juanpe cppcon talks)
-   Updating state to be pure (Juanpe cppcon talks)
-   Side effects to be injected (Bartosz Milewski blogs and functional programming craze)
-   Testability of each state of game (My fantasy after writing worse programs)
-   No pointers (I don't want to check if they are null and even then incorrect)
