
Debian
====================
This directory contains files used to package qualcoind/qualcoin-qt
for Debian-based Linux systems. If you compile qualcoind/qualcoin-qt yourself, there are some useful files here.

## qualcoin: URI support ##


qualcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install qualcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your qualcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/qualcoin128.png` to `/usr/share/pixmaps`

qualcoin-qt.protocol (KDE)

