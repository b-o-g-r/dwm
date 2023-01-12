# DWM
Personal [DWM](https://dwm.suckless.org/) Setup

## Installation
* Install dependencies:
  * `sudo pacman -S dmenu freetype2 libx11 libxft libxinerama`
* Install ST:
  * [Follow the instructions here](https://github.com/b-o-g-r/st)
* Create a folder for the source files in /etc:
  * `sudo mkdir /etc/dwm`
* Enter the newly created folder:
  * `cd /etc/dwm`
* Clone the repository:
  * `sudo git clone https://github.com/b-o-g-r/dwm.git .`
* Compile:
  * `sudo make clean install`
