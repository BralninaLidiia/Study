#!/usr/bin/env python

###
### This file is generated automatically by SALOME v9.14.0 with dump python functionality
###

import sys
import salome
import math

salome.salome_init()
import salome_notebook
notebook = salome_notebook.NoteBook()
sys.path.insert(0, r'/home/chrt/OpenFOAM/chrt-v2406/run/geometry')

### входные параметры
P_input = 200000;
T_input = 1800;
P_output = 9000;
G = 1.5;
alpha_ = 14;
betta_ = 28;
R = 287
k = 1.4

# расчет входного сечения
betta_vh = 0.999
# давление
p_vh = betta_vh*P_input
# температура
T_vh = T_input*betta_vh**((k-1)/k)
# удельный объем
mu_vh = R*T_vh/p_vh
# плотность
ro_vh = 1/mu_vh
# скорость потока
c_vh = math.sqrt(2*k/(k-1)*R*(T_input-T_vh))
# местная скорость звука
a_vh = math.sqrt(k*R*T_vh)
# площадь входного поперечного сечения 
F_vh = G/ro_vh/c_vh
# диаметр входного сечения сопла
d_vh = round(math.sqrt(4/3.14*F_vh)*1e3)


# расчет критического сечения
betta_kr = (2/(k+1))**(k/(k-1))
# давление
p_kr = betta_kr*P_input
# температура
T_kr = T_input*betta_kr**((k-1)/k)
# удельный объем
mu_kr = R*T_kr/p_kr
# плотность 
ro_kr = 1/mu_kr
# скорость потока
c_kr = math.sqrt(2*k/(k-1)*R*(T_input-T_kr))
# местная скорость звука 
a_kr = math.sqrt(k*R*T_kr)
# площадь критического поперечного сечения
F_kr = G/ro_kr/c_kr
# диаметр критического сечения сопла
d_kr = round(math.sqrt(4/3.14*F_kr)*1e3)


# расчет выходного сечения
betta_out = P_output/P_input
# давление
p_out = betta_out*P_input
# температура
T_out = T_input*betta_out**((k-1)/k)
# удельный объем 
mu_out = R*T_out/p_out
# плотность 
ro_out = 1/mu_out
# скорость потока
c_out = math.sqrt(2*k/(k-1)*R*(T_input-T_out))
# местная скорость звука
a_out = math.sqrt(k*R*T_out)
# площадь выходного поперечного сечения
F_out = G/ro_out/c_out
# диаметр выходного сечения сопла
d_out = round(math.sqrt(4/3.14*F_out)*1e3)

# расчетная длина сопла до критического сечения и после
l_left = (d_vh-d_kr)/(2*math.tan(alpha_/2*math.pi/180))
l_right = (d_out-d_kr)/(2*math.tan(betta_/2*math.pi/180))

d_inlet_ = d_vh
d_kr_ = d_kr
d_outlet_ = d_out

r_ = d_kr_
OS_ = r_+d_kr_/2
l1_ = (l_left+l_right)*1.6
l2_ = d_outlet_/5
h_ = d_outlet_*4

arc_left = math.pi*alpha_*r_/180
arc_right = math.pi*betta_*r_/180

# atmosphere height above nozzle
k_height = 177*6/885
# atmosphere width
k_width = (1189.09+152.41+2146.4)/2146.4
# left top atmosphere
k_left_top = (2146.4+30.482)/30.482
# nozzle width
k_nozzle = (1189.09+152.41)/1189.09
# arc left
k_arc_left = (14*3.14*100)/180/628
# arc right
k_arc_right = (28*3.14*100)/180/628

NbSg1 = 15
NbSg2 = 1
NbSg3 = round(l_left*k_nozzle/13.4)

NbSg4 = round(arc_left*k_arc_left*2)
NbSg5 = round(arc_right*k_arc_right)

