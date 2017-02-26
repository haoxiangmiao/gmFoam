Point(1) = {-1, -1, 0, 1.0};

Extrude {1, 0, 0} {
  Point{1};  Layers{1};
}

Extrude {1, 0, 0} {
  Point{2}; Layers{1};
}
Extrude {0, 1, 0} {
  Line{1, 2}; Layers{1}; Recombine;
}
Extrude {0, 1, 0} {
  Line{3, 7}; Layers{1};  Recombine;
}



layer_thickness[]={1,1,1,1};  //outside layer thickness in x & y direction; x direction thickness equals to y direction thickness assumed

Z_layer_thickness[]={1,1,1,1}; // outside layer thickness in z direction  

surface_index=0;  //index of surface id array
volume_index=0;  // index of volume id array
start_line_id=1;  //start_line_id: the begining line(direction from neg_x to pos_x) of the neg_y side

neg_z_length[]={1,1}; //neg_z_length per part
neg_z_layer[]={1,1};      //neg_z_layer per part

neg_y_length[]={1,1};        //neg_y_length per part
pos_y_length[]={1,1};        //pos_y_length per part
neg_x_length[]={1,1};        //neg_X_length per part
pos_x_length[]={1,1};        //pos_x_length per part

neg_y_layer[]={1,1};            //neg_y_layer per part
neg_x_layer[]={1,1};            //neg_x_layer per part
pos_y_layer[]={1,1};            //pos_y_layer per part
pos_x_layer[]={1,1};            //pos_x_layer per part



volume_index=0;




inner_part[]={6,10,14,18};
//Physical Surface("inner surface",#layer_thickness[]+10) =inner_part[];

