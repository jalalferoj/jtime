## Installation:

sudo apt update

sudo apt install libncurses5-dev libncursesw5-dev curl

git clone https://github.com/jalalferoj/jtime.git

cd jtime

make

sudo make install

jtime


nano ~/.bashrc
jtime -s -c -C 2


# 🕒 jtime

A lightweight, terminal-based (TUI) digital clock designed for the computer terminal. It features a custom "Big Font" display, current date, and real-time weather data for Melbourne, Australia.

## Information
A beautiful terminal clock with Melbourne weather for Linux.

## ✨ Features
* **Big Character Rendering:** Custom ASCII-mapped font for high visibility.
* **Real-time Weather:** Fetches live temperature, "Feels Like" stats, and wind speed from `wttr.in`.
* **Dynamic Colors:** Support for command-line arguments to change clock color (Red, Blue, Green, Yellow).
* **Smart Updates:** Hardware-efficient; updates the clock every second but fetches weather only every 15 minutes to save data and prevent API throttling.
* **System Integration:** Designed to be installed as a system-wide binary.

---



Usage:
Once installed, you can run the clock from any directory:
Command  Result
jtime    Starts the clock with the default Green color.
Controls: * Press 'q' to quit the application safely and restore your terminal.

Customization:
To change the city from Melbourne to your local area, edit the get_weather function in myclock.c:
// Change 'Melbourne' to your city name
fp = popen("curl -s 'wttr.in/YOUR_CITY?format=%t+Feels:%f+Wind:%w' ...", "r");
After editing, run make and sudo make install again.

Example - in your terminal:

pi@pi:~ $ sudo apt update

pi@pi:~/jtime $ sudo apt install libncurses5-dev libncursesw5-dev curl

pi@pi:~ $ git clone https://github.com/jalalferoj/jtime.git

pi@pi:~ $ cd jtime

pi@pi:~/jtime $ make

pi@pi:~/jtime $ sudo make install

pi@pi:~/jtime $ nano ~/.bashrc

Inside ~/.bashrc 

Go all the way to the bottom and paste the code: jtime -s -c -C 2     

Save it.

Time will open in the terminal whenever you open your terminal and press q to exit the clock.









