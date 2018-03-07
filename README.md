# debpac
A debian package creator assistant. [![Build Status](https://travis-ci.org/thibDev/debpac.svg?branch=master)](https://travis-ci.org/thibDev/debpac)

## Development status

Features | State
------------ | -------------
Drag & Drop | ![progress](http://progressed.io/bar/100)
Rename package name | ![progress](http://progressed.io/bar/100)
Change package version | ![progress](http://progressed.io/bar/100)
Add postinst/preinst script | ![progress](http://progressed.io/bar/100)
Add postrm/prerm script | ![progress](http://progressed.io/bar/100)
Add .desktop file | ![progress](http://progressed.io/bar/100)
Syntaxic coloration for file editing | ![progress](http://progressed.io/bar/80)
Reorganise tree | ![progress](http://progressed.io/bar/100)
Type of file recognise by "magic number" | ![progress](http://progressed.io/bar/65)
Save package project | ![progress](http://progressed.io/bar/100)
Restore package project | ![progress](http://progressed.io/bar/100)
Generate package | ![progress](http://progressed.io/bar/100)

First release progress ![progress](http://progressed.io/bar/90)

## Requirements

- qt5-default
- gksu

## Installation

```shell
git clone https://github.com/thibDev/debpac.git
cd debpac
mkdir build
cd build
qmake ../debpac.pro
make && make clean
```

## How to use

![Demo debpac](preview/use_debpac.gif)

### Support development :+1:

Star the project :star:

### Credits

Icons | Author
------------ | -------------
binary<br>file<br>diskette<br>generate<br>add_script<br>about<br>credits<br>import | Icon made by Freepik<br>https://www.flaticon.com/authors/freepik
audio<br>package<br>image | Icon made by Buddhe<br>https://www.flaticon.com/authors/pixel-buddha
archive | Icon made by Roundicons<br>https://www.flaticon.com/authors/roundicons
folder | Icon made by Smashicons<br>https://www.flaticon.com/authors/smashicons
desktop | Icon made by vectors Market<br>https://www.flaticon.com/authors/vectors-market
