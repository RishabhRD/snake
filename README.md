# Snake

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

![Intro screen](https://user-images.githubusercontent.com/26287448/157916040-fb58ae13-f1e8-4469-a72d-d31985309f73.png)
![Game screen](https://user-images.githubusercontent.com/26287448/157916059-9884628a-f2f2-42d9-a79f-ef0500c68700.png)
