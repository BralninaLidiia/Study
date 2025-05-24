#!/bin/bash
#стандартные процедуры редактирования сетки и ее вывода в paraView
cd /home/chrt/OpenFOAM/chrt-v2406/run/nozzle_1
ideasUnvToFoam /home/chrt/OpenFOAM/chrt-v2406/run/geometry/Mesh.unv
transformPoints -scale '(0.001 0.001 0.001)'
sed -i '23s/patch/wedge/;29s/patch/wedge/;35s/patch/wall/' constant/polyMesh/boundary
setFields
decomposePar
mpirun -np 6 rhoPimpleFoam -parallel >log
reconstructPar
paraFoam
