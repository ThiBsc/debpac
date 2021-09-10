# debpac
A debian package creator assistant. [![Build Status](https://travis-ci.org/ThiBsc/debpac.svg?branch=master)](https://travis-ci.org/ThiBsc/debpac)

This package is available in [termux-x11-packages](https://github.com/termux/x11-packages) and maintained by [Yisus7u7](https://github.com/Yisus7u7)

## Development status

> **Last update**:  
Remove `gksu` dependency (removed from ubuntu)  
To use TERMUX_PATH (`/data/data/com.termux/files/`), add the following line in the `debpac.pro` file:
>```
>DEFINES += USE_TERMUX_PATH
>```

In the next version:

Features | State
------------ | -------------
Tooltip on tree element hover | ![progress](http://progressed.io/bar/100)
Improve the syntaxic coloration for file editing | ![progress](http://progressed.io/bar/0)
Improve the number of file type recognition by "magic number" | ![progress](http://progressed.io/bar/0)

Second release progress ![progress](http://progressed.io/bar/33)

## Requirements

- qt5-default

## Installation

### Manual compilation
```shell
git clone https://github.com/thibsc/debpac.git
cd debpac
mkdir build
cd build
qmake ../debpac.pro
make && make clean
```
### Termux package
```shell
pkg install debpac
```

## How to use

![Demo debpac](preview/use_debpac.gif)

### Support development :+1:

* Star the project :star:
* You can fork the project and implement the features in the _development status section_

### Credits

Icons | Author
------------ | -------------
binary<br>file<br>diskette<br>generate<br>add_script<br>about<br>credits<br>import | Icon made by Freepik<br>https://www.flaticon.com/authors/freepik
audio<br>package<br>image | Icon made by Buddhe<br>https://www.flaticon.com/authors/pixel-buddha
archive | Icon made by Roundicons<br>https://www.flaticon.com/authors/roundicons
folder | Icon made by Smashicons<br>https://www.flaticon.com/authors/smashicons
desktop | Icon made by vectors Market<br>https://www.flaticon.com/authors/vectors-market
