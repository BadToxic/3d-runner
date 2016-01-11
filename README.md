# 3D Runner

## Introduction

_3D Runner_ is an open source homebrew game that is created to run on _Nintendos 3DS_ handheld family (_3DS_, _3DS XL_, _2DS_, _New 3DS_ and _New 3DS XL_).

It is a simple 2D sidescroller but with stereoscopic 3D. You can controll a little guy on the left of the upper screen, running to the right, avoiding obstacles by jumping.

## What you need to play

If you just want to play it, you need any _3DS_ device prepared to run homebrew. If you don't have a prepared device and don't know about how to do it or even what it is, you can start by checking this site: http://smealum.github.io/3ds
This "soft" way of hacking is not dangerous or illegal. It won't damage your device and is reversible at any time.
These hacks are using exploits in games or in the intern browser to run some code from your (micro) SD card that is able to launch other applications - the homebrew launcher.
Currently every firmware version of the _3DS_ family is supported (today's version is _10.3.0-28_).

## How to play

The player is automatically running to the right, speeding up at the beginning. From time to time gaps in the ground will appear the player has to jump over. If he falls down out of the screen, the game is over.

**Controlls:**
_Jump_ (While on ground): **A**, **UP**, **L**
_Jumpkick_ (While in the air): **B**, **RIGHT**
_Slide_ (While on ground): **B**, **DOWN**
_Restart_: **SELECT**
_Quit_: **START**

## What you need for coding and building

If you want to setup your machine for developing you can start here: http://www.3dbrew.org/wiki/Setting_up_Development_Environment

I installed:
- **_devkitPro_** with **_devkitARM_** that contains **_ctrulib_**
- **_sf2dlib_** a simple and Fast 2D library for the Nintendo _3DS_ (using _ctrulib_) 



