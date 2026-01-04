# 🕒 jtime

A lightweight, terminal-based (TUI) digital clock designed for the computer terminal. It features a custom "Big Font" display, current date, and real-time weather data for Melbourne, Australia.

## ✨ Features
* **Big Character Rendering:** Custom ASCII-mapped font for high visibility.
* **Real-time Weather:** Fetches live temperature, "Feels Like" stats, and wind speed from `wttr.in`.
* **Dynamic Colors:** Support for command-line arguments to change clock color (Red, Blue, Green, Yellow).
* **Smart Updates:** Hardware-efficient; updates the clock every second but fetches weather only every 15 minutes to save data and prevent API throttling.
* **System Integration:** Designed to be installed as a system-wide binary.

---

## Installation

1. Prerequisites:
You will need the `ncurses` library and `curl` installed on your Raspberry Pi:
```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev curl

2. Clone and Build:
git clone https://github.com/jalalferoj/jtime.git
cd jtime
make

3. Install System-Wide:
sudo make install

Usage:
Once installed, you can run the clock from any directory:
Command  Result
jtime    Starts the clock with the default Green color.
jtime red    Starts the clock in Red.
jtime blue   Starts the clock in Blue.
jtime yellow   Starts the clock in Yellow.
Controls: * Press 'q' to quit the application safely and restore your terminal.

Customization:
To change the city from Melbourne to your local area, edit the get_weather function in myclock.c:
// Change 'Melbourne' to your city name
fp = popen("curl -s 'wttr.in/YOUR_CITY?format=%t+Feels:%f+Wind:%w' ...", "r");
After editing, run make and sudo make install again.