NbSg6 = round(l_right*k_nozzle/5.7)
NbSg7 = round(l1_*k_width/7)
NbSg8 = round(l2_*k_left_top/360)
NbSg9 = round(h_*k_height/15)

###
### SHAPER component
###

from SketchAPI import *

from salome.shaper import model

model.begin()
partSet = model.moduleDocument()

### Create Part
Part_1 = model.addPart(partSet)
Part_1_doc = Part_1.document()

model.do()


### Create Part
Part_2 = model.addPart(partSet)
Part_2_doc = Part_2.document()
model.addParameter(Part_2_doc, "d_inlet", "d_inlet_", "double")
model.addParameter(Part_2_doc, "d_kr", "d_kr_", "double")
model.addParameter(Part_2_doc, "d_outlet", "d_outlet_", "double")
model.addParameter(Part_2_doc, "alpha", "alpha_", "double")
model.addParameter(Part_2_doc, "betta", "betta_", "double")
model.addParameter(Part_2_doc, "r", "r_", "double")
model.addParameter(Part_2_doc, "OS", "OS_", "double")
model.addParameter(Part_2_doc, "l1", "l1_", "double")
model.addParameter(Part_2_doc, "l2", "l2_", "double")
model.addParameter(Part_2_doc, "h", "h_", "double")
model.addParameter(Part_2_doc, "l_left", "l_left", "double")
model.addParameter(Part_2_doc, "l_right", "l_right", "double")

### Create Sketch
Sketch_1 = model.addSketch(Part_2_doc, model.defaultPlane("XOY"))

### Create SketchLine
SketchLine_1 = Sketch_1.addLine(0, 0, 0, 196)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchPoint_1.result(), True)
Sketch_1.setVertical(SketchLine_1.result(), True)

### Create SketchLine
SketchLine_2 = Sketch_1.addLine(0, 196, 1164.07, 53.07017618975586)
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.startPoint(), True)
Sketch_1.setLength(SketchLine_1.result(), "d_inlet/2", True)

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(0, 0, 1164.07, 0)
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchLine_3.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_3.result(), True)

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(1164.07, 0, 1164.07, 53.07017618975586)
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.startPoint(), True)
Sketch_1.setCoincident(SketchLine_2.endPoint(), SketchLine_4.endPoint(), True)
Sketch_1.setVertical(SketchLine_4.result(), True)

### Create SketchLine
SketchLine_5 = Sketch_1.addLine(1164.07, 0, 1189.07, 0)
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_5.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_5.result(), True)

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(1189.07, 0, 1189.07, 50)
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_6.startPoint(), True)
Sketch_1.setVertical(SketchLine_6.result(), True)

### Create SketchLine
SketchLine_7 = Sketch_1.addLine(1189.07, 0, 1234.07, 0)
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_7.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_7.result(), True)

### Create SketchLine
SketchLine_8 = Sketch_1.addLine(1234.07, 0, 1234.07, 61.21967921461396)
Sketch_1.setCoincident(SketchLine_7.endPoint(), SketchLine_8.startPoint(), True)
Sketch_1.setVertical(SketchLine_8.result(), True)

### Create SketchLine
SketchLine_9 = Sketch_1.addLine(1234.07, 61.21967921461396, 1341.48, 88)
Sketch_1.setCoincident(SketchLine_8.endPoint(), SketchLine_9.startPoint(), True)

### Create SketchLine
SketchLine_10 = Sketch_1.addLine(1234.07, 0, 1341.48, 0)
Sketch_1.setCoincident(SketchLine_7.endPoint(), SketchLine_10.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_10.result(), True)

### Create SketchLine
SketchLine_11 = Sketch_1.addLine(1341.48, 0, 1341.48, 88)
Sketch_1.setCoincident(SketchLine_10.endPoint(), SketchLine_11.startPoint(), True)
Sketch_1.setCoincident(SketchLine_9.endPoint(), SketchLine_11.endPoint(), True)
Sketch_1.setVertical(SketchLine_11.result(), True)
Sketch_1.setLength(SketchLine_11.result(), "d_outlet/2", True)
Sketch_1.setLength(SketchLine_6.result(), "d_kr/2", True)

