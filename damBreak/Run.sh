#!/bin/bash
ideasUnvToFoam Mesh_1.unv
transformPoints "scale = (0.146 0.146 0.146)"
sed -i '21s/patch/wall/;27s/patch/wall/;33s/patch/wall/;45s/patch/empty/' constant/polyMesh/boundary
setFields
interFoam
paraFoam