ini_surface_inner[]=inner_part[];
For i11 In {0:#neg_z_length[]-1}
  temp_volume[]=Extrude {0, 0, -neg_z_length[i11]} { Surface{ini_surface_inner[]}; Layers{neg_z_layer[i11]}; Recombine; };
  For i12 In {0:#ini_surface_inner[]-1}
  ini_surface_inner[i12]=temp_volume[0+i12*6];
  volume_id[volume_index]=temp_volume[1+i12*6];
  volume_index=volume_index+1;
  EndFor
EndFor

//Physical Volume("inner part",#layer_thickness[]+1)=volume_id[];
volume_index=0;




For i In {0:#layer_thickness[]-1}    
//#layer_thickness[]-1
  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i]} { Surface{ini_surface_inner[]}; Layers{1}; Recombine; };
  For i16 In {0:#ini_surface_inner[]-1}
  ini_surface_inner[i16]=temp_volume[0+i16*6];
  volume_id[volume_index]=temp_volume[1+i16*6];
  volume_index=volume_index+1;
  EndFor

//#layer_thickness[]-1

temp1[]=Extrude {0, -layer_thickness[i], 0} { Line{start_line_id}; Layers{1}; Recombine;};
surface_id[surface_index]=temp1[1];
surface_index=surface_index+1;


ini_line_id=temp1[2];
For i1 In {0:#neg_y_length[]-2}
    temp2[]=Extrude {neg_y_length[i1+1],0,0} {  Line{ini_line_id}; Layers{ neg_y_layer[i1+1]}; Recombine;};
    surface_id[surface_index]=temp2[1];
    surface_index=surface_index+1;
    ini_line_id=temp2[0];
EndFor

temp3[]=Extrude {layer_thickness[i], 0, 0} { Line{temp2[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp3[1];
surface_index=surface_index+1;
ini_line_id=temp3[3];


For i2 In {0:#pos_x_length[]-1}
  temp4[]=Extrude {0,pos_x_length[i2],0} {  Line{ini_line_id}; Layers{ pos_x_layer[i2]}; Recombine;};
  surface_id[surface_index]=temp4[1];
  surface_index=surface_index+1;
  ini_line_id=temp4[0];
EndFor

temp5[]=Extrude {0, layer_thickness[i], 0} { Line{temp4[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp5[1];
surface_index=surface_index+1;
ini_line_id=temp5[2];

For i3 In {0:#pos_y_length[]-1}
  temp6[]=Extrude {-pos_y_length[i3], 0, 0} {  Line{ini_line_id}; Layers{ pos_y_layer[i3]}; Recombine;};
  surface_id[surface_index]=temp6[1];
  surface_index=surface_index+1;
  ini_line_id=temp6[0];
EndFor

temp7[]=Extrude {-layer_thickness[i], 0, 0} { Line{temp6[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp7[1];
surface_index=surface_index+1;
ini_line_id=temp7[3];

//Printf("New surfaces %g and %g", ini_line_id, temp7[3]);

For i4 In {0:#neg_x_length[]-1}
  temp8[]=Extrude {0, -neg_x_length[i4], 0} {  Line{ini_line_id}; Layers{ neg_x_layer[i4]}; Recombine;};
  surface_id[surface_index]=temp8[1];
  surface_index=surface_index+1;
  ini_line_id=temp8[0];
EndFor

temp9[]=Extrude {0,-layer_thickness[i], 0} { Line{temp8[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp9[1];
surface_index=surface_index+1;

start_line_id=temp9[0];
//Printf("New surfaces %g and %g", start_line_id, temp9[0]);
If (i==0)
	//Physical Surface("surface of DMR layer",i+10) = surface_id[];
EndIf
If (i==1 )
	//Physical Surface("surface of outside layer_1",i+10) = surface_id[];
EndIf
If (i==2 )
	//Physical Surface("surface of outside layer_2",i+10) = surface_id[];
EndIf
If (i==3 )
	//Physical Surface("surface of outside layer_3",i+10) = surface_id[];
EndIf


surface_index=0;

ini_surface[]=surface_id[];
For i10 In {0:#neg_z_length[]-1}
  temp_volume[]=Extrude {0, 0, -neg_z_length[i10]} { Surface{ini_surface[]}; Layers{neg_z_layer[i10]}; Recombine; };
  For i9 In {0:#ini_surface[]-1}
  ini_surface[i9]=temp_volume[0+i9*6];
  volume_id[volume_index]=temp_volume[1+i9*6];
  volume_index=volume_index+1;
  EndFor
EndFor

For i13 In {0:i}
  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i13]} { Surface{ini_surface[]}; Layers{1}; Recombine; };
  For i14 In {0:#ini_surface[]-1}
  ini_surface[i14]=temp_volume[0+i14*6];
  volume_id[volume_index]=temp_volume[1+i14*6];
  volume_index=volume_index+1;
  EndFor
EndFor

If (i==0)
	//Physical Volume("DRM layer",i+1)=volume_id[];
EndIf
If (i==1 )
	//Physical Volume("outside layer_1",i+1)=volume_id[];
EndIf
If (i==2 )
	//Physical Volume("outside layer_2",i+1)=volume_id[];
EndIf
If (i==3 )
	//Physical Volume("outside layer_3",i+1)=volume_id[];
EndIf


volume_index=0;


  temp_size=#ini_surface_inner[];
  For i17 In {0:#ini_surface[]-1}
  ini_surface_inner[i17+temp_size]=ini_surface[i17];
  EndFor


//Printf("New surfaces %g %g %g %g %g %g %g %g %g %g %g", temp_volume[0], temp_volume[1],  temp_volume[2], temp_volume[3], temp_volume[4], temp_volume[5],temp_volume[6],temp_volume[7],temp_volume[8], temp_volume[9], temp_volume[10]);

temp_neg_y_length[0]=layer_thickness[i];
temp_pos_y_length[0]=layer_thickness[i];
temp_neg_x_length[0]=layer_thickness[i];
temp_pos_x_length[0]=layer_thickness[i];

temp_neg_y_layer[0]=1;
temp_pos_y_layer[0]=1;
temp_neg_x_layer[0]=1;
temp_pos_x_layer[0]=1;

For i5 In {0:#neg_y_length[]-1}
temp_neg_y_length[i5+1]=neg_y_length[i5];
temp_neg_y_layer[i5+1]=neg_y_layer[i5];
EndFor

For i6 In {0:#pos_y_length[]-1}
temp_pos_y_length[i6+1]=pos_y_length[i6];
temp_pos_y_layer[i6+1]=pos_y_layer[i6];
EndFor

For i7 In {0:#neg_x_length[]-1}
temp_neg_x_length[i7+1]=neg_x_length[i7];
temp_neg_x_layer[i7+1]=neg_x_layer[i7];
EndFor

For i8 In {0:#pos_x_length[]-1}
temp_pos_x_length[i8+1]=pos_x_length[i8];
temp_pos_x_layer[i8+1]=pos_x_layer[i8];
EndFor

temp_neg_y_length[#neg_y_length[]+1]=layer_thickness[i];
temp_pos_y_length[#neg_y_length[]+1]=layer_thickness[i];
temp_neg_x_length[#neg_y_length[]+1]=layer_thickness[i];
temp_pos_x_length[#neg_y_length[]+1]=layer_thickness[i];

temp_neg_y_layer[#neg_y_length[]+1]=1;
temp_pos_y_layer[#neg_y_length[]+1]=1;
temp_neg_x_layer[#neg_y_length[]+1]=1;
temp_pos_x_layer[#neg_y_length[]+1]=1;


neg_y_length[]=temp_neg_y_length[];
neg_x_length[]=temp_neg_x_length[];
pos_y_length[]=temp_pos_y_length[];
pos_x_length[]=temp_pos_x_length[];

neg_y_layer[]=temp_neg_y_layer[];
pos_y_layer[]=temp_pos_y_layer[];
neg_x_layer[]=temp_neg_x_layer[];
pos_x_layer[]=temp_pos_x_layer[];


EndFor

//Printf("New surfaces %g and %g", layer_thickness[0], layer_thickness[1]);

//volume_index=0;

//inner_part[]={89, 93, 97, 101, 105, 85, 81, 77, 69, 49, 53, 73, 57, 61, 65, 45, 41, 37, 29, 33, 13, 9, 17, 25, 21};
//Physical Surface(#layer_thickness[]) =inner_part[] ;

//ini_surface[]=inner_part[];
//For i11 In {0:#neg_z_length[]-1}
//  temp_volume[]=Extrude {0, 0, -neg_z_length[i11]} { Surface{ini_surface[]}; Layers{neg_z_layer[i11]}; Recombine; };
//  For i12 In {0:#ini_surface[]-1}
//  ini_surface[i12]=temp_volume[0+i12*6];
//  volume_id[volume_index]=temp_volume[1+i12*6];
//  volume_index=volume_index+1;
//  EndFor
//EndFor

//Physical Volume(#layer_thickness[])=volume_id[];
//volume_index=0;

//For i15 In {0:#layer_thickness[]-1}
//  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i15]} { Surface{ini_surface[]}; Layers{1}; Recombine; };
//  For i16 In {0:#ini_surface[]-1}
//  ini_surface[i16]=temp_volume[0+i16*6];
//  volume_id[volume_index]=temp_volume[1+i16*6];
//  volume_index=volume_index+1;
//  EndFor
// Physical Volume(#layer_thickness[]+i15+1)=volume_id[];
// volume_index=0;
//EndFor


//Physical Surface("bottom surface",15) = {40875, 40941, 40897, 40853, 40831, 40809, 40787, 41029, 41051, 41007, 40985, 40963, 40919, 29265, 41073, 29177, 29199, 29221, 29243, 29111, 29287, 29309, 29133, 29331, 40765, 29155, 41095, 40743, 28385, 29089, 28539, 28517, 28495, 28473, 28451, 28429, 28407, 28363, 29353, 28341, 27857, 27835, 29375, 27813, 27791, 28561, 27901, 29067, 27879, 40721, 41117, 27923, 29045, 27219, 27241, 40699, 27439, 27461, 27659, 27769, 27945, 28319, 28583, 41139, 29397, 40677, 27483, 27417, 27637, 27747, 27967, 27263, 28297, 28605, 41161, 27197, 29419, 29023, 40655, 27395, 27175, 27285, 27505, 27615, 27725, 27989, 28275, 28627, 41183, 29001, 29441, 28649, 27153, 27351, 27373, 27549, 27571, 27703, 28011, 28253, 28979, 29463, 40633, 41205, 40611, 29485, 41227, 28957, 28671, 28231, 27131, 28033, 27681, 27593, 27527, 27329, 27307, 28099, 40589, 41249, 28055, 28077, 28121, 28143, 28165, 28187, 28209, 28693, 29507, 28935, 28913, 28891, 28869, 28847, 28825, 41271, 28803, 28781, 28759, 28737, 29529, 28715, 40567, 40545, 41293, 29705, 29771, 29749, 29727, 29683, 29661, 29639, 29617, 29573, 29595, 29551, 41359, 41403, 41337, 41315, 41513, 41425, 41447, 41535, 41491, 41469, 41381, 41557, 41579};

//Physical Surface("bottom surface",15) = {13206, 13228, 13250, 13272, 13294, 13316, 13338, 13360, 13382, 13404, 8486, 13184, 8552, 8530, 8508, 13426, 8398, 8420, 8442, 8464, 13162, 8574, 8376, 7914, 7980, 7958, 7936, 7892, 7870, 13448, 7518, 7540, 7562, 8596, 8354, 13470, 13140, 7584, 8002, 7848, 13492, 7386, 8332, 7364, 8618, 7496, 13118, 7606, 7826, 8024, 7342, 8640, 13096, 13514, 8046, 7804, 8310, 7320, 7628, 7474, 7650, 8068, 7782, 13074, 7452, 7408, 8288, 13536, 8662, 7430, 7672, 7694, 7716, 7738, 7760, 13052, 8684, 13558, 8090, 8266, 8134, 13580, 8156, 13030, 8112, 8244, 8222, 8200, 8178, 8706, 13602, 12832, 12854, 12876, 12898, 12920, 12942, 12964, 12986, 13008};
Physical Surface("top_surface",1) = {8778, 8782, 8786, 8790, 8794, 8798, 8802, 8806, 8810, 8814, 4178, 8774, 4190, 4186, 4182, 8818, 4162, 4166, 4170, 4174, 8770, 4194, 4158, 1522, 1534, 1530, 1526, 1518, 1514, 8822, 306, 310, 314, 4198, 4154, 8826, 8766, 318, 1538, 1510, 8830, 18, 4150, 14, 4202, 302, 8762, 322, 1506, 1542, 10, 4206, 8758, 8834, 1546, 1502, 4146, 6, 326, 298, 330, 1550, 1498, 8754, 294, 286, 4142, 8838, 4210, 290, 1478, 1482, 1486, 1490, 1494, 8750, 4214, 8842, 1554, 4138, 4114, 8846, 4118, 8746, 4110, 4134, 4130, 4126, 4122, 4218, 8850, 8710, 8714, 8718, 8722, 8726, 8730, 8734, 8738, 8742};
Physical Surface("bottom_surface",2) = {13008, 13206, 13030, 13052, 13074, 13096, 13184, 13162, 13140, 13118, 8266, 12986, 8398, 8376, 8354, 8332, 8310, 8288, 13228, 8244, 8222, 8420, 12964, 7804, 7870, 7848, 7826, 13250, 7782, 7760, 7892, 13272, 8200, 7452, 7474, 7496, 7518, 7738, 8442, 12942, 8464, 12920, 7342, 13294, 8178, 7386, 7430, 7540, 7716, 7914, 8156, 13316, 7320, 7364, 7408, 7562, 7694, 7936, 12898, 8486, 13338, 8134, 7584, 12876, 7606, 7628, 7958, 7650, 7672, 8508, 8068, 8024, 8002, 8530, 8046, 7980, 8090, 12854, 8112, 13360, 8640, 13382, 8574, 8596, 12832, 8706, 8684, 8662, 8618, 8552, 13602, 13580, 13558, 13536, 13514, 13492, 13470, 13448, 13426, 13404};
Physical Surface("lateral_surface_1",3) = {9641, 9619, 9597, 9575, 9553, 9531, 9509, 9487, 9465, 9439, 10433, 10411, 10389, 10367, 10345, 10323, 10301, 10279, 10257, 10231, 11225, 11203, 11181, 11159, 11137, 11115, 11093, 11071, 11049, 11023, 12017, 11995, 11973, 11951, 11929, 11907, 11885, 11863, 11841, 11815, 12809, 12787, 12765, 12743, 12721, 12699, 12677, 12655, 12633, 12607, 13601, 13579, 13557, 13535, 13513, 13491, 13469, 13447, 13425, 13399};
Physical Surface("lateral_surface_2",4) = {9241, 9259, 9281, 9303, 9325, 9347, 9369, 10033, 9391, 10051, 9413, 10073, 9435, 10095, 10117, 10139, 10161, 10825, 10183, 10843, 10205, 10865, 10227, 10887, 10909, 10931, 10953, 11617, 10975, 11635, 10997, 11657, 11019, 11679, 11701, 11723, 11745, 12409, 11767, 12427, 11789, 12449, 11811, 12471, 12493, 12515, 12537, 13201, 12559, 13219, 12581, 13241, 12603, 13263, 13285, 13307, 13329, 13351, 13373, 13395};
Physical Surface("lateral_surfac_3",5) = {9245, 9223, 9201, 9179, 9157, 9135, 9113, 9091, 9069, 9043, 10037, 10015, 9993, 9971, 9949, 9927, 9905, 9883, 9861, 9835, 10829, 10807, 10785, 10763, 10741, 10719, 10697, 10675, 10653, 10627, 11621, 11599, 11577, 11555, 11533, 11511, 11489, 11467, 11445, 11419, 12413, 12391, 12369, 12347, 12325, 12303, 12281, 12259, 12237, 12211, 13205, 13183, 13161, 13139, 13117, 13095, 13073, 13051, 13029, 13003};
Physical Surface("lateral_urface_4",6) = {8885, 8907, 8929, 8951, 8973, 8995, 9017, 9039, 9637, 8867, 9809, 10429, 9831, 9787, 9765, 9721, 9659, 9699, 9677, 9743, 10557, 11221, 10623, 10601, 10579, 10535, 10513, 10491, 10469, 10451, 11243, 12013, 11415, 11393, 11371, 11327, 11305, 11283, 11261, 11349, 12185, 12805, 12207, 12163, 12141, 12119, 12097, 12075, 12053, 12035, 12827, 12845, 12867, 12889, 12911, 12933, 12955, 12977, 12999, 13597};
Physical Volume("volume",7) = {586, 589, 584, 588, 405, 590, 587, 519, 518, 411, 583, 510, 517, 516, 515, 514, 513, 512, 511, 585, 443, 481, 480, 479, 478, 477, 476, 475, 474, 441, 442, 482, 444, 445, 408, 446, 555, 409, 403, 402, 410, 551, 591, 406, 582, 546, 547, 548, 483, 549, 550, 552, 553, 554, 447, 404, 407, 438, 439, 440, 255, 257, 256, 252, 254, 200, 253, 448, 284, 545, 306, 307, 308, 309, 310, 311, 312, 313, 581, 285, 201, 283, 473, 282, 281, 280, 279, 278, 437, 229, 484, 194, 227, 226, 197, 225, 224, 223, 196, 222, 370, 371, 195, 251, 520, 377, 592, 556, 376, 401, 375, 374, 373, 372, 228, 198, 199, 509, 250, 412, 369, 136, 249, 347, 135, 305, 202, 134, 95, 115, 116, 117, 118, 119, 114, 314, 99, 98, 97, 96, 378, 94, 286, 508, 258, 277, 593, 521, 139, 138, 137, 580, 193, 175, 174, 221, 172, 230, 171, 170, 173, 74, 75, 472, 544, 413, 76, 78, 77, 557, 351, 348, 350, 349, 400, 346, 79, 436, 449, 485, 33, 60, 32, 203, 31, 486, 579, 44, 248, 30, 45, 73, 352, 558, 61, 414, 21, 368, 304, 435, 220, 20, 450, 58, 59, 543, 113, 140, 331, 176, 43, 93, 100, 332, 192, 157, 333, 19, 594, 156, 315, 507, 80, 399, 345, 155, 154, 231, 18, 169, 287, 276, 522, 471, 120, 133, 330, 379, 259, 42, 51, 168, 398, 260, 232, 81, 41, 62, 367, 191, 177, 344, 334, 52, 158, 34, 57, 434, 247, 353, 219, 542, 141, 506, 316, 288, 470, 324, 153, 415, 7, 8, 148, 147, 101, 132, 275, 323, 121, 578, 17, 11, 12, 204, 487, 559, 329, 92, 29, 72, 46, 451, 112, 523, 303, 22, 3, 4, 380, 595, 328, 47, 335, 343, 1, 2, 49, 233, 6, 397, 261, 50, 596, 354, 218, 433, 366, 63, 71, 56, 246, 111, 5, 381, 321, 416, 82, 322, 91, 102, 302, 317, 274, 122, 131, 142, 145, 146, 152, 488, 289, 505, 577, 23, 560, 524, 28, 35, 40, 190, 178, 167, 159, 541, 469, 16, 452, 205, 10, 9, 64, 70, 432, 143, 53, 318, 453, 179, 576, 54, 13, 206, 83, 396, 90, 525, 149, 234, 382, 504, 166, 150, 151, 273, 342, 290, 48, 160, 417, 489, 540, 14, 103, 27, 15, 245, 327, 39, 326, 325, 38, 301, 37, 36, 110, 123, 365, 189, 468, 130, 26, 355, 55, 336, 262, 217, 597, 561, 24, 25, 339, 341, 340, 319, 164, 300, 163, 235, 539, 162, 575, 161, 180, 244, 263, 454, 562, 338, 467, 337, 503, 127, 126, 125, 383, 124, 291, 395, 272, 66, 128, 490, 67, 418, 216, 65, 431, 69, 68, 207, 104, 84, 85, 86, 87, 88, 89, 144, 356, 526, 598, 129, 105, 106, 107, 165, 108, 109, 364, 188, 242, 466, 269, 293, 292, 271, 241, 264, 265, 266, 267, 268, 270, 243, 294, 295, 296, 182, 212, 211, 210, 209, 208, 187, 599, 186, 185, 184, 183, 298, 181, 574, 563, 538, 527, 502, 491, 419, 430, 455, 358, 320, 240, 239, 238, 237, 236, 299, 297, 213, 357, 359, 360, 361, 362, 363, 384, 394, 215, 214, 493, 499, 494, 495, 496, 497, 498, 532, 492, 535, 600, 536, 537, 388, 389, 500, 462, 461, 460, 459, 464, 465, 458, 501, 457, 456, 534, 385, 386, 387, 528, 529, 530, 531, 463, 533, 391, 420, 421, 422, 423, 424, 425, 426, 573, 572, 571, 570, 569, 568, 567, 566, 564, 427, 565, 428, 429, 392, 393, 390};
