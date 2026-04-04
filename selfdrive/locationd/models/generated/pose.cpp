#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2728703337659485106) {
   out_2728703337659485106[0] = delta_x[0] + nom_x[0];
   out_2728703337659485106[1] = delta_x[1] + nom_x[1];
   out_2728703337659485106[2] = delta_x[2] + nom_x[2];
   out_2728703337659485106[3] = delta_x[3] + nom_x[3];
   out_2728703337659485106[4] = delta_x[4] + nom_x[4];
   out_2728703337659485106[5] = delta_x[5] + nom_x[5];
   out_2728703337659485106[6] = delta_x[6] + nom_x[6];
   out_2728703337659485106[7] = delta_x[7] + nom_x[7];
   out_2728703337659485106[8] = delta_x[8] + nom_x[8];
   out_2728703337659485106[9] = delta_x[9] + nom_x[9];
   out_2728703337659485106[10] = delta_x[10] + nom_x[10];
   out_2728703337659485106[11] = delta_x[11] + nom_x[11];
   out_2728703337659485106[12] = delta_x[12] + nom_x[12];
   out_2728703337659485106[13] = delta_x[13] + nom_x[13];
   out_2728703337659485106[14] = delta_x[14] + nom_x[14];
   out_2728703337659485106[15] = delta_x[15] + nom_x[15];
   out_2728703337659485106[16] = delta_x[16] + nom_x[16];
   out_2728703337659485106[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4933784707852487941) {
   out_4933784707852487941[0] = -nom_x[0] + true_x[0];
   out_4933784707852487941[1] = -nom_x[1] + true_x[1];
   out_4933784707852487941[2] = -nom_x[2] + true_x[2];
   out_4933784707852487941[3] = -nom_x[3] + true_x[3];
   out_4933784707852487941[4] = -nom_x[4] + true_x[4];
   out_4933784707852487941[5] = -nom_x[5] + true_x[5];
   out_4933784707852487941[6] = -nom_x[6] + true_x[6];
   out_4933784707852487941[7] = -nom_x[7] + true_x[7];
   out_4933784707852487941[8] = -nom_x[8] + true_x[8];
   out_4933784707852487941[9] = -nom_x[9] + true_x[9];
   out_4933784707852487941[10] = -nom_x[10] + true_x[10];
   out_4933784707852487941[11] = -nom_x[11] + true_x[11];
   out_4933784707852487941[12] = -nom_x[12] + true_x[12];
   out_4933784707852487941[13] = -nom_x[13] + true_x[13];
   out_4933784707852487941[14] = -nom_x[14] + true_x[14];
   out_4933784707852487941[15] = -nom_x[15] + true_x[15];
   out_4933784707852487941[16] = -nom_x[16] + true_x[16];
   out_4933784707852487941[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4112937202201059041) {
   out_4112937202201059041[0] = 1.0;
   out_4112937202201059041[1] = 0.0;
   out_4112937202201059041[2] = 0.0;
   out_4112937202201059041[3] = 0.0;
   out_4112937202201059041[4] = 0.0;
   out_4112937202201059041[5] = 0.0;
   out_4112937202201059041[6] = 0.0;
   out_4112937202201059041[7] = 0.0;
   out_4112937202201059041[8] = 0.0;
   out_4112937202201059041[9] = 0.0;
   out_4112937202201059041[10] = 0.0;
   out_4112937202201059041[11] = 0.0;
   out_4112937202201059041[12] = 0.0;
   out_4112937202201059041[13] = 0.0;
   out_4112937202201059041[14] = 0.0;
   out_4112937202201059041[15] = 0.0;
   out_4112937202201059041[16] = 0.0;
   out_4112937202201059041[17] = 0.0;
   out_4112937202201059041[18] = 0.0;
   out_4112937202201059041[19] = 1.0;
   out_4112937202201059041[20] = 0.0;
   out_4112937202201059041[21] = 0.0;
   out_4112937202201059041[22] = 0.0;
   out_4112937202201059041[23] = 0.0;
   out_4112937202201059041[24] = 0.0;
   out_4112937202201059041[25] = 0.0;
   out_4112937202201059041[26] = 0.0;
   out_4112937202201059041[27] = 0.0;
   out_4112937202201059041[28] = 0.0;
   out_4112937202201059041[29] = 0.0;
   out_4112937202201059041[30] = 0.0;
   out_4112937202201059041[31] = 0.0;
   out_4112937202201059041[32] = 0.0;
   out_4112937202201059041[33] = 0.0;
   out_4112937202201059041[34] = 0.0;
   out_4112937202201059041[35] = 0.0;
   out_4112937202201059041[36] = 0.0;
   out_4112937202201059041[37] = 0.0;
   out_4112937202201059041[38] = 1.0;
   out_4112937202201059041[39] = 0.0;
   out_4112937202201059041[40] = 0.0;
   out_4112937202201059041[41] = 0.0;
   out_4112937202201059041[42] = 0.0;
   out_4112937202201059041[43] = 0.0;
   out_4112937202201059041[44] = 0.0;
   out_4112937202201059041[45] = 0.0;
   out_4112937202201059041[46] = 0.0;
   out_4112937202201059041[47] = 0.0;
   out_4112937202201059041[48] = 0.0;
   out_4112937202201059041[49] = 0.0;
   out_4112937202201059041[50] = 0.0;
   out_4112937202201059041[51] = 0.0;
   out_4112937202201059041[52] = 0.0;
   out_4112937202201059041[53] = 0.0;
   out_4112937202201059041[54] = 0.0;
   out_4112937202201059041[55] = 0.0;
   out_4112937202201059041[56] = 0.0;
   out_4112937202201059041[57] = 1.0;
   out_4112937202201059041[58] = 0.0;
   out_4112937202201059041[59] = 0.0;
   out_4112937202201059041[60] = 0.0;
   out_4112937202201059041[61] = 0.0;
   out_4112937202201059041[62] = 0.0;
   out_4112937202201059041[63] = 0.0;
   out_4112937202201059041[64] = 0.0;
   out_4112937202201059041[65] = 0.0;
   out_4112937202201059041[66] = 0.0;
   out_4112937202201059041[67] = 0.0;
   out_4112937202201059041[68] = 0.0;
   out_4112937202201059041[69] = 0.0;
   out_4112937202201059041[70] = 0.0;
   out_4112937202201059041[71] = 0.0;
   out_4112937202201059041[72] = 0.0;
   out_4112937202201059041[73] = 0.0;
   out_4112937202201059041[74] = 0.0;
   out_4112937202201059041[75] = 0.0;
   out_4112937202201059041[76] = 1.0;
   out_4112937202201059041[77] = 0.0;
   out_4112937202201059041[78] = 0.0;
   out_4112937202201059041[79] = 0.0;
   out_4112937202201059041[80] = 0.0;
   out_4112937202201059041[81] = 0.0;
   out_4112937202201059041[82] = 0.0;
   out_4112937202201059041[83] = 0.0;
   out_4112937202201059041[84] = 0.0;
   out_4112937202201059041[85] = 0.0;
   out_4112937202201059041[86] = 0.0;
   out_4112937202201059041[87] = 0.0;
   out_4112937202201059041[88] = 0.0;
   out_4112937202201059041[89] = 0.0;
   out_4112937202201059041[90] = 0.0;
   out_4112937202201059041[91] = 0.0;
   out_4112937202201059041[92] = 0.0;
   out_4112937202201059041[93] = 0.0;
   out_4112937202201059041[94] = 0.0;
   out_4112937202201059041[95] = 1.0;
   out_4112937202201059041[96] = 0.0;
   out_4112937202201059041[97] = 0.0;
   out_4112937202201059041[98] = 0.0;
   out_4112937202201059041[99] = 0.0;
   out_4112937202201059041[100] = 0.0;
   out_4112937202201059041[101] = 0.0;
   out_4112937202201059041[102] = 0.0;
   out_4112937202201059041[103] = 0.0;
   out_4112937202201059041[104] = 0.0;
   out_4112937202201059041[105] = 0.0;
   out_4112937202201059041[106] = 0.0;
   out_4112937202201059041[107] = 0.0;
   out_4112937202201059041[108] = 0.0;
   out_4112937202201059041[109] = 0.0;
   out_4112937202201059041[110] = 0.0;
   out_4112937202201059041[111] = 0.0;
   out_4112937202201059041[112] = 0.0;
   out_4112937202201059041[113] = 0.0;
   out_4112937202201059041[114] = 1.0;
   out_4112937202201059041[115] = 0.0;
   out_4112937202201059041[116] = 0.0;
   out_4112937202201059041[117] = 0.0;
   out_4112937202201059041[118] = 0.0;
   out_4112937202201059041[119] = 0.0;
   out_4112937202201059041[120] = 0.0;
   out_4112937202201059041[121] = 0.0;
   out_4112937202201059041[122] = 0.0;
   out_4112937202201059041[123] = 0.0;
   out_4112937202201059041[124] = 0.0;
   out_4112937202201059041[125] = 0.0;
   out_4112937202201059041[126] = 0.0;
   out_4112937202201059041[127] = 0.0;
   out_4112937202201059041[128] = 0.0;
   out_4112937202201059041[129] = 0.0;
   out_4112937202201059041[130] = 0.0;
   out_4112937202201059041[131] = 0.0;
   out_4112937202201059041[132] = 0.0;
   out_4112937202201059041[133] = 1.0;
   out_4112937202201059041[134] = 0.0;
   out_4112937202201059041[135] = 0.0;
   out_4112937202201059041[136] = 0.0;
   out_4112937202201059041[137] = 0.0;
   out_4112937202201059041[138] = 0.0;
   out_4112937202201059041[139] = 0.0;
   out_4112937202201059041[140] = 0.0;
   out_4112937202201059041[141] = 0.0;
   out_4112937202201059041[142] = 0.0;
   out_4112937202201059041[143] = 0.0;
   out_4112937202201059041[144] = 0.0;
   out_4112937202201059041[145] = 0.0;
   out_4112937202201059041[146] = 0.0;
   out_4112937202201059041[147] = 0.0;
   out_4112937202201059041[148] = 0.0;
   out_4112937202201059041[149] = 0.0;
   out_4112937202201059041[150] = 0.0;
   out_4112937202201059041[151] = 0.0;
   out_4112937202201059041[152] = 1.0;
   out_4112937202201059041[153] = 0.0;
   out_4112937202201059041[154] = 0.0;
   out_4112937202201059041[155] = 0.0;
   out_4112937202201059041[156] = 0.0;
   out_4112937202201059041[157] = 0.0;
   out_4112937202201059041[158] = 0.0;
   out_4112937202201059041[159] = 0.0;
   out_4112937202201059041[160] = 0.0;
   out_4112937202201059041[161] = 0.0;
   out_4112937202201059041[162] = 0.0;
   out_4112937202201059041[163] = 0.0;
   out_4112937202201059041[164] = 0.0;
   out_4112937202201059041[165] = 0.0;
   out_4112937202201059041[166] = 0.0;
   out_4112937202201059041[167] = 0.0;
   out_4112937202201059041[168] = 0.0;
   out_4112937202201059041[169] = 0.0;
   out_4112937202201059041[170] = 0.0;
   out_4112937202201059041[171] = 1.0;
   out_4112937202201059041[172] = 0.0;
   out_4112937202201059041[173] = 0.0;
   out_4112937202201059041[174] = 0.0;
   out_4112937202201059041[175] = 0.0;
   out_4112937202201059041[176] = 0.0;
   out_4112937202201059041[177] = 0.0;
   out_4112937202201059041[178] = 0.0;
   out_4112937202201059041[179] = 0.0;
   out_4112937202201059041[180] = 0.0;
   out_4112937202201059041[181] = 0.0;
   out_4112937202201059041[182] = 0.0;
   out_4112937202201059041[183] = 0.0;
   out_4112937202201059041[184] = 0.0;
   out_4112937202201059041[185] = 0.0;
   out_4112937202201059041[186] = 0.0;
   out_4112937202201059041[187] = 0.0;
   out_4112937202201059041[188] = 0.0;
   out_4112937202201059041[189] = 0.0;
   out_4112937202201059041[190] = 1.0;
   out_4112937202201059041[191] = 0.0;
   out_4112937202201059041[192] = 0.0;
   out_4112937202201059041[193] = 0.0;
   out_4112937202201059041[194] = 0.0;
   out_4112937202201059041[195] = 0.0;
   out_4112937202201059041[196] = 0.0;
   out_4112937202201059041[197] = 0.0;
   out_4112937202201059041[198] = 0.0;
   out_4112937202201059041[199] = 0.0;
   out_4112937202201059041[200] = 0.0;
   out_4112937202201059041[201] = 0.0;
   out_4112937202201059041[202] = 0.0;
   out_4112937202201059041[203] = 0.0;
   out_4112937202201059041[204] = 0.0;
   out_4112937202201059041[205] = 0.0;
   out_4112937202201059041[206] = 0.0;
   out_4112937202201059041[207] = 0.0;
   out_4112937202201059041[208] = 0.0;
   out_4112937202201059041[209] = 1.0;
   out_4112937202201059041[210] = 0.0;
   out_4112937202201059041[211] = 0.0;
   out_4112937202201059041[212] = 0.0;
   out_4112937202201059041[213] = 0.0;
   out_4112937202201059041[214] = 0.0;
   out_4112937202201059041[215] = 0.0;
   out_4112937202201059041[216] = 0.0;
   out_4112937202201059041[217] = 0.0;
   out_4112937202201059041[218] = 0.0;
   out_4112937202201059041[219] = 0.0;
   out_4112937202201059041[220] = 0.0;
   out_4112937202201059041[221] = 0.0;
   out_4112937202201059041[222] = 0.0;
   out_4112937202201059041[223] = 0.0;
   out_4112937202201059041[224] = 0.0;
   out_4112937202201059041[225] = 0.0;
   out_4112937202201059041[226] = 0.0;
   out_4112937202201059041[227] = 0.0;
   out_4112937202201059041[228] = 1.0;
   out_4112937202201059041[229] = 0.0;
   out_4112937202201059041[230] = 0.0;
   out_4112937202201059041[231] = 0.0;
   out_4112937202201059041[232] = 0.0;
   out_4112937202201059041[233] = 0.0;
   out_4112937202201059041[234] = 0.0;
   out_4112937202201059041[235] = 0.0;
   out_4112937202201059041[236] = 0.0;
   out_4112937202201059041[237] = 0.0;
   out_4112937202201059041[238] = 0.0;
   out_4112937202201059041[239] = 0.0;
   out_4112937202201059041[240] = 0.0;
   out_4112937202201059041[241] = 0.0;
   out_4112937202201059041[242] = 0.0;
   out_4112937202201059041[243] = 0.0;
   out_4112937202201059041[244] = 0.0;
   out_4112937202201059041[245] = 0.0;
   out_4112937202201059041[246] = 0.0;
   out_4112937202201059041[247] = 1.0;
   out_4112937202201059041[248] = 0.0;
   out_4112937202201059041[249] = 0.0;
   out_4112937202201059041[250] = 0.0;
   out_4112937202201059041[251] = 0.0;
   out_4112937202201059041[252] = 0.0;
   out_4112937202201059041[253] = 0.0;
   out_4112937202201059041[254] = 0.0;
   out_4112937202201059041[255] = 0.0;
   out_4112937202201059041[256] = 0.0;
   out_4112937202201059041[257] = 0.0;
   out_4112937202201059041[258] = 0.0;
   out_4112937202201059041[259] = 0.0;
   out_4112937202201059041[260] = 0.0;
   out_4112937202201059041[261] = 0.0;
   out_4112937202201059041[262] = 0.0;
   out_4112937202201059041[263] = 0.0;
   out_4112937202201059041[264] = 0.0;
   out_4112937202201059041[265] = 0.0;
   out_4112937202201059041[266] = 1.0;
   out_4112937202201059041[267] = 0.0;
   out_4112937202201059041[268] = 0.0;
   out_4112937202201059041[269] = 0.0;
   out_4112937202201059041[270] = 0.0;
   out_4112937202201059041[271] = 0.0;
   out_4112937202201059041[272] = 0.0;
   out_4112937202201059041[273] = 0.0;
   out_4112937202201059041[274] = 0.0;
   out_4112937202201059041[275] = 0.0;
   out_4112937202201059041[276] = 0.0;
   out_4112937202201059041[277] = 0.0;
   out_4112937202201059041[278] = 0.0;
   out_4112937202201059041[279] = 0.0;
   out_4112937202201059041[280] = 0.0;
   out_4112937202201059041[281] = 0.0;
   out_4112937202201059041[282] = 0.0;
   out_4112937202201059041[283] = 0.0;
   out_4112937202201059041[284] = 0.0;
   out_4112937202201059041[285] = 1.0;
   out_4112937202201059041[286] = 0.0;
   out_4112937202201059041[287] = 0.0;
   out_4112937202201059041[288] = 0.0;
   out_4112937202201059041[289] = 0.0;
   out_4112937202201059041[290] = 0.0;
   out_4112937202201059041[291] = 0.0;
   out_4112937202201059041[292] = 0.0;
   out_4112937202201059041[293] = 0.0;
   out_4112937202201059041[294] = 0.0;
   out_4112937202201059041[295] = 0.0;
   out_4112937202201059041[296] = 0.0;
   out_4112937202201059041[297] = 0.0;
   out_4112937202201059041[298] = 0.0;
   out_4112937202201059041[299] = 0.0;
   out_4112937202201059041[300] = 0.0;
   out_4112937202201059041[301] = 0.0;
   out_4112937202201059041[302] = 0.0;
   out_4112937202201059041[303] = 0.0;
   out_4112937202201059041[304] = 1.0;
   out_4112937202201059041[305] = 0.0;
   out_4112937202201059041[306] = 0.0;
   out_4112937202201059041[307] = 0.0;
   out_4112937202201059041[308] = 0.0;
   out_4112937202201059041[309] = 0.0;
   out_4112937202201059041[310] = 0.0;
   out_4112937202201059041[311] = 0.0;
   out_4112937202201059041[312] = 0.0;
   out_4112937202201059041[313] = 0.0;
   out_4112937202201059041[314] = 0.0;
   out_4112937202201059041[315] = 0.0;
   out_4112937202201059041[316] = 0.0;
   out_4112937202201059041[317] = 0.0;
   out_4112937202201059041[318] = 0.0;
   out_4112937202201059041[319] = 0.0;
   out_4112937202201059041[320] = 0.0;
   out_4112937202201059041[321] = 0.0;
   out_4112937202201059041[322] = 0.0;
   out_4112937202201059041[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_41468171679069375) {
   out_41468171679069375[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_41468171679069375[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_41468171679069375[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_41468171679069375[3] = dt*state[12] + state[3];
   out_41468171679069375[4] = dt*state[13] + state[4];
   out_41468171679069375[5] = dt*state[14] + state[5];
   out_41468171679069375[6] = state[6];
   out_41468171679069375[7] = state[7];
   out_41468171679069375[8] = state[8];
   out_41468171679069375[9] = state[9];
   out_41468171679069375[10] = state[10];
   out_41468171679069375[11] = state[11];
   out_41468171679069375[12] = state[12];
   out_41468171679069375[13] = state[13];
   out_41468171679069375[14] = state[14];
   out_41468171679069375[15] = state[15];
   out_41468171679069375[16] = state[16];
   out_41468171679069375[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7128628514967391957) {
   out_7128628514967391957[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7128628514967391957[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7128628514967391957[2] = 0;
   out_7128628514967391957[3] = 0;
   out_7128628514967391957[4] = 0;
   out_7128628514967391957[5] = 0;
   out_7128628514967391957[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7128628514967391957[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7128628514967391957[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7128628514967391957[9] = 0;
   out_7128628514967391957[10] = 0;
   out_7128628514967391957[11] = 0;
   out_7128628514967391957[12] = 0;
   out_7128628514967391957[13] = 0;
   out_7128628514967391957[14] = 0;
   out_7128628514967391957[15] = 0;
   out_7128628514967391957[16] = 0;
   out_7128628514967391957[17] = 0;
   out_7128628514967391957[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7128628514967391957[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7128628514967391957[20] = 0;
   out_7128628514967391957[21] = 0;
   out_7128628514967391957[22] = 0;
   out_7128628514967391957[23] = 0;
   out_7128628514967391957[24] = 0;
   out_7128628514967391957[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7128628514967391957[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7128628514967391957[27] = 0;
   out_7128628514967391957[28] = 0;
   out_7128628514967391957[29] = 0;
   out_7128628514967391957[30] = 0;
   out_7128628514967391957[31] = 0;
   out_7128628514967391957[32] = 0;
   out_7128628514967391957[33] = 0;
   out_7128628514967391957[34] = 0;
   out_7128628514967391957[35] = 0;
   out_7128628514967391957[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7128628514967391957[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7128628514967391957[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7128628514967391957[39] = 0;
   out_7128628514967391957[40] = 0;
   out_7128628514967391957[41] = 0;
   out_7128628514967391957[42] = 0;
   out_7128628514967391957[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7128628514967391957[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7128628514967391957[45] = 0;
   out_7128628514967391957[46] = 0;
   out_7128628514967391957[47] = 0;
   out_7128628514967391957[48] = 0;
   out_7128628514967391957[49] = 0;
   out_7128628514967391957[50] = 0;
   out_7128628514967391957[51] = 0;
   out_7128628514967391957[52] = 0;
   out_7128628514967391957[53] = 0;
   out_7128628514967391957[54] = 0;
   out_7128628514967391957[55] = 0;
   out_7128628514967391957[56] = 0;
   out_7128628514967391957[57] = 1;
   out_7128628514967391957[58] = 0;
   out_7128628514967391957[59] = 0;
   out_7128628514967391957[60] = 0;
   out_7128628514967391957[61] = 0;
   out_7128628514967391957[62] = 0;
   out_7128628514967391957[63] = 0;
   out_7128628514967391957[64] = 0;
   out_7128628514967391957[65] = 0;
   out_7128628514967391957[66] = dt;
   out_7128628514967391957[67] = 0;
   out_7128628514967391957[68] = 0;
   out_7128628514967391957[69] = 0;
   out_7128628514967391957[70] = 0;
   out_7128628514967391957[71] = 0;
   out_7128628514967391957[72] = 0;
   out_7128628514967391957[73] = 0;
   out_7128628514967391957[74] = 0;
   out_7128628514967391957[75] = 0;
   out_7128628514967391957[76] = 1;
   out_7128628514967391957[77] = 0;
   out_7128628514967391957[78] = 0;
   out_7128628514967391957[79] = 0;
   out_7128628514967391957[80] = 0;
   out_7128628514967391957[81] = 0;
   out_7128628514967391957[82] = 0;
   out_7128628514967391957[83] = 0;
   out_7128628514967391957[84] = 0;
   out_7128628514967391957[85] = dt;
   out_7128628514967391957[86] = 0;
   out_7128628514967391957[87] = 0;
   out_7128628514967391957[88] = 0;
   out_7128628514967391957[89] = 0;
   out_7128628514967391957[90] = 0;
   out_7128628514967391957[91] = 0;
   out_7128628514967391957[92] = 0;
   out_7128628514967391957[93] = 0;
   out_7128628514967391957[94] = 0;
   out_7128628514967391957[95] = 1;
   out_7128628514967391957[96] = 0;
   out_7128628514967391957[97] = 0;
   out_7128628514967391957[98] = 0;
   out_7128628514967391957[99] = 0;
   out_7128628514967391957[100] = 0;
   out_7128628514967391957[101] = 0;
   out_7128628514967391957[102] = 0;
   out_7128628514967391957[103] = 0;
   out_7128628514967391957[104] = dt;
   out_7128628514967391957[105] = 0;
   out_7128628514967391957[106] = 0;
   out_7128628514967391957[107] = 0;
   out_7128628514967391957[108] = 0;
   out_7128628514967391957[109] = 0;
   out_7128628514967391957[110] = 0;
   out_7128628514967391957[111] = 0;
   out_7128628514967391957[112] = 0;
   out_7128628514967391957[113] = 0;
   out_7128628514967391957[114] = 1;
   out_7128628514967391957[115] = 0;
   out_7128628514967391957[116] = 0;
   out_7128628514967391957[117] = 0;
   out_7128628514967391957[118] = 0;
   out_7128628514967391957[119] = 0;
   out_7128628514967391957[120] = 0;
   out_7128628514967391957[121] = 0;
   out_7128628514967391957[122] = 0;
   out_7128628514967391957[123] = 0;
   out_7128628514967391957[124] = 0;
   out_7128628514967391957[125] = 0;
   out_7128628514967391957[126] = 0;
   out_7128628514967391957[127] = 0;
   out_7128628514967391957[128] = 0;
   out_7128628514967391957[129] = 0;
   out_7128628514967391957[130] = 0;
   out_7128628514967391957[131] = 0;
   out_7128628514967391957[132] = 0;
   out_7128628514967391957[133] = 1;
   out_7128628514967391957[134] = 0;
   out_7128628514967391957[135] = 0;
   out_7128628514967391957[136] = 0;
   out_7128628514967391957[137] = 0;
   out_7128628514967391957[138] = 0;
   out_7128628514967391957[139] = 0;
   out_7128628514967391957[140] = 0;
   out_7128628514967391957[141] = 0;
   out_7128628514967391957[142] = 0;
   out_7128628514967391957[143] = 0;
   out_7128628514967391957[144] = 0;
   out_7128628514967391957[145] = 0;
   out_7128628514967391957[146] = 0;
   out_7128628514967391957[147] = 0;
   out_7128628514967391957[148] = 0;
   out_7128628514967391957[149] = 0;
   out_7128628514967391957[150] = 0;
   out_7128628514967391957[151] = 0;
   out_7128628514967391957[152] = 1;
   out_7128628514967391957[153] = 0;
   out_7128628514967391957[154] = 0;
   out_7128628514967391957[155] = 0;
   out_7128628514967391957[156] = 0;
   out_7128628514967391957[157] = 0;
   out_7128628514967391957[158] = 0;
   out_7128628514967391957[159] = 0;
   out_7128628514967391957[160] = 0;
   out_7128628514967391957[161] = 0;
   out_7128628514967391957[162] = 0;
   out_7128628514967391957[163] = 0;
   out_7128628514967391957[164] = 0;
   out_7128628514967391957[165] = 0;
   out_7128628514967391957[166] = 0;
   out_7128628514967391957[167] = 0;
   out_7128628514967391957[168] = 0;
   out_7128628514967391957[169] = 0;
   out_7128628514967391957[170] = 0;
   out_7128628514967391957[171] = 1;
   out_7128628514967391957[172] = 0;
   out_7128628514967391957[173] = 0;
   out_7128628514967391957[174] = 0;
   out_7128628514967391957[175] = 0;
   out_7128628514967391957[176] = 0;
   out_7128628514967391957[177] = 0;
   out_7128628514967391957[178] = 0;
   out_7128628514967391957[179] = 0;
   out_7128628514967391957[180] = 0;
   out_7128628514967391957[181] = 0;
   out_7128628514967391957[182] = 0;
   out_7128628514967391957[183] = 0;
   out_7128628514967391957[184] = 0;
   out_7128628514967391957[185] = 0;
   out_7128628514967391957[186] = 0;
   out_7128628514967391957[187] = 0;
   out_7128628514967391957[188] = 0;
   out_7128628514967391957[189] = 0;
   out_7128628514967391957[190] = 1;
   out_7128628514967391957[191] = 0;
   out_7128628514967391957[192] = 0;
   out_7128628514967391957[193] = 0;
   out_7128628514967391957[194] = 0;
   out_7128628514967391957[195] = 0;
   out_7128628514967391957[196] = 0;
   out_7128628514967391957[197] = 0;
   out_7128628514967391957[198] = 0;
   out_7128628514967391957[199] = 0;
   out_7128628514967391957[200] = 0;
   out_7128628514967391957[201] = 0;
   out_7128628514967391957[202] = 0;
   out_7128628514967391957[203] = 0;
   out_7128628514967391957[204] = 0;
   out_7128628514967391957[205] = 0;
   out_7128628514967391957[206] = 0;
   out_7128628514967391957[207] = 0;
   out_7128628514967391957[208] = 0;
   out_7128628514967391957[209] = 1;
   out_7128628514967391957[210] = 0;
   out_7128628514967391957[211] = 0;
   out_7128628514967391957[212] = 0;
   out_7128628514967391957[213] = 0;
   out_7128628514967391957[214] = 0;
   out_7128628514967391957[215] = 0;
   out_7128628514967391957[216] = 0;
   out_7128628514967391957[217] = 0;
   out_7128628514967391957[218] = 0;
   out_7128628514967391957[219] = 0;
   out_7128628514967391957[220] = 0;
   out_7128628514967391957[221] = 0;
   out_7128628514967391957[222] = 0;
   out_7128628514967391957[223] = 0;
   out_7128628514967391957[224] = 0;
   out_7128628514967391957[225] = 0;
   out_7128628514967391957[226] = 0;
   out_7128628514967391957[227] = 0;
   out_7128628514967391957[228] = 1;
   out_7128628514967391957[229] = 0;
   out_7128628514967391957[230] = 0;
   out_7128628514967391957[231] = 0;
   out_7128628514967391957[232] = 0;
   out_7128628514967391957[233] = 0;
   out_7128628514967391957[234] = 0;
   out_7128628514967391957[235] = 0;
   out_7128628514967391957[236] = 0;
   out_7128628514967391957[237] = 0;
   out_7128628514967391957[238] = 0;
   out_7128628514967391957[239] = 0;
   out_7128628514967391957[240] = 0;
   out_7128628514967391957[241] = 0;
   out_7128628514967391957[242] = 0;
   out_7128628514967391957[243] = 0;
   out_7128628514967391957[244] = 0;
   out_7128628514967391957[245] = 0;
   out_7128628514967391957[246] = 0;
   out_7128628514967391957[247] = 1;
   out_7128628514967391957[248] = 0;
   out_7128628514967391957[249] = 0;
   out_7128628514967391957[250] = 0;
   out_7128628514967391957[251] = 0;
   out_7128628514967391957[252] = 0;
   out_7128628514967391957[253] = 0;
   out_7128628514967391957[254] = 0;
   out_7128628514967391957[255] = 0;
   out_7128628514967391957[256] = 0;
   out_7128628514967391957[257] = 0;
   out_7128628514967391957[258] = 0;
   out_7128628514967391957[259] = 0;
   out_7128628514967391957[260] = 0;
   out_7128628514967391957[261] = 0;
   out_7128628514967391957[262] = 0;
   out_7128628514967391957[263] = 0;
   out_7128628514967391957[264] = 0;
   out_7128628514967391957[265] = 0;
   out_7128628514967391957[266] = 1;
   out_7128628514967391957[267] = 0;
   out_7128628514967391957[268] = 0;
   out_7128628514967391957[269] = 0;
   out_7128628514967391957[270] = 0;
   out_7128628514967391957[271] = 0;
   out_7128628514967391957[272] = 0;
   out_7128628514967391957[273] = 0;
   out_7128628514967391957[274] = 0;
   out_7128628514967391957[275] = 0;
   out_7128628514967391957[276] = 0;
   out_7128628514967391957[277] = 0;
   out_7128628514967391957[278] = 0;
   out_7128628514967391957[279] = 0;
   out_7128628514967391957[280] = 0;
   out_7128628514967391957[281] = 0;
   out_7128628514967391957[282] = 0;
   out_7128628514967391957[283] = 0;
   out_7128628514967391957[284] = 0;
   out_7128628514967391957[285] = 1;
   out_7128628514967391957[286] = 0;
   out_7128628514967391957[287] = 0;
   out_7128628514967391957[288] = 0;
   out_7128628514967391957[289] = 0;
   out_7128628514967391957[290] = 0;
   out_7128628514967391957[291] = 0;
   out_7128628514967391957[292] = 0;
   out_7128628514967391957[293] = 0;
   out_7128628514967391957[294] = 0;
   out_7128628514967391957[295] = 0;
   out_7128628514967391957[296] = 0;
   out_7128628514967391957[297] = 0;
   out_7128628514967391957[298] = 0;
   out_7128628514967391957[299] = 0;
   out_7128628514967391957[300] = 0;
   out_7128628514967391957[301] = 0;
   out_7128628514967391957[302] = 0;
   out_7128628514967391957[303] = 0;
   out_7128628514967391957[304] = 1;
   out_7128628514967391957[305] = 0;
   out_7128628514967391957[306] = 0;
   out_7128628514967391957[307] = 0;
   out_7128628514967391957[308] = 0;
   out_7128628514967391957[309] = 0;
   out_7128628514967391957[310] = 0;
   out_7128628514967391957[311] = 0;
   out_7128628514967391957[312] = 0;
   out_7128628514967391957[313] = 0;
   out_7128628514967391957[314] = 0;
   out_7128628514967391957[315] = 0;
   out_7128628514967391957[316] = 0;
   out_7128628514967391957[317] = 0;
   out_7128628514967391957[318] = 0;
   out_7128628514967391957[319] = 0;
   out_7128628514967391957[320] = 0;
   out_7128628514967391957[321] = 0;
   out_7128628514967391957[322] = 0;
   out_7128628514967391957[323] = 1;
}
void h_4(double *state, double *unused, double *out_8965394066110212061) {
   out_8965394066110212061[0] = state[6] + state[9];
   out_8965394066110212061[1] = state[7] + state[10];
   out_8965394066110212061[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7405284191817771769) {
   out_7405284191817771769[0] = 0;
   out_7405284191817771769[1] = 0;
   out_7405284191817771769[2] = 0;
   out_7405284191817771769[3] = 0;
   out_7405284191817771769[4] = 0;
   out_7405284191817771769[5] = 0;
   out_7405284191817771769[6] = 1;
   out_7405284191817771769[7] = 0;
   out_7405284191817771769[8] = 0;
   out_7405284191817771769[9] = 1;
   out_7405284191817771769[10] = 0;
   out_7405284191817771769[11] = 0;
   out_7405284191817771769[12] = 0;
   out_7405284191817771769[13] = 0;
   out_7405284191817771769[14] = 0;
   out_7405284191817771769[15] = 0;
   out_7405284191817771769[16] = 0;
   out_7405284191817771769[17] = 0;
   out_7405284191817771769[18] = 0;
   out_7405284191817771769[19] = 0;
   out_7405284191817771769[20] = 0;
   out_7405284191817771769[21] = 0;
   out_7405284191817771769[22] = 0;
   out_7405284191817771769[23] = 0;
   out_7405284191817771769[24] = 0;
   out_7405284191817771769[25] = 1;
   out_7405284191817771769[26] = 0;
   out_7405284191817771769[27] = 0;
   out_7405284191817771769[28] = 1;
   out_7405284191817771769[29] = 0;
   out_7405284191817771769[30] = 0;
   out_7405284191817771769[31] = 0;
   out_7405284191817771769[32] = 0;
   out_7405284191817771769[33] = 0;
   out_7405284191817771769[34] = 0;
   out_7405284191817771769[35] = 0;
   out_7405284191817771769[36] = 0;
   out_7405284191817771769[37] = 0;
   out_7405284191817771769[38] = 0;
   out_7405284191817771769[39] = 0;
   out_7405284191817771769[40] = 0;
   out_7405284191817771769[41] = 0;
   out_7405284191817771769[42] = 0;
   out_7405284191817771769[43] = 0;
   out_7405284191817771769[44] = 1;
   out_7405284191817771769[45] = 0;
   out_7405284191817771769[46] = 0;
   out_7405284191817771769[47] = 1;
   out_7405284191817771769[48] = 0;
   out_7405284191817771769[49] = 0;
   out_7405284191817771769[50] = 0;
   out_7405284191817771769[51] = 0;
   out_7405284191817771769[52] = 0;
   out_7405284191817771769[53] = 0;
}
void h_10(double *state, double *unused, double *out_4429682976893391883) {
   out_4429682976893391883[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4429682976893391883[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4429682976893391883[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3580593939681347040) {
   out_3580593939681347040[0] = 0;
   out_3580593939681347040[1] = 9.8100000000000005*cos(state[1]);
   out_3580593939681347040[2] = 0;
   out_3580593939681347040[3] = 0;
   out_3580593939681347040[4] = -state[8];
   out_3580593939681347040[5] = state[7];
   out_3580593939681347040[6] = 0;
   out_3580593939681347040[7] = state[5];
   out_3580593939681347040[8] = -state[4];
   out_3580593939681347040[9] = 0;
   out_3580593939681347040[10] = 0;
   out_3580593939681347040[11] = 0;
   out_3580593939681347040[12] = 1;
   out_3580593939681347040[13] = 0;
   out_3580593939681347040[14] = 0;
   out_3580593939681347040[15] = 1;
   out_3580593939681347040[16] = 0;
   out_3580593939681347040[17] = 0;
   out_3580593939681347040[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3580593939681347040[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3580593939681347040[20] = 0;
   out_3580593939681347040[21] = state[8];
   out_3580593939681347040[22] = 0;
   out_3580593939681347040[23] = -state[6];
   out_3580593939681347040[24] = -state[5];
   out_3580593939681347040[25] = 0;
   out_3580593939681347040[26] = state[3];
   out_3580593939681347040[27] = 0;
   out_3580593939681347040[28] = 0;
   out_3580593939681347040[29] = 0;
   out_3580593939681347040[30] = 0;
   out_3580593939681347040[31] = 1;
   out_3580593939681347040[32] = 0;
   out_3580593939681347040[33] = 0;
   out_3580593939681347040[34] = 1;
   out_3580593939681347040[35] = 0;
   out_3580593939681347040[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3580593939681347040[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3580593939681347040[38] = 0;
   out_3580593939681347040[39] = -state[7];
   out_3580593939681347040[40] = state[6];
   out_3580593939681347040[41] = 0;
   out_3580593939681347040[42] = state[4];
   out_3580593939681347040[43] = -state[3];
   out_3580593939681347040[44] = 0;
   out_3580593939681347040[45] = 0;
   out_3580593939681347040[46] = 0;
   out_3580593939681347040[47] = 0;
   out_3580593939681347040[48] = 0;
   out_3580593939681347040[49] = 0;
   out_3580593939681347040[50] = 1;
   out_3580593939681347040[51] = 0;
   out_3580593939681347040[52] = 0;
   out_3580593939681347040[53] = 1;
}
void h_13(double *state, double *unused, double *out_9139916048338221099) {
   out_9139916048338221099[0] = state[3];
   out_9139916048338221099[1] = state[4];
   out_9139916048338221099[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7207704418589255823) {
   out_7207704418589255823[0] = 0;
   out_7207704418589255823[1] = 0;
   out_7207704418589255823[2] = 0;
   out_7207704418589255823[3] = 1;
   out_7207704418589255823[4] = 0;
   out_7207704418589255823[5] = 0;
   out_7207704418589255823[6] = 0;
   out_7207704418589255823[7] = 0;
   out_7207704418589255823[8] = 0;
   out_7207704418589255823[9] = 0;
   out_7207704418589255823[10] = 0;
   out_7207704418589255823[11] = 0;
   out_7207704418589255823[12] = 0;
   out_7207704418589255823[13] = 0;
   out_7207704418589255823[14] = 0;
   out_7207704418589255823[15] = 0;
   out_7207704418589255823[16] = 0;
   out_7207704418589255823[17] = 0;
   out_7207704418589255823[18] = 0;
   out_7207704418589255823[19] = 0;
   out_7207704418589255823[20] = 0;
   out_7207704418589255823[21] = 0;
   out_7207704418589255823[22] = 1;
   out_7207704418589255823[23] = 0;
   out_7207704418589255823[24] = 0;
   out_7207704418589255823[25] = 0;
   out_7207704418589255823[26] = 0;
   out_7207704418589255823[27] = 0;
   out_7207704418589255823[28] = 0;
   out_7207704418589255823[29] = 0;
   out_7207704418589255823[30] = 0;
   out_7207704418589255823[31] = 0;
   out_7207704418589255823[32] = 0;
   out_7207704418589255823[33] = 0;
   out_7207704418589255823[34] = 0;
   out_7207704418589255823[35] = 0;
   out_7207704418589255823[36] = 0;
   out_7207704418589255823[37] = 0;
   out_7207704418589255823[38] = 0;
   out_7207704418589255823[39] = 0;
   out_7207704418589255823[40] = 0;
   out_7207704418589255823[41] = 1;
   out_7207704418589255823[42] = 0;
   out_7207704418589255823[43] = 0;
   out_7207704418589255823[44] = 0;
   out_7207704418589255823[45] = 0;
   out_7207704418589255823[46] = 0;
   out_7207704418589255823[47] = 0;
   out_7207704418589255823[48] = 0;
   out_7207704418589255823[49] = 0;
   out_7207704418589255823[50] = 0;
   out_7207704418589255823[51] = 0;
   out_7207704418589255823[52] = 0;
   out_7207704418589255823[53] = 0;
}
void h_14(double *state, double *unused, double *out_6372905199228253303) {
   out_6372905199228253303[0] = state[6];
   out_6372905199228253303[1] = state[7];
   out_6372905199228253303[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7958671449596407551) {
   out_7958671449596407551[0] = 0;
   out_7958671449596407551[1] = 0;
   out_7958671449596407551[2] = 0;
   out_7958671449596407551[3] = 0;
   out_7958671449596407551[4] = 0;
   out_7958671449596407551[5] = 0;
   out_7958671449596407551[6] = 1;
   out_7958671449596407551[7] = 0;
   out_7958671449596407551[8] = 0;
   out_7958671449596407551[9] = 0;
   out_7958671449596407551[10] = 0;
   out_7958671449596407551[11] = 0;
   out_7958671449596407551[12] = 0;
   out_7958671449596407551[13] = 0;
   out_7958671449596407551[14] = 0;
   out_7958671449596407551[15] = 0;
   out_7958671449596407551[16] = 0;
   out_7958671449596407551[17] = 0;
   out_7958671449596407551[18] = 0;
   out_7958671449596407551[19] = 0;
   out_7958671449596407551[20] = 0;
   out_7958671449596407551[21] = 0;
   out_7958671449596407551[22] = 0;
   out_7958671449596407551[23] = 0;
   out_7958671449596407551[24] = 0;
   out_7958671449596407551[25] = 1;
   out_7958671449596407551[26] = 0;
   out_7958671449596407551[27] = 0;
   out_7958671449596407551[28] = 0;
   out_7958671449596407551[29] = 0;
   out_7958671449596407551[30] = 0;
   out_7958671449596407551[31] = 0;
   out_7958671449596407551[32] = 0;
   out_7958671449596407551[33] = 0;
   out_7958671449596407551[34] = 0;
   out_7958671449596407551[35] = 0;
   out_7958671449596407551[36] = 0;
   out_7958671449596407551[37] = 0;
   out_7958671449596407551[38] = 0;
   out_7958671449596407551[39] = 0;
   out_7958671449596407551[40] = 0;
   out_7958671449596407551[41] = 0;
   out_7958671449596407551[42] = 0;
   out_7958671449596407551[43] = 0;
   out_7958671449596407551[44] = 1;
   out_7958671449596407551[45] = 0;
   out_7958671449596407551[46] = 0;
   out_7958671449596407551[47] = 0;
   out_7958671449596407551[48] = 0;
   out_7958671449596407551[49] = 0;
   out_7958671449596407551[50] = 0;
   out_7958671449596407551[51] = 0;
   out_7958671449596407551[52] = 0;
   out_7958671449596407551[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2728703337659485106) {
  err_fun(nom_x, delta_x, out_2728703337659485106);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4933784707852487941) {
  inv_err_fun(nom_x, true_x, out_4933784707852487941);
}
void pose_H_mod_fun(double *state, double *out_4112937202201059041) {
  H_mod_fun(state, out_4112937202201059041);
}
void pose_f_fun(double *state, double dt, double *out_41468171679069375) {
  f_fun(state,  dt, out_41468171679069375);
}
void pose_F_fun(double *state, double dt, double *out_7128628514967391957) {
  F_fun(state,  dt, out_7128628514967391957);
}
void pose_h_4(double *state, double *unused, double *out_8965394066110212061) {
  h_4(state, unused, out_8965394066110212061);
}
void pose_H_4(double *state, double *unused, double *out_7405284191817771769) {
  H_4(state, unused, out_7405284191817771769);
}
void pose_h_10(double *state, double *unused, double *out_4429682976893391883) {
  h_10(state, unused, out_4429682976893391883);
}
void pose_H_10(double *state, double *unused, double *out_3580593939681347040) {
  H_10(state, unused, out_3580593939681347040);
}
void pose_h_13(double *state, double *unused, double *out_9139916048338221099) {
  h_13(state, unused, out_9139916048338221099);
}
void pose_H_13(double *state, double *unused, double *out_7207704418589255823) {
  H_13(state, unused, out_7207704418589255823);
}
void pose_h_14(double *state, double *unused, double *out_6372905199228253303) {
  h_14(state, unused, out_6372905199228253303);
}
void pose_H_14(double *state, double *unused, double *out_7958671449596407551) {
  H_14(state, unused, out_7958671449596407551);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