### Create SketchConstraintAngle
Sketch_1.setAngle(SketchLine_2.result(), SketchLine_3.result(), "alpha/2", type = "Direct", is_active = True)

### Create SketchConstraintAngle
Sketch_1.setAngle(SketchLine_9.result(), SketchLine_10.result(), "betta/2", type = "Direct", is_active = True)

### Create SketchLine
SketchLine_12 = Sketch_1.addLine(1189.07, 50, 1189.07, 150)
SketchLine_12.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_6.endPoint(), SketchLine_12.startPoint(), True)
Sketch_1.setVertical(SketchLine_12.result(), True)
Sketch_1.setVerticalDistance(SketchLine_12.endPoint(), SketchLine_7.startPoint(), 150, True)
Sketch_1.setHorizontalDistance(SketchLine_5.endPoint(), SketchLine_10.endPoint(), "l_right", True)
Sketch_1.setHorizontalDistance(SketchAPI_Point(SketchPoint_1).coordinates(), SketchLine_5.endPoint(), "l_left", True)

### Create SketchArc
SketchArc_1 = Sketch_1.addArc(1188.037388842133, 149.994668428855, 1189.07, 50, 1234.07, 61.21967921461396, False)
Sketch_1.setCoincident(SketchLine_6.endPoint(), SketchArc_1.startPoint(), True)
Sketch_1.setRadius(SketchArc_1.results()[1], 100, True)
Sketch_1.setCoincident(SketchArc_1.endPoint(), SketchLine_8.endPoint(), True)

### Create SketchArc
SketchArc_2 = Sketch_1.addArc(1188.662082948673, 149.9991680149387, 1164.07, 53.07017618975586, 1189.07, 50, False)
Sketch_1.setCoincident(SketchLine_2.result(), SketchArc_2.startPoint(), True)
Sketch_1.setCoincident(SketchLine_6.endPoint(), SketchArc_2.endPoint(), True)
Sketch_1.setCoincident(SketchArc_2.startPoint(), SketchLine_2.endPoint(), True)
Sketch_1.setRadius(SketchArc_2.results()[1], 100, True)
Sketch_1.setLength(SketchLine_5.result(), 25, True)
Sketch_1.setLength(SketchLine_7.result(), 45, True)

### Create SketchLine
SketchLine_13 = Sketch_1.addLine(1306.28, 88, 1341.48, 88)
Sketch_1.setHorizontal(SketchLine_13.result(), True)
Sketch_1.setCoincident(SketchLine_13.endPoint(), SketchLine_9.endPoint(), True)
Sketch_1.setLength(SketchLine_13.result(), "l2", True)

### Create SketchLine
SketchLine_14 = Sketch_1.addLine(1306.28, 88, 1306.28, 792)
Sketch_1.setVertical(SketchLine_14.result(), True)
Sketch_1.setLength(SketchLine_14.result(), "h", True)
Sketch_1.setCoincident(SketchLine_14.startPoint(), SketchLine_13.startPoint(), True)

### Create SketchLine
SketchLine_15 = Sketch_1.addLine(1306.28, 792, 1341.48, 792)
Sketch_1.setCoincident(SketchLine_14.endPoint(), SketchLine_15.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_15.result(), True)
Sketch_1.setLength(SketchLine_15.result(), "l2", True)

### Create SketchLine
SketchLine_16 = Sketch_1.addLine(1341.48, 88, 1341.48, 792)
Sketch_1.setCoincident(SketchLine_9.endPoint(), SketchLine_16.startPoint(), True)
Sketch_1.setCoincident(SketchLine_15.endPoint(), SketchLine_16.endPoint(), True)

