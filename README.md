# 🕒 jtime

A lightweight, terminal-based (TUI) digital clock designed for the computer terminal. It features a custom "Big Font" display, current date, and real-time weather data for Melbourne, Australia.

## ✨ Features
* **Big Character Rendering:** Custom ASCII-mapped font for high visibility.
* **Real-time Weather:** Fetches live temperature, "Feels Like" stats, and wind speed from `wttr.in`.
* **Dynamic Colors:** Support for command-line arguments to change clock color (Red, Blue, Green, Yellow).
* **Smart Updates:** Hardware-efficient; updates the clock every second but fetches weather only every 15 minutes to save data and prevent API throttling.
* **System Integration:** Designed to be installed as a system-wide binary.

---

## Information
A beautiful terminal clock with Melbourne weather for Linux.

## Installation
You will need the `ncurses` library and `curl` installed on your Raspberry Pi:
```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev curl
git clone https://github.com/jalalferoj/jtime.git
cd jtime
make
sudo make install

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

Example - This is what I have done below:
pi@pi:~ $ sudo apt update
pi@pi:~/jtime $ sudo apt install libncurses5-dev libncursesw5-dev curl
pi@pi:~ $ git clone https://github.com/jalalferoj/jtime.git
Cloning into 'jtime'...
remote: Enumerating objects: 12, done.
remote: Counting objects: 100% (12/12), done.
remote: Compressing objects: 100% (11/11), done.
remote: Total 12 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Receiving objects: 100% (12/12), 10.88 KiB | 506.00 KiB/s, done.
pi@pi:~ $ cd jtime
pi@pi:~/jtime $ make
gcc jtime.c -o jtime -lncurses
pi@pi:~/jtime $ sudo make install
install -m 755 jtime /usr/local/bin/jtime
pi@pi:~/jtime $ nano ~/.bashrc
inside ~/.bashrc go all the way to the bottom and paste the code below and save it, time will open in terminal whenever you open your terminal and press q to exit clock:
jtime -s -c -C 2
then run in the terminal: jtime







