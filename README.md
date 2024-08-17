# Snake

A snake game trying to be reasonable. My main motive of writing this snake game is to test my programming skills.
What I tried to enforce throught the program:

- Game Logic should not be mixed with viewing game
- Local Reasoning of functions
- Design by contract
- Generic Programming

## Screenshots

<img src="https://user-images.githubusercontent.com/26287448/157916040-fb58ae13-f1e8-4469-a72d-d31985309f73.png" alt = "Intro Screen" width=200> <img src="https://user-images.githubusercontent.com/26287448/157916059-9884628a-f2f2-42d9-a79f-ef0500c68700.png" alt = "Game Screen" width=200>

## Installation

    ./update_package
    ./build

## Why such goals

I wanted the game to be highly testable... That's it.

(And maybe I used to hate my past codes... They were full of pointers and irrelevant dependencies)

## Motivations

- Design by contract (SEAN PARENT and DAVE ABRAHAMS)
- Value semantics + No inheritance (SEAN PARENT)
- Polymorphic usecase with value semantics (SEAN PARENT)
- Saperation of View and Model (My experience of writing bad programs)
- Unidirectional data flow (My past pains, Juanpe cppcon talks)
- Updating state to be pure (Juanpe cppcon talks)
- Side effects to be injected (Bartosz Milewski blogs and functional programming craze)
- Testability of each state of game (My fantasy after writing worse programs)
- No pointers (I don't want to check if they are null and even then incorrect)
- Relationships (SEAN PARENT)

## Take Aways

- Think of preconditions and post-conditions while writing a function.
- Only argument types doesn't define the domain of the function, but precondition + types do
- Violating precondition is not an error but a bug. So stop handling precondition violation.
- Try to provide APIs where its hard to violate preconditions. Use your type-system.
- Inability to satisfy post-condition is an error.
- While testing a function, post-conditions should be tested and maybe we can move towards proofs someday.
- With composition of functions, there is logical composition of preconditions and post-conditions that would define correctness of program.
- Stronger precondition and weaker post-condition leads to less responsibility of function. So we should crave for that. However, should not trade efficiency for the same.
- Classes should try to have one responsibility and that is to maintain the class invariants.
- If post-conditions and class invariants are getting complex think of if its the right design.
- Generic programming really helps to achieve the same. Generic programming approach try to depend on minimal requirements that is enough to achieve the post-conditions.
- For writing generic functions, its important to understand the relationships. Sean Parent's talk on Better Code: Relationships would help. https://youtu.be/ejF6qqohp3M
- Try to provide generic and efficient basis for the class that free functions can use to achieve use-case related tasks. (Its really hard, most of the time goes into realizing what exactly is this thing...)
- Algorithms are important learn them.
