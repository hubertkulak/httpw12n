# httpw12n

ESP32 esp-idf web-server project

## Setup from scratch

### Set up the esp-idf toolchain

NOTE: The ESP-IDF build system does not support spaces in the paths to either ESP-IDF or to projects.

#### Linux

esp-idf setup src: <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html>

First, install all dependencies.

```console
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 gcc
```

Get ESP-IDF toolchain directly from git

```console
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

Then

```console
cd ~/esp/esp-idf
./install.sh esp32
```

make sure to export the environmental variables.

```console
. ./export.sh
```

#### Windows

follow the installation process from here: <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html>

### Build our project

Create projects direcory (in `/esp-idf`)

```console
mkdir projects && cd projects
```

#### Clone the repo

```console
git clone https://github.com/hubertkulak/httpw12n
```

#### Wifi credentials

Before building make sure to set up your wifi credentials in sdkconfig file

```console
CONFIG_ESP_WIFI_SSID="name_of_your_network"
CONFIG_ESP_WIFI_PASSWORD="password_to_it"
```

#### Build the code

Building the code is done with the `idf.py` script. Make sure to be in `/httpw12n` dir

```console
cd projects/httpw12n
idf.py build
````

note: building for the first time may take a while since all of the esp-idf tools  are also building. If fails enter ```idf.py set-target esp32``` and try again.

#### Flashing the device

On linux the port should be `/dev/ttyUSB0` If not, change accordingly.
On windows it will be one of the ```COM``` ports.  

```console
idf.py -p /dev/ttyUSB0 flash
```

note: For some reason (mostly in ubuntu based systems) esp-idf may not be able to detect the connection. If so, try: ``sudo chmod 0777 /dev/ttyUSB0`` and flash again.

#### Read the IP address of the website

The IP address can be read from serial monitor:

```console
idf.py monitor
```

(hint: to exit the monitor hit Ctrl+])

#### Connect to the webstie

Enter the IP address into your web browser. Make sure to be connected to the same wi-fi as the ESP! (If for some reason ESP does not connect, reflash the board)
