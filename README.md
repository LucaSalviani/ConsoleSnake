# Console Snake
#### Video Demo:  https://youtu.be/tj2-_NJhyMM
#### Description:

**Console Snake** is a modern take on the classic snake game, built specifically for the Windows console. It features smooth, responsive gameplay, a custom-configured console environment, and a unique **Game Talker** that interacts dynamically with the player through text-based messages. The game retains the traditional mechanics of snake while introducing enhanced features like score saving, animations, and a user-friendly interface designed for an immersive experience.  

## Installation  
The game is a simple executable! Just download, run, and play.  

I have tested it on Windows 10 and 11 across different computers, and it works on all of them. The only caveat is that, like any unregistered software, Windows may warn you that it could be a potential virus. Rest assured, it's completely safe!  

## How to Play  
The objective of **Console Snake** is simple: control the snake, eat food to grow, and survive as long as possible without crashing into walls or yourself. The game follows the traditional mechanics of the classic Snake game but includes some additional features to enhance the experience.  

### Controls  
- **Arrow keys** – Move the snake in the desired direction (Up, Down, Left, Right).  
- **Spacebar** – Pause or resume the game.  
- **R key** – After losing, hold R to restart the game immediately.  

### Game Rules  
- The snake moves continuously in the chosen direction.  
- Eating food increases the score by **1 point** and extends the snake’s body by **1 segment**, making movement more challenging as the game progresses.  
- **Colliding with the walls or your own body results in an instant game over.** Unlike some snake games where you can wrap around the screen, here you must carefully navigate to avoid crashing.  

## Features  
### **Game Talker** – Interactive Dialogue System  
One of the most unique aspects of **Console Snake** is the **Game Talker**, a dynamic text-based narrator that reacts to player actions and events during gameplay. It appears in the **bottom-right corner of the screen** and provides a variety of messages, making each playthrough more engaging. Some of the interactions include:  
- **Warnings when approaching or hitting a border.**  
- **Encouraging messages when reaching certain score milestones.**  
- **Humorous or randomized responses** to prevent repetition in different playthroughs.  

### **Special Animations and Milestone Effects**  
At **100 points**, the game triggers unique visual animations to celebrate the player's achievement, adding an extra layer of excitement.  

### **Score Saving System**  
When the player loses, an **animated Game Over screen** appears, followed by a prompt asking whether to save the score. If the player chooses to save it:  
- The score is stored in a file.  
- It is automatically **sorted in descending order** with previous records.  
- The **top 3 scores** are **highlighted with special tags**.  
- If there are too many scores to display at once, a **scrolling system** is enabled, allowing players to navigate through the leaderboard.  

### **Quick Restart Functionality**  
Rather than navigating menus to restart, the game features a **quick restart system**. After losing, the player can **hold down the R key** to instantly reset the game loop and start a new round without delay.  

## Summary  
With its simple yet engaging mechanics, interactive dialogue system, and score-saving features, **Console Snake** delivers a fun and immersive retro gaming experience while maintaining the charm of the classic Snake game. Whether you're aiming for a high score or just looking for a nostalgic challenge, this game provides a polished and entertaining experience in the console environment!  

## Code Structure

The game was developed in **Visual Studio** (not Visual Studio Code) in my personal codespace. Initially, I started by building everything in a single main file. However, as the project grew, I realized (and was advised) to modularize the code into separate libraries. This was my first time modularizing a project of this scale, so it presented a learning opportunity. I decided to split the code into **four libraries** aside from the main program.

### Libraries Breakdown

1. **Game Library**  
   This library handles all the gameplay-related functions. Its responsibilities include:
   - Managing the snake’s food.
   - Handling player controls (movement and pause functionality).
   - Implementing the **Game Talker** to provide interactive text-based dialogue.
   - Managing the **score records**: reading, sorting, and writing scores to the record file.

2. **Snake Library**  
   This library focuses on the snake’s features and behavior:
   - Collision detection (with walls and the snake itself).
   - Updating the snake's segments in the correct order and position.
   - Adding new segments to the snake’s body as it eats food.
   - Drawing the snake to the screen.
   - Memory management, ensuring that memory used by the snake is properly freed.