### Create SketchLine
SketchLine_17 = Sketch_1.addLine(1341.48, 0, 3487.85, 0)
Sketch_1.setHorizontal(SketchLine_17.result(), True)
Sketch_1.setLength(SketchLine_17.result(), "l1", True)
Sketch_1.setCoincident(SketchLine_17.startPoint(), SketchLine_10.endPoint(), True)

### Create SketchLine
SketchLine_18 = Sketch_1.addLine(1341.48, 792, 3487.85, 792)
SketchLine_18.setName("SketchLine_19")
SketchLine_18.result().setName("SketchLine_19")
Sketch_1.setCoincident(SketchLine_15.endPoint(), SketchLine_18.startPoint(), True)
Sketch_1.setHorizontal(SketchLine_18.result(), True)

### Create SketchLine
SketchLine_19 = Sketch_1.addLine(1341.48, 88, 3487.85, 88)
SketchLine_19.setName("SketchLine_20")
SketchLine_19.result().setName("SketchLine_20")
Sketch_1.setHorizontal(SketchLine_19.result(), True)
Sketch_1.setCoincident(SketchLine_19.startPoint(), SketchLine_9.endPoint(), True)

### Create SketchLine
SketchLine_20 = Sketch_1.addLine(3487.85, 0, 3487.85, 88)
SketchLine_20.setName("SketchLine_21")
SketchLine_20.result().setName("SketchLine_21")
Sketch_1.setCoincident(SketchLine_19.endPoint(), SketchLine_20.endPoint(), True)
Sketch_1.setVertical(SketchLine_20.result(), True)
Sketch_1.setCoincident(SketchLine_20.startPoint(), SketchLine_17.endPoint(), True)

### Create SketchLine
SketchLine_21 = Sketch_1.addLine(3487.85, 88, 3487.85, 792)
SketchLine_21.setName("SketchLine_22")
SketchLine_21.result().setName("SketchLine_22")
Sketch_1.setCoincident(SketchLine_19.endPoint(), SketchLine_21.startPoint(), True)
Sketch_1.setCoincident(SketchLine_18.endPoint(), SketchLine_21.endPoint(), True)
Sketch_1.setVertical(SketchLine_21.result(), True)
model.do()
Sketch_1.changeFacesOrder([[SketchLine_3.result(), SketchLine_4.result(), SketchLine_2.result(), SketchLine_1.result()],
                           [SketchLine_5.result(), SketchLine_6.result(), SketchArc_2.results()[1], SketchLine_4.result()],
                           [SketchLine_10.result(), SketchLine_11.result(), SketchLine_9.result(), SketchLine_8.result()],
                           [SketchLine_7.result(), SketchLine_8.result(), SketchArc_1.results()[1], SketchLine_6.result()],
                           [SketchLine_17.result(), SketchLine_20.result(), SketchLine_19.result(), SketchLine_11.result()],
                           [SketchLine_13.result(), SketchLine_16.result(), SketchLine_15.result(), SketchLine_14.result()],
                           [SketchLine_19.result(), SketchLine_21.result(), SketchLine_18.result(), SketchLine_16.result()]
                          ])
model.do()

### Create Face
Face_1 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_3f-SketchLine_4f-SketchLine_2r-SketchLine_1r")])

### Create Face
Face_2 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_5f-SketchLine_6f-SketchArc_2_2r-SketchLine_4r")])

### Create Face
Face_3 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_7f-SketchLine_8f-SketchArc_1_2r-SketchLine_6r")])

### Create Face
Face_4 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_10f-SketchLine_11f-SketchLine_9r-SketchLine_8r")])

### Create Face
Face_5 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_13f-SketchLine_16f-SketchLine_15r-SketchLine_14r")])

### Create Face
Face_6 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_20f-SketchLine_22f-SketchLine_19r-SketchLine_16r")])

