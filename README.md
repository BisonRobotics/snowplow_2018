# Thundar 3.0 
## Autonomous Snowplow 

## Overview 

This is the repo for Bisons Robotic's robot for the [Institute of Navigation (ION)](http://www.autosnowplow.com/welcome.html) competition. The group meets every Tuesday from 3pm to 5pm in the Auxillay Enterprises building and sometimes random meetings in the week. We also use Groupme to communicate with the entire group like the rest of [Bison Robotics](http://www.ndsubisonrobotics.org/). We have some files on the [Bison robotic's Google drive](https://drive.google.com/drive/folders/0Bx21BgDrMVqsMk5uX25LN2Y3cW8?usp=sharing) including the presentations for the competition.
## The Competition 

The [Rulebook](http://www.autosnowplow.com/rulebooks_files/Autonomous%20Snowplow%20Rulebook,%202017.2.pdf) defines the challenge in a short 23 pages. Basically, the main challenge is to autonomously plow 2 different fields of snow with obstacles.
### Snow Fields
The first field is call the "single-I". It is a single strip roughly 1 meter wide by 10 meters with snow being 5.0cm to 15cm deep. The "triple-I" is three "single-I" next to each other so it is 3 meters wide by 10 meters long and the same depth as the single-I. There will be 2 obstacles randomly placed throughout each field. One is a stationary obstacle that will be placed randomly in the snow field when they set up the field. The other obstacle is the Moving obstacle which will be


## Snowplow computer info 
The snowplows’ computer runs the Xubuntu 16.04. You can either access it either through SSH, x2go, or a normal mouse and keyboard. 

Computer name: snowplow
ip address: 192.168.0.5
Username: thundar
password: BRsnowplow18 

router info: 
SSID:
password: BRsnowplow18
config info: usr:admin pass:admin 

### To connect over SSH: (CLI interface)
1. Power on the computer and router.
2. Connect your computer to the router either with WIFI or Ethernet cable.
3. Open a terminal and run ssh thundar@192.168.0.5
4. The first time you connect it will prompt you about accepting the connection type yes 
5. enter password for user thundar
6. and you are in!!

### To connect with X2go: (remote desktop) 
1. Power on the computer and router.
2. Connect your computer to the router either with WIFI or Ethernet cable.
3. Open x2go client software
4. create a session. give the session a name Host: 192.168.0.5 login: thundar session type: XFCE 
5. click OK
6. click on the session you just created on the right side.
7.enter password
8. you should be connected.

