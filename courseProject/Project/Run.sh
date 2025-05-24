#!/bin/bash
blockMesh
transformPoints -scale '(0.001 0.001 0.001)'
pimpleFoam > solver.log 2>&1
paraFoam
