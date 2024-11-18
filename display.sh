#!/bin/sh

set -xe

convert -size 496x372 -depth 8 GRAY:Images/out/output.yuv output.png

xdg-open output-0.png

rm output*
