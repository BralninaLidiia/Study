#!/bin/bash
rm -rf 0.*
rm -rf 1
rm -rf constant/polyMesh
rm 0/alpha.water
cp 0/alpha.water.orig 0/alpha.water
echo Done