### Create Face
Face_7 = model.addFace(Part_2_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_17f-SketchLine_21f-SketchLine_20r-SketchLine_11r")])

### Create Shell
Shell_1_objects = [model.selection("FACE", "Face_1_1"),
                   model.selection("FACE", "Face_2_1"),
                   model.selection("FACE", "Face_3_1"),
                   model.selection("FACE", "Face_4_1"),
                   model.selection("FACE", "Face_7_1"),
                   model.selection("FACE", "Face_6_1"),
                   model.selection("FACE", "Face_5_1")]
Shell_1 = model.addShell(Part_2_doc, Shell_1_objects)

### Create Revolution
Revolution_1 = model.addRevolution(Part_2_doc, [model.selection("SHELL", "Shell_1_1")], model.selection("EDGE", "PartSet/OX"), 2.5, 2.5, "Faces")

### Create Group
Group_1_objects = [model.selection("EDGE", "[Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_2][Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_1]"),
                   model.selection("EDGE", "[Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_4][Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_2]"),
                   model.selection("EDGE", "[Revolution_1_1_2/Generated_Face&Sketch_1/SketchLine_6][Revolution_1_1_2/Generated_Face&Sketch_1/SketchArc_2_2]"),
                   model.selection("EDGE", "[Revolution_1_1_3/Generated_Face&Sketch_1/SketchLine_8][Revolution_1_1_3/Generated_Face&Sketch_1/SketchArc_1_2]"),
                   model.selection("EDGE", "[Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_11][Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_9]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_13][Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_14]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_15][Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_14]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_16][Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_15]"),
                   model.selection("EDGE", "[Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_22][Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_19]"),
                   model.selection("EDGE", "[Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_21][Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_20]")]
Group_1 = model.addGroup(Part_2_doc, "Edges", Group_1_objects)

### Create Group
Group_2_objects = [model.selection("FACE", "Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_1"),
                   model.selection("FACE", "Revolution_1_1_2/Generated_Face&Sketch_1/SketchLine_4"),
                   model.selection("FACE", "Revolution_1_1_3/Generated_Face&Sketch_1/SketchLine_6"),
                   model.selection("FACE", "Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_8"),
                   model.selection("FACE", "Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_11"),
                   model.selection("FACE", "Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_21")]
Group_2 = model.addGroup(Part_2_doc, "Faces", Group_2_objects)

### Create Group
Group_3_objects = [model.selection("EDGE", "[Revolution_1_1_1/From_Face][Revolution_1_1_1/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_2][Revolution_1_1_1/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_2][Revolution_1_1_1/From_Face]")]
Group_3 = model.addGroup(Part_2_doc, "Edges", Group_3_objects)

### Create Group
Group_4_objects = [model.selection("EDGE", "[Revolution_1_1_2/Generated_Face&Sketch_1/SketchArc_2_2][Revolution_1_1_2/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_2/Generated_Face&Sketch_1/SketchArc_2_2][Revolution_1_1_2/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_2/From_Face][Revolution_1_1_2/To_Face]")]
Group_4 = model.addGroup(Part_2_doc, "Edges", Group_4_objects)

### Create Group
Group_5_objects = [model.selection("EDGE", "[Revolution_1_1_3/Generated_Face&Sketch_1/SketchArc_1_2][Revolution_1_1_3/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_3/Generated_Face&Sketch_1/SketchArc_1_2][Revolution_1_1_3/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_3/From_Face][Revolution_1_1_3/To_Face]")]
Group_5 = model.addGroup(Part_2_doc, "Edges", Group_5_objects)

### Create Group
Group_6_objects = [model.selection("EDGE", "[Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_9][Revolution_1_1_4/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_9][Revolution_1_1_4/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_4/From_Face][Revolution_1_1_4/To_Face]")]
Group_6 = model.addGroup(Part_2_doc, "Edges", Group_6_objects)

### Create Group
Group_7_objects = [model.selection("EDGE", "[Revolution_1_1_5/From_Face][Revolution_1_1_5/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_20][Revolution_1_1_5/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_20][Revolution_1_1_5/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_19][Revolution_1_1_6/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_19][Revolution_1_1_6/From_Face]")]
Group_7 = model.addGroup(Part_2_doc, "Edges", Group_7_objects)

### Create Group
Group_8_objects = [model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_13][Revolution_1_1_7/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_13][Revolution_1_1_7/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_15][Revolution_1_1_7/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_15][Revolution_1_1_7/From_Face]")]
Group_8 = model.addGroup(Part_2_doc, "Edges", Group_8_objects)

### Create Group
Group_9_objects = [model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_14][Revolution_1_1_7/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_14][Revolution_1_1_7/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_16][Revolution_1_1_7/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_16][Revolution_1_1_7/To_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_22][Revolution_1_1_6/From_Face]"),
                   model.selection("EDGE", "[Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_22][Revolution_1_1_6/To_Face]")]
