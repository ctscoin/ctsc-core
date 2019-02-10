
Debian
====================
This directory contains files used to package ctscd/ctsc-qt
for Debian-based Linux systems. If you compile ctscd/ctsc-qt yourself, there are some useful files here.

## ctsc: URI support ##


ctsc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ctsc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ctsqt binary to `/usr/bin`
and the `../../share/pixmaps/cts128.png` to `/usr/share/pixmaps`

ctsc-qt.protocol (KDE)

