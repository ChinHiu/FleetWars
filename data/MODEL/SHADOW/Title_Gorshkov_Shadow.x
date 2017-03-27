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
 82;
 -25.24815;55.88591;-191.42735;,
 -15.74020;55.88589;-224.02910;,
 -15.74019;-54.12162;-224.02907;,
 -25.24814;-54.12160;-191.42732;,
 0.79103;55.88592;-193.11818;,
 0.79104;-54.12160;-193.11815;,
 0.79103;55.88592;-193.11815;,
 15.02589;55.88592;-146.22624;,
 15.02590;-54.12160;-146.22624;,
 -32.75389;55.88590;-132.96826;,
 -25.24815;55.88591;-191.42732;,
 -32.75388;-54.12161;-132.96826;,
 21.75326;55.88590;-113.62800;,
 21.75327;-54.12161;-113.62801;,
 -34.12913;55.88590;-85.94914;,
 -34.12913;-54.12161;-85.94915;,
 22.81151;55.88590;-105.12526;,
 22.81151;-54.12161;-105.12527;,
 -35.86926;55.88590;-74.01069;,
 -35.86926;-54.12161;-74.01070;,
 22.81152;55.88590;-105.12527;,
 16.11814;55.88590;-96.34942;,
 16.11814;-54.12161;-96.34943;,
 -36.54063;55.88590;-54.09396;,
 -35.86926;55.88590;-74.01070;,
 -36.54063;-54.12161;-54.09396;,
 -37.68563;55.88590;33.98847;,
 -37.68563;-54.12161;33.98847;,
 -39.21483;55.88590;108.54268;,
 -39.21483;-54.12161;108.54268;,
 -40.31233;55.88591;162.33234;,
 -39.21483;55.88590;108.54267;,
 -40.31233;-54.12160;156.84554;,
 -35.71617;55.88591;232.38406;,
 -36.81974;-54.12160;232.38407;,
 17.46185;55.88592;231.97287;,
 17.46185;-54.12160;231.97289;,
 18.11809;55.88590;200.26837;,
 19.39614;-54.12161;200.26838;,
 26.82604;55.88590;-13.46690;,
 16.11814;55.88590;-96.34943;,
 26.19145;55.88590;13.69439;,
 21.53456;-54.12161;-10.93122;,
 25.00788;-54.12161;13.69439;,
 33.46359;55.88590;-18.47796;,
 28.82504;55.88590;-11.56277;,
 32.05437;-54.12161;-11.56277;,
 36.69291;-54.12161;-18.47797;,
 32.49302;55.88590;-79.98952;,
 34.28152;55.88590;-72.19079;,
 34.28152;-54.12161;-74.43019;,
 32.92304;-54.12161;-82.22890;,
 26.35752;-54.12161;-85.00764;,
 26.35752;55.88590;-85.00764;,
 19.12771;-54.12161;-87.17510;,
 19.12771;55.88590;-87.17511;,
 35.75123;-54.12161;-66.11385;,
 35.75124;55.88590;-64.56447;,
 27.67861;55.88590;-2.46009;,
 31.33666;-54.12161;-2.46009;,
 37.69460;-54.12161;-51.32319;,
 36.01533;55.88590;-51.32319;,
 25.86568;55.88590;45.35401;,
 25.96898;55.88590;54.37421;,
 25.96898;-54.12161;54.37419;,
 26.96019;-54.12161;45.35401;,
 30.68249;55.88590;78.05158;,
 29.35045;55.88590;139.71491;,
 30.62850;-54.12161;139.71494;,
 31.31063;-54.12161;77.52396;,
 27.22826;-54.12161;69.58916;,
 25.96898;55.88590;54.37419;,
 26.87314;55.88590;70.06805;,
 38.41317;-54.12161;-40.90245;,
 37.32058;55.88590;-40.90246;,
 37.35134;55.88590;-28.39036;,
 35.97910;-54.12161;-25.85559;,
 19.50504;55.88590;159.88921;,
 18.11809;55.88590;200.26838;,
 20.86179;-54.12161;159.27865;,
 29.35045;55.88590;139.71494;,
 -40.31233;55.88591;162.33235;;
 
 61;
 4;0,1,2,3;,
 4;1,4,5,2;,
 3;1,0,4;,
 4;6,7,8,5;,
 4;9,10,3,11;,
 4;9,7,6,10;,
 4;7,12,13,8;,
 4;14,9,11,15;,
 4;14,12,7,9;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;18,16,12,14;,
 4;20,21,22,17;,
 4;23,24,19,25;,
 4;23,21,20,24;,
 4;26,23,25,27;,
 4;28,26,27,29;,
 4;30,31,29,32;,
 4;33,30,32,34;,
 4;35,33,34,36;,
 4;37,35,36,38;,
 4;30,33,35,37;,
 3;5,3,2;,
 4;5,8,11,3;,
 4;8,13,15,11;,
 4;13,17,19,15;,
 4;17,22,25,19;,
 4;38,36,34,32;,
 5;39,40,23,26,41;,
 5;42,43,27,25,22;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 6;54,52,51,50,42,22;,
 4;54,22,40,55;,
 4;55,53,52,54;,
 6;55,40,39,49,48,53;,
 4;56,50,49,57;,
 5;58,45,44,39,41;,
 4;58,41,43,59;,
 4;59,46,45,58;,
 5;59,43,42,47,46;,
 4;60,56,57,61;,
 4;62,63,64,65;,
 4;65,43,41,62;,
 5;62,41,26,28,63;,
 5;65,64,29,27,43;,
 4;66,67,68,69;,
 4;70,64,71,72;,
 4;72,66,69,70;,
 6;72,71,31,30,67,66;,
 6;70,69,68,32,29,64;,
 4;73,60,61,74;,
 7;75,74,61,57,49,39,44;,
 4;75,44,47,76;,
 4;76,73,74,75;,
 7;76,47,42,50,56,60,73;,
 4;77,78,38,79;,
 4;79,68,80,77;,
 4;77,80,81,78;,
 4;79,38,32,68;;
 
 MeshMaterialList {
  4;
  61;
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
  94;
  -0.960007;-0.000000;-0.279976;,
  -0.978912;-0.000000;-0.204283;,
  0.923798;0.000000;-0.382881;,
  0.969130;0.000000;-0.246552;,
  -0.996923;-0.000000;-0.078387;,
  0.986636;0.000000;-0.162939;,
  -0.996219;-0.000000;-0.086880;,
  0.965385;-0.000000;0.260828;,
  -0.996023;0.000000;-0.089099;,
  0.986038;-0.000000;0.166521;,
  -0.999728;0.000000;-0.023345;,
  -0.000000;-1.000000;0.000000;,
  -0.999860;0.000000;-0.016753;,
  0.999939;0.003351;-0.010533;,
  -0.999779;0.000254;-0.021032;,
  -0.999851;0.002183;0.017149;,
  0.971910;0.009305;0.235168;,
  0.999242;0.008836;0.037916;,
  0.007653;-0.000038;0.999971;,
  -0.998433;0.003853;0.055830;,
  0.881815;-0.000000;-0.471596;,
  -0.991858;-0.000000;-0.127348;,
  0.956882;0.000000;-0.290478;,
  0.992344;0.000000;-0.123507;,
  -0.989544;-0.000000;-0.144234;,
  -0.999432;0.000000;-0.033690;,
  0.795125;-0.000000;0.606445;,
  -0.000000;1.000000;0.000000;,
  -0.000001;1.000000;-0.000000;,
  0.998788;0.004954;0.048978;,
  -0.999790;0.000000;-0.020507;,
  0.997545;0.001737;-0.070006;,
  -0.999768;0.000509;-0.021557;,
  0.999830;0.008636;0.016282;,
  0.896667;0.009522;0.442603;,
  0.999316;0.011872;0.035028;,
  0.000000;1.000000;0.000000;,
  0.999150;0.005799;0.040802;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.981843;0.004527;-0.189642;,
  0.940204;0.028596;0.339408;,
  0.934037;0.019365;0.356651;,
  0.405112;0.004641;-0.914255;,
  0.817672;0.008280;-0.575625;,
  -0.000000;-1.000000;0.000000;,
  0.697958;-0.000000;-0.716139;,
  0.991677;0.005841;-0.128615;,
  0.985828;0.020716;0.166473;,
  -0.000002;1.000000;-0.000000;,
  0.996248;0.010547;-0.085900;,
  0.999929;0.002281;0.011674;,
  0.975441;0.007552;-0.220130;,
  0.965053;0.003964;-0.262026;,
  0.999939;0.006617;-0.008879;,
  0.994059;0.007015;0.108616;,
  -0.000000;1.000000;-0.000000;,
  0.969645;0.010941;0.244271;,
  -0.000000;1.000000;-0.000001;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.950181;-0.000000;-0.311700;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000001;1.000000;-0.000000;,
  0.994641;0.004954;0.103268;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;;
  61;
  4;0,0,0,1;,
  4;20,20,2,20;,
  3;58,58,58;,
  4;22,3,3,2;,
  4;4,21,1,4;,
  4;59,59,60,60;,
  4;3,5,5,3;,
  4;6,4,4,6;,
  4;61,61,59,59;,
  4;5,23,7,5;,
  4;24,6,6,8;,
  4;62,62,61,61;,
  4;26,26,9,7;,
  4;10,25,8,10;,
  4;63,62,62,62;,
  4;12,10,10,12;,
  4;30,12,12,14;,
  4;15,32,14,15;,
  4;19,15,15,19;,
  4;18,18,18,18;,
  4;37,37,37,17;,
  4;64,65,65,65;,
  3;66,66,67;,
  4;66,68,68,66;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,72,70;,
  4;73,74,74,75;,
  5;39,27,63,76,28;,
  5;38,11,77,72,71;,
  4;42,41,41,42;,
  4;44,40,40,44;,
  4;44,44,43,43;,
  6;45,45,45,78,38,71;,
  4;46,9,79,46;,
  4;46,43,43,46;,
  6;80,27,39,81,80,80;,
  4;47,40,40,47;,
  5;49,49,82,39,28;,
  4;48,83,83,48;,
  4;48,41,41,48;,
  5;84,11,38,85,84;,
  4;50,47,47,50;,
  4;51,29,13,51;,
  4;51,83,83,51;,
  5;86,28,76,86,86;,
  5;87,88,88,77,11;,
  4;52,33,16,52;,
  4;53,13,31,53;,
  4;53,52,52,53;,
  6;89,89,89,64,89,89;,
  6;90,90,91,75,88,88;,
  4;54,50,50,54;,
  7;56,56,56,56,81,39,82;,
  4;55,42,42,55;,
  4;55,54,54,55;,
  7;92,85,38,78,92,92,92;,
  4;57,35,17,57;,
  4;57,16,34,57;,
  4;36,36,36,36;,
  4;93,73,75,91;;
 }
 MeshTextureCoords {
  82;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
 MeshVertexColors {
  82;
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
  81;1.000000;1.000000;1.000000;1.000000;;
 }
}