Group_9 = model.addGroup(Part_2_doc, "Edges", Group_9_objects)

### Create Group
Group_10_objects = [model.selection("FACE", "Revolution_1_1_1/To_Face"),
                    model.selection("FACE", "Revolution_1_1_2/To_Face"),
                    model.selection("FACE", "Revolution_1_1_3/To_Face"),
                    model.selection("FACE", "Revolution_1_1_4/To_Face"),
                    model.selection("FACE", "Revolution_1_1_5/To_Face"),
                    model.selection("FACE", "Revolution_1_1_6/To_Face"),
                    model.selection("FACE", "Revolution_1_1_7/To_Face")]
Group_10 = model.addGroup(Part_2_doc, "Faces", Group_10_objects)
Group_10.setName("front")
Group_10.result().setName("front")

### Create Group
Group_11_objects = [model.selection("FACE", "Revolution_1_1_1/From_Face"),
                    model.selection("FACE", "Revolution_1_1_2/From_Face"),
                    model.selection("FACE", "Revolution_1_1_3/From_Face"),
                    model.selection("FACE", "Revolution_1_1_4/From_Face"),
                    model.selection("FACE", "Revolution_1_1_5/From_Face"),
                    model.selection("FACE", "Revolution_1_1_6/From_Face"),
                    model.selection("FACE", "Revolution_1_1_7/From_Face")]
Group_11 = model.addGroup(Part_2_doc, "Faces", Group_11_objects)
Group_11.setName("back")
Group_11.result().setName("back")

### Create Group
Group_12_objects = [model.selection("FACE", "Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_2"),
                    model.selection("FACE", "Revolution_1_1_2/Generated_Face&Sketch_1/SketchArc_2_2"),
                    model.selection("FACE", "Revolution_1_1_3/Generated_Face&Sketch_1/SketchArc_1_2"),
                    model.selection("FACE", "Revolution_1_1_4/Generated_Face&Sketch_1/SketchLine_9"),
                    model.selection("FACE", "Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_13")]
Group_12 = model.addGroup(Part_2_doc, "Faces", Group_12_objects)
Group_12.setName("wall")
Group_12.result().setName("wall")

### Create Group
Group_13 = model.addGroup(Part_2_doc, "Faces", [model.selection("FACE", "Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_15"), model.selection("FACE", "Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_19")])
Group_13.setName("outletTop")
Group_13.result().setName("outletTop")

### Create Group
Group_14 = model.addGroup(Part_2_doc, "Faces", [model.selection("FACE", "Revolution_1_1_1/Generated_Face&Sketch_1/SketchLine_1")])
Group_14.setName("inlet")
Group_14.result().setName("inlet")

### Create Group
Group_15 = model.addGroup(Part_2_doc, "Faces", [model.selection("FACE", "Revolution_1_1_7/Generated_Face&Sketch_1/SketchLine_14")])
Group_15.setName("outletLeft")
Group_15.result().setName("outletLeft")

