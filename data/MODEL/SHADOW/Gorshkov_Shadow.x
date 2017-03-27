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
 46;
 0.00000;49.41345;-230.52945;,
 4.97630;49.41345;-220.21182;,
 6.01462;-49.41345;-220.21182;,
 0.00000;-49.41345;-230.52945;,
 -4.97630;49.41345;-220.21182;,
 -6.01462;-49.41345;-220.21182;,
 -9.70090;49.41345;-206.75507;,
 -9.70090;-49.41345;-206.75507;,
 9.70087;49.41345;-206.75507;,
 9.70087;-49.41345;-206.75507;,
 -17.22869;49.41345;-179.69635;,
 -17.22869;-49.41345;-179.69635;,
 17.22869;49.41345;-179.69635;,
 17.22869;-49.41345;-179.69635;,
 24.80065;49.41345;-131.00562;,
 24.80065;-49.41345;-131.00562;,
 -24.80065;49.41345;-131.00562;,
 -24.80065;-49.41345;-131.00562;,
 -30.76848;49.41345;-89.45842;,
 -30.76848;-49.41345;-89.45842;,
 30.76848;49.41345;-89.45842;,
 30.76848;-49.41345;-89.45842;,
 -31.69218;49.41345;-52.74755;,
 -31.69218;-49.41345;-52.74755;,
 31.69218;49.41345;-52.74755;,
 31.69218;-49.41345;-52.74755;,
 -34.42056;49.41345;20.19932;,
 -34.42056;-49.41345;20.19932;,
 34.42056;49.41345;20.19932;,
 34.42056;-49.41345;20.19932;,
 -36.10147;49.41345;82.51789;,
 -36.10147;-49.41345;82.51789;,
 36.10147;49.41345;82.51789;,
 36.10147;-49.41345;82.51789;,
 -35.88303;49.41345;116.37709;,
 -35.88303;-49.41345;116.37709;,
 35.88303;49.41345;116.37709;,
 35.88303;-49.41345;116.37709;,
 -35.52819;49.41345;164.75066;,
 -35.52819;-49.41345;164.75066;,
 35.52819;49.41345;164.75066;,
 35.52819;-49.41345;164.75066;,
 -35.72273;49.41345;230.52945;,
 -35.72273;-49.41345;230.52945;,
 35.72273;49.41345;230.52945;,
 35.72273;-49.41345;230.52945;;
 
 45;
 4;0,1,2,3;,
 4;4,0,3,5;,
 3;4,1,0;,
 4;6,4,5,7;,
 4;1,8,9,2;,
 4;1,4,6,8;,
 4;10,6,7,11;,
 4;8,12,13,9;,
 4;8,6,10,12;,
 4;12,14,15,13;,
 4;16,10,11,17;,
 4;14,12,10,16;,
 4;18,16,17,19;,
 4;14,20,21,15;,
 4;16,18,20,14;,
 4;22,18,19,23;,
 4;20,24,25,21;,
 4;18,22,24,20;,
 4;26,22,23,27;,
 4;24,28,29,25;,
 4;22,26,28,24;,
 4;30,26,27,31;,
 4;28,32,33,29;,
 4;26,30,32,28;,
 4;34,30,31,35;,
 4;32,36,37,33;,
 4;30,34,36,32;,
 4;38,34,35,39;,
 4;36,40,41,37;,
 4;34,38,40,36;,
 4;42,38,39,43;,
 4;44,42,43,45;,
 4;40,44,45,41;,
 4;38,42,44,40;,
 3;2,5,3;,
 4;2,9,7,5;,
 4;9,13,11,7;,
 4;13,15,17,11;,
 4;15,21,19,17;,
 4;21,25,23,19;,
 4;25,29,27,23;,
 4;29,33,31,27;,
 4;33,37,35,31;,
 4;37,41,39,35;,
 4;41,45,43,39;;
 
 MeshMaterialList {
  2;
  45;
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
   0.387100;0.387100;0.387100;1.000000;;
   60.000000;
   0.100000;0.100000;0.100000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\bizch\\Desktop\\Gorshkov_Normal.tga";
   }
  }
  Material {
   0.452900;0.452900;0.452900;1.000000;;
   60.000000;
   0.100000;0.100000;0.100000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\bizch\\Desktop\\player.tga";
   }
  }
 }
 MeshNormals {
  27;
  -0.996482;0.000000;-0.083812;,
  0.996482;0.000000;-0.083812;,
  0.999947;0.000000;-0.010257;,
  0.999998;0.000000;0.002189;,
  0.000000;0.000000;1.000000;,
  0.999483;0.000000;-0.032170;,
  0.999511;0.000000;-0.031265;,
  0.999976;0.000000;0.006893;,
  -0.999947;0.000000;-0.010257;,
  -0.999998;0.000000;0.002189;,
  -0.999996;0.000000;-0.002957;,
  -0.999483;0.000000;-0.032170;,
  -0.999511;0.000000;-0.031266;,
  -0.999976;0.000000;0.006893;,
  0.922774;0.004771;-0.385312;,
  0.959115;0.002480;-0.283004;,
  0.882987;0.004542;-0.469376;,
  0.977442;0.000000;-0.211206;,
  -0.922774;0.004771;-0.385313;,
  -0.959115;0.002480;-0.283005;,
  -0.977442;0.000000;-0.211205;,
  0.988999;0.000000;-0.147925;,
  -0.988999;0.000000;-0.147925;,
  -0.882987;0.004542;-0.469376;,
  0.000000;1.000000;0.000000;,
  0.999996;0.000000;-0.002957;,
  0.000000;-1.000000;0.000000;;
  45;
  4;16,14,14,16;,
  4;18,23,23,18;,
  3;24,24,24;,
  4;19,18,18,19;,
  4;14,15,15,14;,
  4;24,24,24,24;,
  4;20,19,19,20;,
  4;15,17,17,15;,
  4;24,24,24,24;,
  4;17,21,21,17;,
  4;22,20,20,22;,
  4;24,24,24,24;,
  4;0,22,22,0;,
  4;21,1,1,21;,
  4;24,24,24,24;,
  4;12,0,0,12;,
  4;1,6,6,1;,
  4;24,24,24,24;,
  4;11,12,12,11;,
  4;6,5,5,6;,
  4;24,24,24,24;,
  4;8,11,11,8;,
  4;5,2,2,5;,
  4;24,24,24,24;,
  4;13,8,8,13;,
  4;2,7,7,2;,
  4;24,24,24,24;,
  4;9,13,13,9;,
  4;7,3,3,7;,
  4;24,24,24,24;,
  4;10,9,9,10;,
  4;4,4,4,4;,
  4;3,25,25,3;,
  4;24,24,24,24;,
  3;26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;;
 }
 MeshTextureCoords {
  46;
  0.034544;0.055976;,
  0.052340;0.057342;,
  0.052340;0.057342;,
  0.034544;0.055976;,
  0.052340;0.057342;,
  0.052340;0.057342;,
  0.075687;0.059541;,
  0.075687;0.059541;,
  0.075687;0.059541;,
  0.075687;0.059541;,
  0.132467;0.061456;,
  0.132467;0.061456;,
  0.132467;0.061456;,
  0.132467;0.061456;,
  0.199799;0.065133;,
  0.199799;0.065133;,
  0.199799;0.065133;,
  0.199799;0.065133;,
  0.271878;0.063667;,
  0.271878;0.063667;,
  0.271878;0.063667;,
  0.271878;0.063667;,
  0.335566;0.066298;,
  0.335566;0.066298;,
  0.335566;0.066298;,
  0.335566;0.066298;,
  0.462119;0.056134;,
  0.462119;0.056134;,
  0.462119;0.056134;,
  0.462119;0.056134;,
  0.570234;0.056106;,
  0.570234;0.056106;,
  0.570235;0.056106;,
  0.570235;0.056106;,
  0.628976;0.059549;,
  0.628976;0.059549;,
  0.628976;0.059549;,
  0.628976;0.059549;,
  0.712897;0.064636;,
  0.712897;0.064636;,
  0.712897;0.064636;,
  0.712897;0.064636;,
  0.863313;0.064291;,
  0.863313;0.064291;,
  0.981174;0.064291;,
  0.981174;0.064291;;
 }
 MeshVertexColors {
  46;
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
  45;1.000000;1.000000;1.000000;1.000000;;
 }
}
