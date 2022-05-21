#!/bin/sh

# How to check these properties of a client?
# The xprop utility can be used to get this information: WM_CLASS is (instance, class), WM_NAME (or _NET_WM_NAME) is the title.
# For example this shell script prints the relevant properties of the selected client (if the properties does not contain '=' or ','):
# https://dwm.suckless.org/customisation/rules/

xprop | awk '
	/^WM_CLASS/{sub(/.* =/, "instance:"); sub(/,/, "\nclass:"); print}
	/^WM_NAME/{sub(/.* =/, "title:"); print}'
