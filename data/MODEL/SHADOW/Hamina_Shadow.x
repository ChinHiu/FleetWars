xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 74;
 37.95647;-115.87065;217.19870;,
 -38.21749;-115.87065;217.23698;,
 -39.10059;-115.87065;175.19577;,
 38.80622;-115.87076;175.15706;,
 -39.51346;-115.87065;135.74916;,
 39.19201;-115.87076;135.70963;,
 -38.97124;-115.87065;110.12905;,
 38.62951;-115.87065;110.09005;,
 -38.90896;-115.87065;84.19897;,
 38.56063;-115.87065;84.16004;,
 -38.64166;-115.87076;48.22874;,
 38.26488;-115.87065;48.19011;,
 -38.20441;-115.87076;-10.95180;,
 37.78089;-115.87076;-10.98995;,
 -37.99027;-115.87065;-40.10511;,
 37.54366;-115.87065;-40.14304;,
 -37.45382;-115.87076;-78.23468;,
 36.97685;-115.87065;-78.27203;,
 -36.71380;-115.87065;-104.75160;,
 36.21980;-115.87076;-104.78825;,
 -35.43359;-115.87076;-120.05440;,
 34.92735;-115.87065;-120.08976;,
 -30.88480;-115.87065;-139.29979;,
 30.36341;-115.87076;-139.33057;,
 -28.23709;-115.87065;-155.84823;,
 27.70704;-115.87076;-155.87626;,
 -22.69163;-115.87076;-176.29674;,
 22.14492;-115.87076;-176.31902;,
 -17.50034;-115.87076;-191.83179;,
 16.94121;-115.87065;-191.84892;,
 -9.09852;-115.87076;-211.16560;,
 8.52407;-115.87065;-211.17429;,
 -8.85763;-115.87065;-211.69037;,
 8.28273;-115.87065;-211.69884;,
 -3.91175;-115.87076;-216.11907;,
 3.33314;-115.87065;-216.12267;,
 -0.28994;-115.87065;-217.23592;,
 38.98176;115.87129;175.15706;,
 -38.92509;115.87140;175.19577;,
 -38.04192;115.87140;217.23698;,
 38.13198;115.87140;217.19870;,
 39.36754;115.87129;135.70963;,
 -39.33792;115.87140;135.74916;,
 38.80508;115.87140;110.09005;,
 -38.79569;115.87140;110.12905;,
 38.73614;115.87140;84.16004;,
 -38.73344;115.87140;84.19897;,
 38.44041;115.87140;48.19011;,
 -38.46613;115.87129;48.22874;,
 37.95639;115.87129;-10.98995;,
 -38.02887;115.87129;-10.95180;,
 37.71915;115.87140;-40.14304;,
 -37.81474;115.87140;-40.10511;,
 37.15239;115.87140;-78.27203;,
 -37.27830;115.87129;-78.23468;,
 36.39529;115.87129;-104.78825;,
 -36.53827;115.87140;-104.75160;,
 35.10286;115.87140;-120.08976;,
 -35.25806;115.87129;-120.05440;,
 30.53893;115.87129;-139.33057;,
 -30.70927;115.87140;-139.29979;,
 27.88255;115.87129;-155.87626;,
 -28.06156;115.87140;-155.84823;,
 22.32045;115.87129;-176.31902;,
 -22.51612;115.87129;-176.29674;,
 17.11673;115.87140;-191.84892;,
 -17.32482;115.87129;-191.83179;,
 8.69959;115.87140;-211.17429;,
 -8.92299;115.87129;-211.16560;,
 8.45824;115.87140;-211.69884;,
 -8.68212;115.87140;-211.69037;,
 3.50867;115.87140;-216.12267;,
 -3.73623;115.87129;-216.11907;,
 -0.11442;115.87140;-217.23592;;
 
 73;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 3;34,36,35;,
 4;37,38,39,40;,
 4;41,42,38,37;,
 4;43,44,42,41;,
 4;43,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;65,67,68,66;,
 4;67,69,70,68;,
 4;69,71,72,70;,
 3;71,73,72;,
 4;39,38,2,1;,
 4;40,39,1,0;,
 4;37,40,0,3;,
 4;38,42,4,2;,
 4;41,37,3,5;,
 4;42,44,6,4;,
 4;43,41,5,7;,
 4;45,43,7,9;,
 4;44,46,8,6;,
 4;47,45,9,11;,
 4;46,48,10,8;,
 4;49,47,11,13;,
 4;48,50,12,10;,
 4;51,49,13,15;,
 4;50,52,14,12;,
 4;53,51,15,17;,
 4;52,54,16,14;,
 4;55,53,17,19;,
 4;54,56,18,16;,
 4;57,55,19,21;,
 4;56,58,20,18;,
 4;59,57,21,23;,
 4;58,60,22,20;,
 4;61,59,23,25;,
 4;60,62,24,22;,
 4;63,61,25,27;,
 4;62,64,26,24;,
 4;65,63,27,29;,
 4;64,66,28,26;,
 4;67,65,29,31;,
 4;66,68,30,28;,
 4;69,67,31,33;,
 4;68,70,32,30;,
 4;71,69,33,35;,
 4;70,72,34,32;,
 4;73,71,35,36;,
 4;72,73,36,34;;
 
 MeshMaterialList {
  2;
  73;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.341056;0.341056;0.341056;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\bizch\\Desktop\\Hamina.tga";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  76;
  0.000016;-1.000000;-0.000053;,
  0.000012;-1.000000;-0.000015;,
  0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000001;,
  0.000003;-1.000000;-0.000002;,
  -0.000001;-1.000000;-0.000001;,
  -0.000001;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000002;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000001;,
  0.000001;-1.000000;0.000001;,
  0.000000;-1.000000;0.000001;,
  -0.000000;-1.000000;-0.000001;,
  0.000006;-1.000000;-0.000044;,
  0.000004;-1.000000;-0.000055;,
  0.000000;-1.000000;-0.000002;,
  -0.000001;-1.000000;0.000001;,
  -0.000016;1.000000;0.000053;,
  -0.000012;1.000000;0.000015;,
  -0.000000;1.000000;-0.000001;,
  -0.000000;1.000000;0.000000;,
  -0.000003;1.000000;0.000001;,
  0.000001;1.000000;0.000001;,
  0.000001;1.000000;-0.000001;,
  -0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000001;1.000000;-0.000000;,
  0.000002;1.000000;-0.000002;,
  -0.000000;1.000000;0.000001;,
  -0.000001;1.000000;-0.000001;,
  -0.000000;1.000000;-0.000001;,
  0.000000;1.000000;0.000001;,
  -0.000006;1.000000;0.000045;,
  -0.000004;1.000000;0.000056;,
  -0.000000;1.000000;0.000002;,
  0.000001;1.000000;-0.000001;,
  -0.999779;0.000757;0.021002;,
  -0.999876;0.000757;0.015734;,
  0.000503;-0.000000;1.000000;,
  0.999887;-0.000757;0.014994;,
  0.999795;-0.000757;0.020208;,
  -0.999985;0.000757;-0.005348;,
  0.999981;-0.000757;-0.006086;,
  -0.999930;0.000757;-0.011781;,
  0.999924;-0.000757;-0.012304;,
  0.999985;-0.000757;-0.005440;,
  -0.999988;0.000757;-0.004916;,
  0.999966;-0.000757;-0.008200;,
  -0.999972;0.000757;-0.007410;,
  0.999967;-0.000757;-0.008158;,
  -0.999973;0.000757;-0.007367;,
  0.999934;-0.000757;-0.011500;,
  -0.999942;0.000757;-0.010706;,
  0.999764;-0.000757;-0.021702;,
  -0.999780;0.000757;-0.020983;,
  0.998409;-0.000756;-0.056374;,
  -0.998450;0.000756;-0.055654;,
  0.987452;-0.000748;-0.157917;,
  -0.987578;0.000748;-0.157127;,
  0.980845;-0.000743;-0.194790;,
  -0.980975;0.000743;-0.194135;,
  0.977523;-0.000740;-0.210826;,
  -0.977667;0.000740;-0.210159;,
  0.956951;-0.000725;-0.290247;,
  -0.957190;0.000725;-0.289458;,
  0.933392;-0.000707;-0.358859;,
  -0.933686;0.000707;-0.358091;,
  0.912681;-0.000691;-0.408672;,
  -0.913032;0.000692;-0.407887;,
  0.804284;-0.000609;-0.594245;,
  -0.804821;0.000610;-0.593517;,
  0.491436;-0.000372;-0.870913;,
  -0.492274;0.000373;-0.870441;,
  -0.000502;0.000000;-1.000000;;
  73;
  4;18,18,6,6;,
  4;6,6,5,5;,
  4;5,5,14,14;,
  4;14,13,13,14;,
  4;13,12,12,13;,
  4;12,17,17,12;,
  4;17,11,11,17;,
  4;11,2,2,11;,
  4;2,7,7,2;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,3,3,10;,
  4;3,4,4,3;,
  4;4,16,16,4;,
  4;16,15,15,16;,
  4;15,1,1,15;,
  3;1,0,1;,
  4;25,25,37,37;,
  4;24,24,25,25;,
  4;33,33,24,24;,
  4;33,32,32,33;,
  4;32,31,31,32;,
  4;31,36,36,31;,
  4;36,30,30,36;,
  4;30,21,21,30;,
  4;21,26,26,21;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,22,22,29;,
  4;22,23,23,22;,
  4;23,35,35,23;,
  4;35,34,34,35;,
  4;34,20,20,34;,
  3;20,19,20;,
  4;38,39,39,38;,
  4;40,40,40,40;,
  4;41,42,42,41;,
  4;39,43,43,39;,
  4;44,41,41,44;,
  4;43,45,45,43;,
  4;46,44,44,46;,
  4;47,46,46,47;,
  4;45,48,48,45;,
  4;49,47,47,49;,
  4;48,50,50,48;,
  4;51,49,49,51;,
  4;50,52,52,50;,
  4;53,51,51,53;,
  4;52,54,54,52;,
  4;55,53,53,55;,
  4;54,56,56,54;,
  4;57,55,55,57;,
  4;56,58,58,56;,
  4;59,57,57,59;,
  4;58,60,60,58;,
  4;61,59,59,61;,
  4;60,62,62,60;,
  4;63,61,61,63;,
  4;62,64,64,62;,
  4;65,63,63,65;,
  4;64,66,66,64;,
  4;67,65,65,67;,
  4;66,68,68,66;,
  4;69,67,67,69;,
  4;68,70,70,68;,
  4;71,69,69,71;,
  4;70,72,72,70;,
  4;73,71,71,73;,
  4;72,74,74,72;,
  4;75,73,73,75;,
  4;74,75,75,74;;
 }
 MeshTextureCoords {
  74;
  0.589342;-0.195813;,
  0.756398;-0.062790;,
  0.746924;-0.157297;,
  0.937457;-0.158936;,
  0.746388;-0.234249;,
  0.936922;-0.235888;,
  0.745850;-0.291869;,
  0.936384;-0.293508;,
  0.745674;-0.310656;,
  0.936208;-0.312295;,
  0.744919;-0.391555;,
  0.935453;-0.393194;,
  0.743681;-0.524654;,
  0.934215;-0.526293;,
  0.743073;-0.590221;,
  0.933607;-0.591860;,
  0.735931;-0.675942;,
  0.926465;-0.677581;,
  0.731312;-0.723965;,
  0.921846;-0.725604;,
  0.728766;-0.758368;,
  0.919300;-0.760007;,
  0.726673;-0.801638;,
  0.917207;-0.803277;,
  0.726796;-0.826366;,
  0.917330;-0.828005;,
  0.724784;-0.873642;,
  0.915319;-0.875280;,
  0.723939;-0.908572;,
  0.914473;-0.910210;,
  0.721928;-0.952038;,
  0.912462;-0.953677;,
  0.721867;-0.953219;,
  0.912400;-0.954858;,
  0.722707;-0.963175;,
  0.913240;-0.964814;,
  0.722702;-0.965687;,
  0.937457;-0.158936;,
  0.746924;-0.157297;,
  0.756398;-0.062790;,
  0.589342;-0.195813;,
  0.936922;-0.235888;,
  0.746388;-0.234249;,
  0.936384;-0.293508;,
  0.745850;-0.291869;,
  0.936208;-0.312295;,
  0.745674;-0.310656;,
  0.935453;-0.393194;,
  0.744919;-0.391555;,
  0.934215;-0.526293;,
  0.743681;-0.524654;,
  0.933607;-0.591860;,
  0.743073;-0.590221;,
  0.926465;-0.677581;,
  0.735931;-0.675942;,
  0.921846;-0.725604;,
  0.731312;-0.723965;,
  0.919300;-0.760007;,
  0.728766;-0.758368;,
  0.917207;-0.803277;,
  0.726673;-0.801638;,
  0.917330;-0.828005;,
  0.726796;-0.826366;,
  0.915319;-0.875280;,
  0.724784;-0.873642;,
  0.914473;-0.910210;,
  0.723939;-0.908572;,
  0.912462;-0.953677;,
  0.721928;-0.952038;,
  0.912400;-0.954858;,
  0.721867;-0.953219;,
  0.913240;-0.964814;,
  0.722707;-0.963175;,
  0.722702;-0.965687;;
 }
 MeshVertexColors {
  74;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;;
 }
}
