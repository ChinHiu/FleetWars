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
 146;
 0.00000;-6.67353;-11.08081;,
 0.00000;-2.25900;-8.99595;,
 2.77990;-2.25900;-8.55566;,
 3.42416;-6.67353;-10.53848;,
 5.28769;-2.25900;-7.27787;,
 6.51314;-6.67353;-8.96457;,
 7.27787;-2.25900;-5.28769;,
 8.96457;-6.67353;-6.51314;,
 8.55565;-2.25900;-2.77990;,
 10.53848;-6.67353;-3.42416;,
 8.99595;-2.25900;-0.00000;,
 11.08081;-6.67353;-0.00000;,
 8.55565;-2.25900;2.77990;,
 10.53848;-6.67353;3.42416;,
 7.27787;-2.25900;5.28768;,
 8.96457;-6.67353;6.51314;,
 5.28769;-2.25900;7.27788;,
 6.51314;-6.67353;8.96457;,
 2.77990;-2.25900;8.55565;,
 3.42416;-6.67353;10.53848;,
 0.00000;-2.25900;8.99595;,
 0.00000;-6.67353;11.08081;,
 -2.77990;-2.25900;8.55565;,
 -3.42417;-6.67353;10.53848;,
 -5.28769;-2.25900;7.27787;,
 -6.51314;-6.67353;8.96456;,
 -7.27788;-2.25900;5.28768;,
 -8.96457;-6.67353;6.51313;,
 -8.55566;-2.25900;2.77989;,
 -10.53848;-6.67353;3.42415;,
 -8.99595;-2.25900;-0.00000;,
 -11.08081;-6.67353;-0.00000;,
 -8.55565;-2.25900;-2.77991;,
 -10.53848;-6.67353;-3.42418;,
 -7.27787;-2.25900;-5.28770;,
 -8.96456;-6.67353;-6.51315;,
 -5.28768;-2.25900;-7.27788;,
 -6.51313;-6.67353;-8.96458;,
 -2.77989;-2.25900;-8.55566;,
 -3.42415;-6.67353;-10.53849;,
 -4.92283;-2.14963;-6.77571;,
 -2.58808;-2.14963;-7.96532;,
 0.00000;-2.14963;-8.37522;,
 2.58809;-2.14963;-7.96531;,
 4.92284;-2.14963;-6.77570;,
 6.77570;-2.14963;-4.92284;,
 7.96531;-2.14963;-2.58809;,
 8.37523;-2.14963;-0.00000;,
 7.96531;-2.14963;2.58809;,
 6.77570;-2.14963;4.92283;,
 4.92284;-2.14963;6.77570;,
 2.58809;-2.14963;7.96531;,
 0.00000;-2.14963;8.37523;,
 -2.58809;-2.14963;7.96531;,
 -4.92284;-2.14963;6.77569;,
 -6.77570;-2.14963;4.92282;,
 -7.96532;-2.14963;2.58808;,
 -8.37523;-2.14963;-0.00000;,
 -7.96531;-2.14963;-2.58810;,
 -6.77570;-2.14963;-4.92284;,
 2.16351;-2.74438;-6.65861;,
 0.00000;-2.74438;-7.00129;,
 0.00000;-2.74438;-0.00000;,
 4.11525;-2.74438;-5.66415;,
 5.66416;-2.74438;-4.11525;,
 6.65861;-2.74438;-2.16351;,
 7.00128;-2.74438;-0.00000;,
 6.65861;-2.74438;2.16351;,
 5.66416;-2.74438;4.11525;,
 4.11525;-2.74438;5.66415;,
 2.16351;-2.74438;6.65861;,
 0.00000;-2.74438;7.00128;,
 -2.16352;-2.74438;6.65861;,
 -4.11525;-2.74438;5.66415;,
 -5.66416;-2.74438;4.11525;,
 -6.65862;-2.74438;2.16350;,
 -7.00128;-2.74438;-0.00000;,
 -6.65861;-2.74438;-2.16352;,
 -5.66415;-2.74438;-4.11526;,
 -2.16350;-2.74438;-6.65861;,
 -4.11524;-2.74438;-5.66416;,
 -2.84347;-0.67448;5.76240;,
 -4.81204;-1.98877;0.69861;,
 -3.79383;-1.40375;4.82389;,
 0.71028;5.48346;1.29935;,
 1.01352;6.67353;1.23251;,
 1.13496;3.18558;-4.95771;,
 0.79309;2.49678;-4.33461;,
 0.99261;0.28478;-7.30054;,
 0.70298;0.52012;-6.20118;,
 -3.61373;0.74719;-6.35641;,
 -3.94080;-1.86194;-6.28956;,
 -6.36047;-1.85746;-2.97500;,
 -5.29016;3.18560;-4.94589;,
 -1.05635;-1.86322;-7.22568;,
 -3.47472;-2.45069;-5.45381;,
 -5.60901;-2.44672;-2.53016;,
 -2.30952;-3.78013;-3.36810;,
 -3.73033;-3.77747;-1.42186;,
 0.00000;-3.78114;-4.11630;,
 3.79383;-1.40375;4.82389;,
 3.62870;-3.47262;0.72891;,
 4.81204;-1.98877;0.69861;,
 3.49884;-3.08314;3.47645;,
 2.84347;-0.67448;5.76240;,
 2.26285;-1.38143;7.49881;,
 1.50233;-2.39284;5.38405;,
 5.75656;-1.33802;0.86396;,
 2.24163;4.80289;5.08731;,
 1.60642;3.27725;8.03718;,
 1.60801;-0.51518;7.59639;,
 3.94080;-1.86194;-6.28956;,
 3.47472;-2.45069;-5.45381;,
 1.05635;-1.86322;-7.22568;,
 -3.62870;-3.47262;0.72891;,
 -3.49884;-3.08314;3.47645;,
 -1.50233;-2.39284;5.38405;,
 -2.26285;-1.38143;7.49884;,
 -5.75656;-1.33802;0.86396;,
 -1.60642;3.27725;8.03718;,
 -2.24163;4.80289;5.08731;,
 -1.60801;-0.51518;7.59639;,
 3.00782;6.57408;1.79043;,
 3.73033;-3.77747;-1.42186;,
 5.60901;-2.44672;-2.53016;,
 2.30952;-3.78013;-3.36810;,
 0.25585;3.27757;8.27000;,
 0.25744;-0.51488;7.82942;,
 6.36047;-1.85746;-2.97500;,
 3.61373;0.74719;-6.35641;,
 5.29016;3.18560;-4.94589;,
 0.49094;-1.38115;7.82946;,
 0.49749;-2.39270;5.52023;,
 0.58170;4.80286;5.08258;,
 -3.00782;6.57408;1.79043;,
 -0.25744;-0.51488;7.82942;,
 -0.25585;3.27757;8.27000;,
 -0.99261;0.28478;-7.30054;,
 -0.49094;-1.38115;7.82946;,
 -0.49749;-2.39270;5.52023;,
 -0.58170;4.80286;5.08258;,
 -1.01352;6.67353;1.23251;,
 -1.13496;3.18558;-4.95771;,
 -0.71028;5.48346;1.29935;,
 -0.79309;2.49678;-4.33461;,
 -0.70298;0.52012;-6.20118;;
 
 149;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;39,38,1,0;,
 4;36,40,41,38;,
 4;41,42,1,38;,
 4;42,43,2,1;,
 4;43,44,4,2;,
 4;44,45,6,4;,
 4;46,8,6,45;,
 4;46,47,10,8;,
 4;48,12,10,47;,
 4;49,14,12,48;,
 4;49,50,16,14;,
 4;51,18,16,50;,
 4;52,20,18,51;,
 4;20,52,53,22;,
 4;22,53,54,24;,
 4;26,55,56,28;,
 4;28,56,57,30;,
 4;57,58,32,30;,
 4;58,59,34,32;,
 4;59,40,36,34;,
 3;60,61,62;,
 3;63,60,62;,
 3;64,63,62;,
 3;65,64,62;,
 3;66,65,62;,
 3;67,66,62;,
 3;68,67,62;,
 3;69,68,62;,
 3;70,69,62;,
 3;71,70,62;,
 3;72,71,62;,
 3;73,72,62;,
 3;74,73,62;,
 3;75,74,62;,
 3;76,75,62;,
 3;77,76,62;,
 3;78,77,62;,
 3;79,80,62;,
 3;61,79,62;,
 4;52,71,72,53;,
 4;52,51,70,71;,
 4;51,50,69,70;,
 4;50,49,68,69;,
 4;49,48,67,68;,
 4;48,47,66,67;,
 4;47,46,65,66;,
 4;46,45,64,65;,
 4;45,44,63,64;,
 4;63,44,43,60;,
 4;60,43,42,61;,
 4;79,61,42,41;,
 4;41,40,80,79;,
 4;40,59,78,80;,
 4;59,58,77,78;,
 4;58,57,76,77;,
 4;57,56,75,76;,
 4;56,55,74,75;,
 4;55,54,73,74;,
 4;73,54,53,72;,
 4;24,54,55,26;,
 3;80,78,62;,
 3;81,82,83;,
 4;84,85,86,87;,
 4;86,88,89,87;,
 4;90,91,92,93;,
 3;94,95,91;,
 4;96,95,97,98;,
 4;95,96,92,91;,
 3;94,99,95;,
 3;100,101,102;,
 3;101,100,103;,
 3;100,102,104;,
 3;100,105,106;,
 3;102,107,104;,
 3;106,103,100;,
 3;104,108,109;,
 3;110,104,109;,
 3;111,112,113;,
 3;82,114,83;,
 3;115,83,114;,
 3;116,117,83;,
 3;81,118,82;,
 3;83,115,116;,
 3;119,120,81;,
 3;119,81,121;,
 4;104,107,122,108;,
 4;102,101,123,124;,
 4;125,112,124,123;,
 4;109,126,127,110;,
 4;128,111,129,130;,
 4;129,111,113,88;,
 4;131,105,110,127;,
 4;105,100,104,110;,
 4;128,124,112,111;,
 4;107,102,124,128;,
 4;131,132,106,105;,
 4;85,133,108,122;,
 4;122,130,86,85;,
 4;86,130,129,88;,
 4;107,128,130,122;,
 4;134,118,81,120;,
 4;98,114,82,96;,
 4;135,136,119,121;,
 4;94,91,90,137;,
 4;121,117,138,135;,
 4;81,83,117,121;,
 4;96,82,118,92;,
 4;116,139,138,117;,
 4;120,140,141,134;,
 4;142,93,134,141;,
 4;90,93,142,137;,
 4;142,141,143,144;,
 4;145,137,142,144;,
 4;93,92,118,134;,
 4;109,108,133,126;,
 4;140,120,119,136;,
 4;88,113,94,137;,
 3;113,112,99;,
 3;94,113,99;,
 4;145,89,88,137;,
 4;144,87,89,145;,
 4;144,143,84,87;,
 4;141,85,84,143;,
 4;85,141,140,133;,
 4;133,140,136,126;,
 4;126,136,135,127;,
 4;127,135,138,131;,
 4;131,138,139,132;,
 3;99,97,95;,
 3;112,125,99;;
 
 MeshMaterialList {
  2;
  149;
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
  173;
  0.000000;0.427044;-0.904231;,
  0.279423;0.427045;-0.859974;,
  0.531493;0.427045;-0.731538;,
  0.731538;0.427045;-0.531494;,
  0.859974;0.427045;-0.279423;,
  0.904230;0.427045;-0.000000;,
  0.859974;0.427045;0.279422;,
  0.731538;0.427045;0.531493;,
  0.531493;0.427044;0.731538;,
  0.279422;0.427045;0.859974;,
  0.000000;0.427045;0.904230;,
  -0.279423;0.427045;0.859974;,
  -0.531494;0.427045;0.731537;,
  -0.731538;0.427045;0.531493;,
  -0.859974;0.427045;0.279422;,
  -0.904231;0.427045;-0.000001;,
  -0.859974;0.427045;-0.279423;,
  -0.731537;0.427045;-0.531494;,
  -0.531492;0.427045;-0.731539;,
  -0.279421;0.427045;-0.859975;,
  0.000000;0.796407;-0.604761;,
  0.186882;0.796407;-0.575162;,
  0.355470;0.796407;-0.489262;,
  0.489262;0.796407;-0.355470;,
  0.575162;0.796407;-0.186881;,
  0.604761;0.796407;-0.000000;,
  0.575162;0.796407;0.186881;,
  0.489262;0.796407;0.355470;,
  0.355470;0.796407;0.489262;,
  0.186881;0.796407;0.575162;,
  0.000000;0.796407;0.604761;,
  -0.186882;0.796407;0.575162;,
  -0.355470;0.796407;0.489262;,
  -0.489262;0.796407;0.355469;,
  -0.575162;0.796407;0.186881;,
  -0.604761;0.796407;-0.000000;,
  -0.575162;0.796407;-0.186882;,
  -0.489261;0.796407;-0.355470;,
  -0.355469;0.796407;-0.489262;,
  -0.186881;0.796407;-0.575162;,
  0.068506;0.993185;0.094290;,
  0.036016;0.993185;0.110845;,
  -0.000000;0.993185;0.116550;,
  -0.036016;0.993185;0.110845;,
  -0.068505;0.993185;0.094290;,
  -0.094290;0.993185;0.068505;,
  -0.110844;0.993185;0.036015;,
  -0.116549;0.993185;0.000000;,
  -0.110844;0.993185;-0.036015;,
  -0.094290;0.993185;-0.068505;,
  -0.068505;0.993185;-0.094290;,
  -0.036015;0.993185;-0.110844;,
  0.000000;0.993185;-0.116548;,
  0.036016;0.993185;-0.110844;,
  0.068506;0.993185;-0.094290;,
  0.094290;0.993185;-0.068506;,
  0.110844;0.993185;-0.036015;,
  0.116549;0.993185;0.000000;,
  0.110844;0.993185;0.036016;,
  0.094290;0.993185;0.068506;,
  -0.000000;0.979252;0.202644;,
  -0.062621;0.979252;0.192726;,
  -0.119111;0.979252;0.163942;,
  -0.163942;0.979253;0.119111;,
  -0.192726;0.979253;0.062620;,
  -0.202644;0.979252;0.000000;,
  -0.192726;0.979253;-0.062620;,
  -0.163942;0.979253;-0.119111;,
  -0.119111;0.979253;-0.163942;,
  -0.062620;0.979253;-0.192726;,
  0.000000;0.979253;-0.202644;,
  0.062620;0.979253;-0.192726;,
  0.119111;0.979252;-0.163943;,
  0.163943;0.979252;-0.119111;,
  0.192726;0.979252;-0.062620;,
  0.202644;0.979252;0.000000;,
  0.192726;0.979252;0.062621;,
  0.163942;0.979252;0.119111;,
  0.119111;0.979252;0.163943;,
  0.062620;0.979252;0.192726;,
  0.000000;1.000000;0.000000;,
  -0.948530;0.270980;-0.163895;,
  -0.937827;0.272635;-0.214828;,
  -0.924581;0.273552;-0.265179;,
  -0.721342;0.643480;0.256124;,
  -0.637699;0.768765;0.048377;,
  -0.866874;0.327631;0.375748;,
  -0.718139;-0.631842;-0.291636;,
  -0.595095;-0.324043;-0.735431;,
  -0.482073;0.308093;-0.820173;,
  -0.431566;0.199383;-0.879771;,
  0.000000;-0.871415;-0.490547;,
  -0.575734;-0.815627;-0.057304;,
  -0.271147;-0.863742;-0.424770;,
  -0.600298;-0.797568;-0.059398;,
  -0.291156;-0.872121;-0.393235;,
  -0.144341;-0.594421;-0.791093;,
  0.700816;-0.624294;0.345129;,
  0.575733;-0.815627;-0.057304;,
  0.271146;-0.863742;-0.424770;,
  0.778144;-0.470511;0.416066;,
  0.600298;-0.797568;-0.059398;,
  0.291156;-0.872121;-0.393235;,
  0.645654;-0.713137;0.273068;,
  0.837964;-0.512853;0.186542;,
  0.086893;-0.048338;0.995044;,
  0.541938;0.093911;0.835155;,
  0.866875;0.327629;0.375749;,
  0.718139;-0.631842;-0.291636;,
  0.358671;-0.639951;-0.679571;,
  0.084719;-0.114961;0.989751;,
  0.730645;-0.015042;0.682591;,
  0.919519;0.176554;0.351160;,
  0.482073;0.308093;-0.820173;,
  0.431566;0.199383;-0.879771;,
  0.088679;0.018536;0.995888;,
  0.255336;-0.906153;0.337179;,
  0.032557;-0.914619;0.403003;,
  0.321442;-0.827387;0.460549;,
  0.925744;0.248566;0.284980;,
  0.541121;-0.782247;0.308670;,
  -0.001330;0.897405;0.441206;,
  0.144341;-0.594421;-0.791093;,
  -0.778144;-0.470511;0.416066;,
  -0.837964;-0.512853;0.186542;,
  -0.086890;-0.048335;0.995045;,
  -0.541936;0.093917;0.835156;,
  -0.084719;-0.114961;0.989751;,
  -0.730645;-0.015042;0.682591;,
  -0.919519;0.176554;0.351160;,
  -0.088674;0.018542;0.995888;,
  -0.255334;-0.906155;0.337177;,
  -0.032555;-0.914620;0.403003;,
  -0.321440;-0.827389;0.460547;,
  -0.925744;0.248566;0.284980;,
  -0.541121;-0.782247;0.308670;,
  0.001330;0.897405;0.441206;,
  -0.017445;0.987873;0.154284;,
  -0.090662;0.741709;-0.664567;,
  -0.143546;0.183468;-0.972489;,
  0.948530;0.270980;-0.163895;,
  0.937827;0.272636;-0.214828;,
  0.924581;0.273552;-0.265179;,
  -0.164328;-0.847221;-0.505185;,
  0.721344;0.643476;0.256127;,
  0.637699;0.768765;0.048377;,
  0.475319;-0.788883;0.389533;,
  -0.645654;-0.713137;0.273068;,
  -0.700816;-0.624294;0.345128;,
  -0.475319;-0.788883;0.389533;,
  0.771585;-0.012006;-0.636012;,
  0.143546;0.183468;-0.972489;,
  0.523659;0.287411;0.801983;,
  0.017445;0.987873;0.154284;,
  -0.002662;0.894005;0.448050;,
  0.026604;0.999585;-0.011043;,
  0.089632;0.879866;-0.466692;,
  0.090661;0.741709;-0.664567;,
  0.950115;0.278448;0.140530;,
  -0.523653;0.287424;0.801982;,
  0.002662;0.894005;0.448050;,
  -0.026604;0.999585;-0.011043;,
  -0.089632;0.879866;-0.466692;,
  -0.950115;0.278448;0.140530;,
  0.037114;0.893117;0.448290;,
  0.018561;0.897772;0.440069;,
  -0.037114;0.893117;0.448290;,
  -0.018561;0.897772;0.440069;,
  0.000000;0.871539;-0.490326;,
  0.000000;0.977845;-0.209331;,
  0.000000;0.795633;-0.605779;,
  0.000000;0.883529;-0.468377;,
  0.000000;-0.056080;-0.998426;;
  149;
  4;0,20,21,1;,
  4;1,21,22,2;,
  4;2,22,23,3;,
  4;3,23,24,4;,
  4;4,24,25,5;,
  4;5,25,26,6;,
  4;6,26,27,7;,
  4;7,27,28,8;,
  4;8,28,29,9;,
  4;9,29,30,10;,
  4;10,30,31,11;,
  4;11,31,32,12;,
  4;12,32,33,13;,
  4;13,33,34,14;,
  4;14,34,35,15;,
  4;15,35,36,16;,
  4;16,36,37,17;,
  4;17,37,38,18;,
  4;18,38,39,19;,
  4;19,39,20,0;,
  4;38,40,41,39;,
  4;41,42,20,39;,
  4;42,43,21,20;,
  4;43,44,22,21;,
  4;44,45,23,22;,
  4;46,24,23,45;,
  4;46,47,25,24;,
  4;48,26,25,47;,
  4;49,27,26,48;,
  4;49,50,28,27;,
  4;51,29,28,50;,
  4;52,30,29,51;,
  4;30,52,53,31;,
  4;31,53,54,32;,
  4;33,55,56,34;,
  4;34,56,57,35;,
  4;57,58,36,35;,
  4;58,59,37,36;,
  4;59,40,38,37;,
  3;61,60,80;,
  3;62,61,80;,
  3;63,62,80;,
  3;64,63,80;,
  3;65,64,80;,
  3;66,65,80;,
  3;67,66,80;,
  3;68,67,80;,
  3;69,68,80;,
  3;70,69,80;,
  3;71,70,80;,
  3;72,71,80;,
  3;73,72,80;,
  3;74,73,80;,
  3;75,74,80;,
  3;76,75,80;,
  3;77,76,80;,
  3;79,78,80;,
  3;60,79,80;,
  4;52,70,71,53;,
  4;52,51,69,70;,
  4;51,50,68,69;,
  4;50,49,67,68;,
  4;49,48,66,67;,
  4;48,47,65,66;,
  4;47,46,64,65;,
  4;46,45,63,64;,
  4;45,44,62,63;,
  4;62,44,43,61;,
  4;61,43,42,60;,
  4;79,60,42,41;,
  4;41,40,78,79;,
  4;40,59,77,78;,
  4;59,58,76,77;,
  4;58,57,75,76;,
  4;57,56,74,75;,
  4;56,55,73,74;,
  4;55,54,72,73;,
  4;72,54,53,71;,
  4;32,54,55,33;,
  3;78,77,80;,
  3;86,85,84;,
  4;81,81,82,82;,
  4;82,83,83,82;,
  4;90,88,87,89;,
  3;96,93,143;,
  4;92,93,95,94;,
  4;93,92,87,88;,
  3;96,91,93;,
  3;97,104,103;,
  3;104,97,100;,
  3;144,145,107;,
  3;97,116,118;,
  3;103,120,146;,
  3;118,100,97;,
  3;107,112,111;,
  3;106,107,111;,
  3;109,99,122;,
  3;147,124,148;,
  3;123,148,124;,
  3;133,131,148;,
  3;149,135,147;,
  3;148,123,133;,
  3;128,129,86;,
  3;128,86,126;,
  4;107,119,119,112;,
  4;103,104,101,98;,
  4;102,99,98,101;,
  4;111,110,105,106;,
  4;108,150,114,113;,
  4;114,109,122,151;,
  4;115,152,106,105;,
  4;152,144,107,106;,
  4;108,98,99,109;,
  4;120,103,98,108;,
  4;117,117,118,116;,
  4;153,121,154,155;,
  4;155,156,157,153;,
  4;157,113,114,151;,
  4;119,158,158,119;,
  4;134,134,86,129;,
  4;94,124,147,92;,
  4;125,127,128,126;,
  4;96,88,90,139;,
  4;126,159,130,125;,
  4;86,84,159,126;,
  4;92,147,135,87;,
  4;133,132,132,131;,
  4;160,136,137,161;,
  4;138,162,161,137;,
  4;90,89,138,139;,
  4;141,140,140,141;,
  4;142,142,141,141;,
  4;163,163,134,134;,
  4;164,154,121,165;,
  4;136,160,166,167;,
  4;151,122,96,139;,
  3;122,99,91;,
  3;96,122,91;,
  4;168,168,169,169;,
  4;170,170,168,168;,
  4;170,171,171,170;,
  4;172,172,172,172;,
  4;153,137,136,121;,
  4;121,136,167,165;,
  4;110,127,125,105;,
  4;105,125,130,115;,
  4;117,132,132,117;,
  3;91,95,93;,
  3;99,102,91;;
 }
 MeshTextureCoords {
  146;
  0.872997;0.698121;,
  0.860653;0.676804;,
  0.870493;0.669032;,
  0.888403;0.685339;,
  0.877232;0.658363;,
  0.899622;0.668812;,
  0.880271;0.646305;,
  0.905380;0.649084;,
  0.879870;0.633746;,
  0.904097;0.628573;,
  0.875105;0.622072;,
  0.896970;0.609187;,
  0.867309;0.612358;,
  0.883580;0.593350;,
  0.856838;0.605440;,
  0.866299;0.582671;,
  0.844626;0.602102;,
  0.846921;0.577825;,
  0.832099;0.603018;,
  0.826630;0.578572;,
  0.820373;0.607396;,
  0.807600;0.586264;,
  0.810490;0.615335;,
  0.792246;0.599186;,
  0.803867;0.626040;,
  0.781032;0.616023;,
  0.800586;0.638122;,
  0.776050;0.635661;,
  0.801469;0.650596;,
  0.776755;0.656148;,
  0.805873;0.662274;,
  0.784523;0.675434;,
  0.813770;0.672066;,
  0.797802;0.691065;,
  0.824320;0.678828;,
  0.815051;0.701649;,
  0.836382;0.682113;,
  0.834490;0.706397;,
  0.849010;0.681544;,
  0.854215;0.705031;,
  0.836684;0.679292;,
  0.848392;0.678711;,
  0.859241;0.674371;,
  0.868365;0.667117;,
  0.874634;0.657235;,
  0.877519;0.646015;,
  0.877030;0.634353;,
  0.872677;0.623488;,
  0.865429;0.614427;,
  0.855672;0.608035;,
  0.844346;0.604959;,
  0.832702;0.605764;,
  0.821804;0.609900;,
  0.812638;0.617246;,
  0.806443;0.627168;,
  0.803396;0.638398;,
  0.804205;0.649992;,
  0.808332;0.660858;,
  0.815691;0.669928;,
  0.825455;0.676275;,
  0.863382;0.662655;,
  0.855940;0.668701;,
  0.840534;0.642178;,
  0.868572;0.654595;,
  0.871005;0.645336;,
  0.870487;0.635756;,
  0.867015;0.626793;,
  0.860980;0.619353;,
  0.852966;0.614098;,
  0.843691;0.611602;,
  0.834104;0.612189;,
  0.825108;0.615625;,
  0.817650;0.621707;,
  0.812472;0.629796;,
  0.809989;0.639048;,
  0.810614;0.648602;,
  0.814080;0.657544;,
  0.820097;0.665029;,
  0.828145;0.670238;,
  0.846982;0.672175;,
  0.837394;0.672707;,
  0.700854;0.624594;,
  0.678060;0.598110;,
  0.701005;0.616884;,
  0.666468;0.639833;,
  0.668931;0.641296;,
  0.651862;0.642792;,
  0.652005;0.640568;,
  0.639062;0.641856;,
  0.643500;0.640231;,
  0.644403;0.627230;,
  0.634854;0.621397;,
  0.650482;0.609655;,
  0.654844;0.626321;,
  0.627441;0.633303;,
  0.628737;0.617547;,
  0.648676;0.604188;,
  0.588248;0.593148;,
  0.639652;0.574019;,
  0.553091;0.637431;,
  0.699668;0.661775;,
  0.682167;0.701274;,
  0.675842;0.679629;,
  0.704338;0.680266;,
  0.699980;0.654134;,
  0.707827;0.648904;,
  0.731660;0.655381;,
  0.673448;0.672378;,
  0.682119;0.644134;,
  0.690908;0.642384;,
  0.703921;0.645647;,
  0.634137;0.655360;,
  0.627895;0.659020;,
  0.627351;0.643359;,
  0.685588;0.576328;,
  0.706800;0.598260;,
  0.733566;0.624560;,
  0.708396;0.630128;,
  0.675256;0.605364;,
  0.691072;0.636073;,
  0.682431;0.634063;,
  0.704265;0.633228;,
  0.670394;0.645181;,
  0.636781;0.702372;,
  0.647054;0.672793;,
  0.586610;0.682280;,
  0.691351;0.639772;,
  0.705268;0.640308;,
  0.649103;0.667426;,
  0.643860;0.649826;,
  0.654229;0.651006;,
  0.709720;0.641629;,
  0.733651;0.645164;,
  0.682027;0.640339;,
  0.670915;0.632663;,
  0.705249;0.638557;,
  0.691367;0.638688;,
  0.639304;0.635086;,
  0.709700;0.637459;,
  0.734727;0.635207;,
  0.682126;0.637829;,
  0.669280;0.636508;,
  0.652014;0.634497;,
  0.666268;0.637851;,
  0.652056;0.636726;,
  0.643309;0.636864;;
 }
 MeshVertexColors {
  146;
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
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;;
 }
}