### Create Group
Group_16 = model.addGroup(Part_2_doc, "Faces", [model.selection("FACE", "Revolution_1_1_5/Generated_Face&Sketch_1/SketchLine_21"), model.selection("FACE", "Revolution_1_1_6/Generated_Face&Sketch_1/SketchLine_22")])
Group_16.setName("outletRight")
Group_16.result().setName("outletRight")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Revolution_1_1, Group_1_1, Group_2_1, Group_3_1, Group_4_1, Group_5_1, Group_6_1, Group_7_1, Group_8_1, Group_9_1, front, back, wall, outletTop, inlet, outletLeft, outletRight, = SHAPERSTUDY.shape(model.featureStringId(Revolution_1))

###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Revolution_1_1,'Mesh_1')
Regular_1D = Mesh_1.Segment()
Number_of_Segments_1 = Regular_1D.NumberOfSegments(NbSg1)
Prism_3D = Mesh_1.Prism()
front_1 = Mesh_1.GroupOnGeom(front,'front',SMESH.FACE)
back_1 = Mesh_1.GroupOnGeom(back,'back',SMESH.FACE)
wall_1 = Mesh_1.GroupOnGeom(wall,'wall',SMESH.FACE)
outletTop_1 = Mesh_1.GroupOnGeom(outletTop,'outletTop',SMESH.FACE)
inlet_1 = Mesh_1.GroupOnGeom(inlet,'inlet',SMESH.FACE)
outletLeft_1 = Mesh_1.GroupOnGeom(outletLeft,'outletLeft',SMESH.FACE)
outletRight_1 = Mesh_1.GroupOnGeom(outletRight,'outletRight',SMESH.FACE)
Regular_1D_1 = Mesh_1.Segment(geom=Group_1_1)
Sub_mesh_1 = Regular_1D_1.GetSubMesh()
Number_of_Segments_3 = Regular_1D_1.NumberOfSegments(NbSg2)
Regular_1D_2 = Mesh_1.Segment(geom=Group_2_1)
Sub_mesh_2 = Regular_1D_2.GetSubMesh()
Number_of_Segments_2 = Regular_1D_2.NumberOfSegments(NbSg2)
RadialQuadrangle_1D2D = Mesh_1.Quadrangle(algo=smeshBuilder.RADIAL_QUAD,geom=Group_2_1)
isDone = Mesh_1.SetMeshOrder( [ [ Sub_mesh_1, Sub_mesh_2 ] ])
[ front_1, back_1, wall_1, outletTop_1, inlet_1, outletLeft_1, outletRight_1 ] = Mesh_1.GetGroups()
Regular_1D_3 = Mesh_1.Segment(geom=Group_3_1)
Number_of_Segments_4 = Regular_1D_3.NumberOfSegments(NbSg3,None,[])
Number_of_Segments_4.SetConversionMode( 0 )
Number_of_Segments_4.SetExpressionFunction( '0.5*t' )
[ front_1, back_1, wall_1, outletTop_1, inlet_1, outletLeft_1, outletRight_1 ] = Mesh_1.GetGroups()
Regular_1D_4 = Mesh_1.Segment(geom=Group_4_1)
Number_of_Segments_5 = Regular_1D_4.NumberOfSegments(NbSg4)
Regular_1D_5 = Mesh_1.Segment(geom=Group_5_1)
Number_of_Segments_6 = Regular_1D_5.NumberOfSegments(NbSg5)
Regular_1D_6 = Mesh_1.Segment(geom=Group_6_1)
Number_of_Segments_7 = Regular_1D_6.NumberOfSegments(NbSg6)
[ front_1, back_1, wall_1, outletTop_1, inlet_1, outletLeft_1, outletRight_1 ] = Mesh_1.GetGroups()
Regular_1D_7 = Mesh_1.Segment(geom=Group_7_1)
Number_of_Segments_8 = Regular_1D_7.NumberOfSegments(NbSg7)
Regular_1D_8 = Mesh_1.Segment(geom=Group_8_1)
Number_of_Segments_9 = Regular_1D_8.NumberOfSegments(NbSg8)
[ front_1, back_1, wall_1, outletTop_1, inlet_1, outletLeft_1, outletRight_1 ] = Mesh_1.GetGroups()
Regular_1D_9 = Mesh_1.Segment(geom=Group_9_1)
Number_of_Segments_10 = Regular_1D_9.NumberOfSegments(NbSg9,None,[])
Number_of_Segments_10.SetConversionMode( 0 )
Number_of_Segments_10.SetExpressionFunction( '-t*t' )
isDone = Mesh_1.Compute()
Mesh_1.CheckCompute()
[ front_1, back_1, wall_1, outletTop_1, inlet_1, outletLeft_1, outletRight_1 ] = Mesh_1.GetGroups()
try:
  Mesh_1.ExportUNV( r'/home/chrt/OpenFOAM/chrt-v2406/run/geometry/Mesh.unv', 0 )
  pass
