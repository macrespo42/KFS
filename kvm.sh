#!/bin/bash

sudo kvm -m 2048 -s -hda ./kern.img --redir tcp:2323:23 -curses
