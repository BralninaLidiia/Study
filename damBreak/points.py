#!/usr/bin/env python

###
### This file is generated automatically by SALOME v9.14.0 with dump python functionality
###

import sys
import salome

salome.salome_init()
import salome_notebook
notebook = salome_notebook.NoteBook()
sys.path.insert(0, r'/home/chrt/OpenFOAM/chrt-v2406/run/damBreak')

###
### GEOM component
###

import GEOM
from salome.geom import geomBuilder
import math
import SALOMEDS


geompy = geomBuilder.New()

O = geompy.MakeVertex(0, 0, 0)
OX = geompy.MakeVectorDXDYDZ(1, 0, 0)
OY = geompy.MakeVectorDXDYDZ(0, 1, 0)
OZ = geompy.MakeVectorDXDYDZ(0, 0, 1)
Vertex_1 = geompy.MakeVertex(0, 0, 0)
Vertex_2 = geompy.MakeVertex(2, 0, 0)
Vertex_3 = geompy.MakeVertex(2.16438, 0, 0)
Vertex_4 = geompy.MakeVertex(4, 0, 0)
Vertex_5 = geompy.MakeVertex(0, 0.32876, 0)
Vertex_6 = geompy.MakeVertex(2, 0.32876, 0)
Vertex_7 = geompy.MakeVertex(2.16438, 0.32876, 0)
Vertex_8 = geompy.MakeVertex(4, 0.32876, 0)
Vertex_9 = geompy.MakeVertex(0, 4, 0)
Vertex_10 = geompy.MakeVertex(2, 4, 0)
Vertex_11 = geompy.MakeVertex(2.16438, 4, 0)
Vertex_12 = geompy.MakeVertex(4, 4, 0)
geompy.addToStudy( O, 'O' )
geompy.addToStudy( OX, 'OX' )
geompy.addToStudy( OY, 'OY' )
geompy.addToStudy( OZ, 'OZ' )
geompy.addToStudy( Vertex_1, 'Vertex_1' )
geompy.addToStudy( Vertex_2, 'Vertex_2' )
geompy.addToStudy( Vertex_3, 'Vertex_3' )
geompy.addToStudy( Vertex_4, 'Vertex_4' )
geompy.addToStudy( Vertex_5, 'Vertex_5' )
geompy.addToStudy( Vertex_6, 'Vertex_6' )
geompy.addToStudy( Vertex_7, 'Vertex_7' )
geompy.addToStudy( Vertex_8, 'Vertex_8' )
geompy.addToStudy( Vertex_9, 'Vertex_9' )
geompy.addToStudy( Vertex_10, 'Vertex_10' )
geompy.addToStudy( Vertex_11, 'Vertex_11' )
geompy.addToStudy( Vertex_12, 'Vertex_12' )


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
