# Command Line Chess
## About the project
After a few months of on and off work with the little free time I had, I finally finished my chess cmd line project in c++. It works great and allows you to have 
full chess functionality including castling and en passant. There are also endgame checks for checkmate and stalemate to see who won or caused a tie game.
It also includes a saveslot system which is infinitely expandable where you can save, load, or delete savefiles to saveslots. I learned a lot while making this
project like how to use fstream, basic object oriented programming, game loops/logic, and more about vectors than I previously knew, but the worst part about making the project was testing every situation by hand.
This is the single file solution which is how I made it originally having no sense or organization at the time.
## How To Run
### Downloading The Code
Download the code and make file as follows
Git:
1. ```git clone https://github.com/zach-lawrence-1/Chess-Single-File.git c```
   - c can be any local directory you want.
2. ```cd c```

OR

Just download zip from github and unzip where you want
### Windows
On windows, as long as you have MSYS2 setup with g++ and you can run make files then you should be able to run the main program clock_ND.cpp as follows:
1. Download code and make file.
2. Open a terminal in the same directory as the code and make file.
3. Type in ```make```
4. run ```./chess.exe``` or ```./chess```

## Project Images

Main board:

<img width="654" alt="main board" src="https://github.com/user-attachments/assets/e71c2b98-4a72-47f5-9a69-e83e82830fba">

Piece being killed and sent to the killzone:
<img width="639" alt="killed" src="https://github.com/user-attachments/assets/57651fa9-7287-4daa-8846-f9e4a629728d">

Infinitely expandable save slots:
<img width="653" alt="saveslot" src="https://github.com/user-attachments/assets/21f5b065-d481-435e-9ca8-494a36c5c3a8">