3. **Utils Library**  
   This library contains all the non-gameplay-related functions, primarily related to the console and auxiliary operations to ensure smooth performance. The most challenging part of the game’s development was working with the **Windows API**. Key functionalities include:
   - **Console window management**: Adjusting the console size and removing scrollbars.
   - Enabling **ANSI escape codes** for text formatting.
   - Disabling default console features like resize, maximize, quick edit, and text selection.
   - Text positioning and font size management.
   - Implementing a **color randomizer** and special effects for text colors.
   - Handling **seed randomization** for game randomness.
   - **Input reading** with support for special characters and error handling to keep the record file clean.
   - A buffer-cleaning function to maintain smooth game performance.

4. **Art Library**  
   This library contains all the visual components of the game, such as artwork, dialogues, colors, and other essential visual features. Responsibilities include:
   - Drawing points, numbers, the game title, game over screen, controls, dialogues for the **Game Talker**, and special animations.
   - Screen clearing and cleaning functions to ensure the display is refreshed correctly.

### Main Function

The **main function** acts as the entry point for the game. It is implemented as a **Windows application** (not a console application). Upon execution, it calls the console (using **conhost**), ensuring the game works properly in the console environment, as it does not function correctly in the **Windows Terminal**. 

The game operates on a **tick system** that synchronizes game events, and it uses various conditionals and loops to manage the different stages of the game: title screen, gameplay, and game over screen.

## Design Choices and Challenges
During the development of the game, I faced several key design choices and challenges. The first major decision was to modularize the game. While I was familiar with the concept of modular programming, I had never applied it on this scale. Modularizing the code greatly improved maintainability and scalability, and it allowed me to split the game into smaller, more manageable components.

One of the biggest challenges at the beginning was implementing dynamic snake growth while ensuring a properly functioning collision system. I came up with what I consider a clever solution: I used a list of segments to track the position of each segment of the snake. Each segment updates its position based on the segment in front of it on the following tick, with the head updating itself based on user input.

Another important design choice was the addition of the "game talker," a system I created to make the game feel more personal and immersive. I wanted the game to feel like it was interacting with the player. The challenge here was designing a dialogue system that triggers when specific milestones are reached, or when the snake collides with the map borders. The key to success was ensuring that these dialogues appeared smoothly without interrupting gameplay. Coordinating the game’s different features was essential to making this work seamlessly.

I also decided to implement a record-keeping system for the game. Initially, I thought it would be fun to have a file with records of my friends’ scores on my computer. This feature turned out to be more challenging than expected, particularly when it came to ensuring that the scoreboard would work efficiently and remain stable, especially when handling more than 15 records. I focused on creating a system that would prevent the game from breaking or displaying errors as the number of records grew. One of the most interesting and complex aspects was designing a scroll bar that would function seamlessly when the number of records exceeded a certain threshold. This allowed the user to easily navigate through the scores without issues. The record system, in my opinion, is one of the most impressive parts of the game—it looks great and works flawlessly, even under heavy use.

The biggest challenge, however, was ensuring the game ran properly within the console environment. Initially, I struggled with the game not running as expected, and I suspected that some features required administrator permissions. This frustration grew as I realized that the console settings were crucial to making the game function correctly. I had to ensure that the game window felt like a native application, not a typical console app, and that it didn’t break when the user resized, scrolled, or interacted with the console in other ways. I accomplished this using the Windows API, which presented its own set of challenges. I had to learn about advanced concepts such as handles, pipes, buffers, and other features I wasn’t initially familiar with.

Eventually, I discovered that the issue wasn’t related to administrator permissions but rather to the console environment itself. When the game was opened with admin-level permissions, it would launch in the older, more powerful conhost console, not the newer Windows Terminal (which is dependent on conhost). To fix this, I focused on finding a way to ensure the game always opened conhost instead of the Windows Terminal whitout the need of admin-level permissons. I tested various approaches until I settled on two main options. The first solution involved opening the game in a console, then reopening it as a child process in conhost while killing the parent process. While functional, this approach felt a bit messy. The second, more elegant solution involved creating a Windows application and allocating a console to it, which automatically opened conhost. This solution worked flawlessly, and now the game runs smoothly without requiring administrator permissions.

## Resources used
- [Windows API Documentation](https://learn.microsoft.com/en-us/windows/win32/)
- An ASCII art text generator which helped design some of the game features: [TAAG Generator](https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20)
- Google, Stack Overflow, YouTube, sweat, and tears :)

## About the creator
Luca Salviani is a 24-year-old systems engineering student from UTN University, Buenos Aires, Argentina, and loves being a nerd.
