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
Physical Surface("inner surface",#layer_thickness[]+10) =inner_part[];

ini_surface_inner[]=inner_part[];
For i11 In {0:#neg_z_length[]-1}
  temp_volume[]=Extrude {0, 0, -neg_z_length[i11]} { Surface{ini_surface_inner[]}; Layers{neg_z_layer[i11]}; Recombine; };
  For i12 In {0:#ini_surface_inner[]-1}
  ini_surface_inner[i12]=temp_volume[0+i12*6];
  volume_id[volume_index]=temp_volume[1+i12*6];
  volume_index=volume_index+1;
  EndFor
EndFor

Physical Volume("inner part",#layer_thickness[]+1)=volume_id[];
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
	Physical Surface("surface of DMR layer",i+10) = surface_id[];
EndIf
If (i==1 )
	Physical Surface("surface of outside layer_1",i+10) = surface_id[];
EndIf
If (i==2 )
	Physical Surface("surface of outside layer_2",i+10) = surface_id[];
EndIf
If (i==3 )
	Physical Surface("surface of outside layer_3",i+10) = surface_id[];
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
	Physical Volume("DRM layer",i+1)=volume_id[];
EndIf
If (i==1 )
	Physical Volume("outside layer_1",i+1)=volume_id[];
EndIf
If (i==2 )
	Physical Volume("outside layer_2",i+1)=volume_id[];
EndIf
If (i==3 )
	Physical Volume("outside layer_3",i+1)=volume_id[];
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

Physical Surface("bottom surface",15) = {13206, 13228, 13250, 13272, 13294, 13316, 13338, 13360, 13382, 13404, 8486, 13184, 8552, 8530, 8508, 13426, 8398, 8420, 8442, 8464, 13162, 8574, 8376, 7914, 7980, 7958, 7936, 7892, 7870, 13448, 7518, 7540, 7562, 8596, 8354, 13470, 13140, 7584, 8002, 7848, 13492, 7386, 8332, 7364, 8618, 7496, 13118, 7606, 7826, 8024, 7342, 8640, 13096, 13514, 8046, 7804, 8310, 7320, 7628, 7474, 7650, 8068, 7782, 13074, 7452, 7408, 8288, 13536, 8662, 7430, 7672, 7694, 7716, 7738, 7760, 13052, 8684, 13558, 8090, 8266, 8134, 13580, 8156, 13030, 8112, 8244, 8222, 8200, 8178, 8706, 13602, 12832, 12854, 12876, 12898, 12920, 12942, 12964, 12986, 13008};
