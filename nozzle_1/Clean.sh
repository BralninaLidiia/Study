#!/bin/bash
rm -rf 0.*
rm -rf processor*
rm -rf constant/polyMesh
rm -rf geometry/Mesh.unv
rm 0/p
rm log
cp /home/chrt/OpenFOAM/chrt-v2406/run/nozzle_1/p.org 0/p
sed -i '19,23d' params.txt
echo Done