except:
  print('ExportUNV() failed. Invalid file name?')
Sub_mesh_3 = Regular_1D_3.GetSubMesh()
Sub_mesh_4 = Regular_1D_4.GetSubMesh()
Sub_mesh_5 = Regular_1D_5.GetSubMesh()
Sub_mesh_6 = Regular_1D_6.GetSubMesh()
Sub_mesh_7 = Regular_1D_7.GetSubMesh()
Sub_mesh_8 = Regular_1D_8.GetSubMesh()
Sub_mesh_9 = Regular_1D_9.GetSubMesh()

## some objects were removed
aStudyBuilder = salome.myStudy.NewBuilder()

## Set names of Mesh objects
smesh.SetName(Regular_1D.GetAlgorithm(), 'Regular_1D')
smesh.SetName(Sub_mesh_1, 'Sub-mesh_1')
smesh.SetName(Number_of_Segments_10, 'Number of Segments_10')
smesh.SetName(outletTop_1, 'outletTop')
smesh.SetName(Sub_mesh_8, 'Sub-mesh_8')
smesh.SetName(inlet_1, 'inlet')
smesh.SetName(Sub_mesh_2, 'Sub-mesh_2')
smesh.SetName(Sub_mesh_3, 'Sub-mesh_3')
smesh.SetName(Prism_3D.GetAlgorithm(), 'Prism_3D')
smesh.SetName(outletRight_1, 'outletRight')
smesh.SetName(Number_of_Segments_2, 'Number of Segments_2')
smesh.SetName(Number_of_Segments_7, 'Number of Segments_7')
smesh.SetName(front_1, 'front')
smesh.SetName(Number_of_Segments_5, 'Number of Segments_5')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(Sub_mesh_9, 'Sub-mesh_9')
smesh.SetName(Sub_mesh_5, 'Sub-mesh_5')
smesh.SetName(wall_1, 'wall')
smesh.SetName(Sub_mesh_7, 'Sub-mesh_7')
smesh.SetName(Number_of_Segments_9, 'Number of Segments_9')
smesh.SetName(Number_of_Segments_8, 'Number of Segments_8')
smesh.SetName(Number_of_Segments_3, 'Number of Segments_3')
smesh.SetName(Sub_mesh_6, 'Sub-mesh_6')
smesh.SetName(back_1, 'back')
smesh.SetName(Number_of_Segments_6, 'Number of Segments_6')
smesh.SetName(outletLeft_1, 'outletLeft')
smesh.SetName(Number_of_Segments_1, 'Number of Segments_1')
smesh.SetName(Number_of_Segments_4, 'Number of Segments_4')
smesh.SetName(RadialQuadrangle_1D2D.GetAlgorithm(), 'RadialQuadrangle_1D2D')
smesh.SetName(Sub_mesh_4, 'Sub-mesh_4')

#change params for setfields
file = open("/home/chrt/OpenFOAM/chrt-v2406/run/nozzle_1/params.txt", "a")
file.write(f"width\n{l_left/1000}\n\nheight\n{d_inlet_/2000}")
file.close()

if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
  
