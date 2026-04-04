#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6097178045969778433) {
   out_6097178045969778433[0] = delta_x[0] + nom_x[0];
   out_6097178045969778433[1] = delta_x[1] + nom_x[1];
   out_6097178045969778433[2] = delta_x[2] + nom_x[2];
   out_6097178045969778433[3] = delta_x[3] + nom_x[3];
   out_6097178045969778433[4] = delta_x[4] + nom_x[4];
   out_6097178045969778433[5] = delta_x[5] + nom_x[5];
   out_6097178045969778433[6] = delta_x[6] + nom_x[6];
   out_6097178045969778433[7] = delta_x[7] + nom_x[7];
   out_6097178045969778433[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8027253490896525492) {
   out_8027253490896525492[0] = -nom_x[0] + true_x[0];
   out_8027253490896525492[1] = -nom_x[1] + true_x[1];
   out_8027253490896525492[2] = -nom_x[2] + true_x[2];
   out_8027253490896525492[3] = -nom_x[3] + true_x[3];
   out_8027253490896525492[4] = -nom_x[4] + true_x[4];
   out_8027253490896525492[5] = -nom_x[5] + true_x[5];
   out_8027253490896525492[6] = -nom_x[6] + true_x[6];
   out_8027253490896525492[7] = -nom_x[7] + true_x[7];
   out_8027253490896525492[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2448319121674464114) {
   out_2448319121674464114[0] = 1.0;
   out_2448319121674464114[1] = 0.0;
   out_2448319121674464114[2] = 0.0;
   out_2448319121674464114[3] = 0.0;
   out_2448319121674464114[4] = 0.0;
   out_2448319121674464114[5] = 0.0;
   out_2448319121674464114[6] = 0.0;
   out_2448319121674464114[7] = 0.0;
   out_2448319121674464114[8] = 0.0;
   out_2448319121674464114[9] = 0.0;
   out_2448319121674464114[10] = 1.0;
   out_2448319121674464114[11] = 0.0;
   out_2448319121674464114[12] = 0.0;
   out_2448319121674464114[13] = 0.0;
   out_2448319121674464114[14] = 0.0;
   out_2448319121674464114[15] = 0.0;
   out_2448319121674464114[16] = 0.0;
   out_2448319121674464114[17] = 0.0;
   out_2448319121674464114[18] = 0.0;
   out_2448319121674464114[19] = 0.0;
   out_2448319121674464114[20] = 1.0;
   out_2448319121674464114[21] = 0.0;
   out_2448319121674464114[22] = 0.0;
   out_2448319121674464114[23] = 0.0;
   out_2448319121674464114[24] = 0.0;
   out_2448319121674464114[25] = 0.0;
   out_2448319121674464114[26] = 0.0;
   out_2448319121674464114[27] = 0.0;
   out_2448319121674464114[28] = 0.0;
   out_2448319121674464114[29] = 0.0;
   out_2448319121674464114[30] = 1.0;
   out_2448319121674464114[31] = 0.0;
   out_2448319121674464114[32] = 0.0;
   out_2448319121674464114[33] = 0.0;
   out_2448319121674464114[34] = 0.0;
   out_2448319121674464114[35] = 0.0;
   out_2448319121674464114[36] = 0.0;
   out_2448319121674464114[37] = 0.0;
   out_2448319121674464114[38] = 0.0;
   out_2448319121674464114[39] = 0.0;
   out_2448319121674464114[40] = 1.0;
   out_2448319121674464114[41] = 0.0;
   out_2448319121674464114[42] = 0.0;
   out_2448319121674464114[43] = 0.0;
   out_2448319121674464114[44] = 0.0;
   out_2448319121674464114[45] = 0.0;
   out_2448319121674464114[46] = 0.0;
   out_2448319121674464114[47] = 0.0;
   out_2448319121674464114[48] = 0.0;
   out_2448319121674464114[49] = 0.0;
   out_2448319121674464114[50] = 1.0;
   out_2448319121674464114[51] = 0.0;
   out_2448319121674464114[52] = 0.0;
   out_2448319121674464114[53] = 0.0;
   out_2448319121674464114[54] = 0.0;
   out_2448319121674464114[55] = 0.0;
   out_2448319121674464114[56] = 0.0;
   out_2448319121674464114[57] = 0.0;
   out_2448319121674464114[58] = 0.0;
   out_2448319121674464114[59] = 0.0;
   out_2448319121674464114[60] = 1.0;
   out_2448319121674464114[61] = 0.0;
   out_2448319121674464114[62] = 0.0;
   out_2448319121674464114[63] = 0.0;
   out_2448319121674464114[64] = 0.0;
   out_2448319121674464114[65] = 0.0;
   out_2448319121674464114[66] = 0.0;
   out_2448319121674464114[67] = 0.0;
   out_2448319121674464114[68] = 0.0;
   out_2448319121674464114[69] = 0.0;
   out_2448319121674464114[70] = 1.0;
   out_2448319121674464114[71] = 0.0;
   out_2448319121674464114[72] = 0.0;
   out_2448319121674464114[73] = 0.0;
   out_2448319121674464114[74] = 0.0;
   out_2448319121674464114[75] = 0.0;
   out_2448319121674464114[76] = 0.0;
   out_2448319121674464114[77] = 0.0;
   out_2448319121674464114[78] = 0.0;
   out_2448319121674464114[79] = 0.0;
   out_2448319121674464114[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1967878612429161037) {
   out_1967878612429161037[0] = state[0];
   out_1967878612429161037[1] = state[1];
   out_1967878612429161037[2] = state[2];
   out_1967878612429161037[3] = state[3];
   out_1967878612429161037[4] = state[4];
   out_1967878612429161037[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1967878612429161037[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1967878612429161037[7] = state[7];
   out_1967878612429161037[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6453372126869218354) {
   out_6453372126869218354[0] = 1;
   out_6453372126869218354[1] = 0;
   out_6453372126869218354[2] = 0;
   out_6453372126869218354[3] = 0;
   out_6453372126869218354[4] = 0;
   out_6453372126869218354[5] = 0;
   out_6453372126869218354[6] = 0;
   out_6453372126869218354[7] = 0;
   out_6453372126869218354[8] = 0;
   out_6453372126869218354[9] = 0;
   out_6453372126869218354[10] = 1;
   out_6453372126869218354[11] = 0;
   out_6453372126869218354[12] = 0;
   out_6453372126869218354[13] = 0;
   out_6453372126869218354[14] = 0;
   out_6453372126869218354[15] = 0;
   out_6453372126869218354[16] = 0;
   out_6453372126869218354[17] = 0;
   out_6453372126869218354[18] = 0;
   out_6453372126869218354[19] = 0;
   out_6453372126869218354[20] = 1;
   out_6453372126869218354[21] = 0;
   out_6453372126869218354[22] = 0;
   out_6453372126869218354[23] = 0;
   out_6453372126869218354[24] = 0;
   out_6453372126869218354[25] = 0;
   out_6453372126869218354[26] = 0;
   out_6453372126869218354[27] = 0;
   out_6453372126869218354[28] = 0;
   out_6453372126869218354[29] = 0;
   out_6453372126869218354[30] = 1;
   out_6453372126869218354[31] = 0;
   out_6453372126869218354[32] = 0;
   out_6453372126869218354[33] = 0;
   out_6453372126869218354[34] = 0;
   out_6453372126869218354[35] = 0;
   out_6453372126869218354[36] = 0;
   out_6453372126869218354[37] = 0;
   out_6453372126869218354[38] = 0;
   out_6453372126869218354[39] = 0;
   out_6453372126869218354[40] = 1;
   out_6453372126869218354[41] = 0;
   out_6453372126869218354[42] = 0;
   out_6453372126869218354[43] = 0;
   out_6453372126869218354[44] = 0;
   out_6453372126869218354[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6453372126869218354[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6453372126869218354[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6453372126869218354[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6453372126869218354[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6453372126869218354[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6453372126869218354[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6453372126869218354[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6453372126869218354[53] = -9.8100000000000005*dt;
   out_6453372126869218354[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6453372126869218354[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6453372126869218354[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6453372126869218354[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6453372126869218354[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6453372126869218354[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6453372126869218354[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6453372126869218354[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6453372126869218354[62] = 0;
   out_6453372126869218354[63] = 0;
   out_6453372126869218354[64] = 0;
   out_6453372126869218354[65] = 0;
   out_6453372126869218354[66] = 0;
   out_6453372126869218354[67] = 0;
   out_6453372126869218354[68] = 0;
   out_6453372126869218354[69] = 0;
   out_6453372126869218354[70] = 1;
   out_6453372126869218354[71] = 0;
   out_6453372126869218354[72] = 0;
   out_6453372126869218354[73] = 0;
   out_6453372126869218354[74] = 0;
   out_6453372126869218354[75] = 0;
   out_6453372126869218354[76] = 0;
   out_6453372126869218354[77] = 0;
   out_6453372126869218354[78] = 0;
   out_6453372126869218354[79] = 0;
   out_6453372126869218354[80] = 1;
}
void h_25(double *state, double *unused, double *out_2045742138170453634) {
   out_2045742138170453634[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5971299771663955791) {
   out_5971299771663955791[0] = 0;
   out_5971299771663955791[1] = 0;
   out_5971299771663955791[2] = 0;
   out_5971299771663955791[3] = 0;
   out_5971299771663955791[4] = 0;
   out_5971299771663955791[5] = 0;
   out_5971299771663955791[6] = 1;
   out_5971299771663955791[7] = 0;
   out_5971299771663955791[8] = 0;
}
void h_24(double *state, double *unused, double *out_5287849605296050304) {
   out_5287849605296050304[0] = state[4];
   out_5287849605296050304[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1224790444697446757) {
   out_1224790444697446757[0] = 0;
   out_1224790444697446757[1] = 0;
   out_1224790444697446757[2] = 0;
   out_1224790444697446757[3] = 0;
   out_1224790444697446757[4] = 1;
   out_1224790444697446757[5] = 0;
   out_1224790444697446757[6] = 0;
   out_1224790444697446757[7] = 0;
   out_1224790444697446757[8] = 0;
   out_1224790444697446757[9] = 0;
   out_1224790444697446757[10] = 0;
   out_1224790444697446757[11] = 0;
   out_1224790444697446757[12] = 0;
   out_1224790444697446757[13] = 0;
   out_1224790444697446757[14] = 1;
   out_1224790444697446757[15] = 0;
   out_1224790444697446757[16] = 0;
   out_1224790444697446757[17] = 0;
}
void h_30(double *state, double *unused, double *out_8519729284785048797) {
   out_8519729284785048797[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5558753960553979070) {
   out_5558753960553979070[0] = 0;
   out_5558753960553979070[1] = 0;
   out_5558753960553979070[2] = 0;
   out_5558753960553979070[3] = 0;
   out_5558753960553979070[4] = 1;
   out_5558753960553979070[5] = 0;
   out_5558753960553979070[6] = 0;
   out_5558753960553979070[7] = 0;
   out_5558753960553979070[8] = 0;
}
void h_26(double *state, double *unused, double *out_7576219431883386362) {
   out_7576219431883386362[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2229796452789899567) {
   out_2229796452789899567[0] = 0;
   out_2229796452789899567[1] = 0;
   out_2229796452789899567[2] = 0;
   out_2229796452789899567[3] = 0;
   out_2229796452789899567[4] = 0;
   out_2229796452789899567[5] = 0;
   out_2229796452789899567[6] = 0;
   out_2229796452789899567[7] = 1;
   out_2229796452789899567[8] = 0;
}
void h_27(double *state, double *unused, double *out_7047415405831299279) {
   out_7047415405831299279[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7733517272354403981) {
   out_7733517272354403981[0] = 0;
   out_7733517272354403981[1] = 0;
   out_7733517272354403981[2] = 0;
   out_7733517272354403981[3] = 1;
   out_7733517272354403981[4] = 0;
   out_7733517272354403981[5] = 0;
   out_7733517272354403981[6] = 0;
   out_7733517272354403981[7] = 0;
   out_7733517272354403981[8] = 0;
}
void h_29(double *state, double *unused, double *out_7322609468115805168) {
   out_7322609468115805168[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5048522616239586886) {
   out_5048522616239586886[0] = 0;
   out_5048522616239586886[1] = 1;
   out_5048522616239586886[2] = 0;
   out_5048522616239586886[3] = 0;
   out_5048522616239586886[4] = 0;
   out_5048522616239586886[5] = 0;
   out_5048522616239586886[6] = 0;
   out_5048522616239586886[7] = 0;
   out_5048522616239586886[8] = 0;
}
void h_28(double *state, double *unused, double *out_6173421452042927390) {
   out_6173421452042927390[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3917465057416066028) {
   out_3917465057416066028[0] = 1;
   out_3917465057416066028[1] = 0;
   out_3917465057416066028[2] = 0;
   out_3917465057416066028[3] = 0;
   out_3917465057416066028[4] = 0;
   out_3917465057416066028[5] = 0;
   out_3917465057416066028[6] = 0;
   out_3917465057416066028[7] = 0;
   out_3917465057416066028[8] = 0;
}
void h_31(double *state, double *unused, double *out_1591707390083568716) {
   out_1591707390083568716[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6001945733540916219) {
   out_6001945733540916219[0] = 0;
   out_6001945733540916219[1] = 0;
   out_6001945733540916219[2] = 0;
   out_6001945733540916219[3] = 0;
   out_6001945733540916219[4] = 0;
   out_6001945733540916219[5] = 0;
   out_6001945733540916219[6] = 0;
   out_6001945733540916219[7] = 0;
   out_6001945733540916219[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6097178045969778433) {
  err_fun(nom_x, delta_x, out_6097178045969778433);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8027253490896525492) {
  inv_err_fun(nom_x, true_x, out_8027253490896525492);
}
void car_H_mod_fun(double *state, double *out_2448319121674464114) {
  H_mod_fun(state, out_2448319121674464114);
}
void car_f_fun(double *state, double dt, double *out_1967878612429161037) {
  f_fun(state,  dt, out_1967878612429161037);
}
void car_F_fun(double *state, double dt, double *out_6453372126869218354) {
  F_fun(state,  dt, out_6453372126869218354);
}
void car_h_25(double *state, double *unused, double *out_2045742138170453634) {
  h_25(state, unused, out_2045742138170453634);
}
void car_H_25(double *state, double *unused, double *out_5971299771663955791) {
  H_25(state, unused, out_5971299771663955791);
}
void car_h_24(double *state, double *unused, double *out_5287849605296050304) {
  h_24(state, unused, out_5287849605296050304);
}
void car_H_24(double *state, double *unused, double *out_1224790444697446757) {
  H_24(state, unused, out_1224790444697446757);
}
void car_h_30(double *state, double *unused, double *out_8519729284785048797) {
  h_30(state, unused, out_8519729284785048797);
}
void car_H_30(double *state, double *unused, double *out_5558753960553979070) {
  H_30(state, unused, out_5558753960553979070);
}
void car_h_26(double *state, double *unused, double *out_7576219431883386362) {
  h_26(state, unused, out_7576219431883386362);
}
void car_H_26(double *state, double *unused, double *out_2229796452789899567) {
  H_26(state, unused, out_2229796452789899567);
}
void car_h_27(double *state, double *unused, double *out_7047415405831299279) {
  h_27(state, unused, out_7047415405831299279);
}
void car_H_27(double *state, double *unused, double *out_7733517272354403981) {
  H_27(state, unused, out_7733517272354403981);
}
void car_h_29(double *state, double *unused, double *out_7322609468115805168) {
  h_29(state, unused, out_7322609468115805168);
}
void car_H_29(double *state, double *unused, double *out_5048522616239586886) {
  H_29(state, unused, out_5048522616239586886);
}
void car_h_28(double *state, double *unused, double *out_6173421452042927390) {
  h_28(state, unused, out_6173421452042927390);
}
void car_H_28(double *state, double *unused, double *out_3917465057416066028) {
  H_28(state, unused, out_3917465057416066028);
}
void car_h_31(double *state, double *unused, double *out_1591707390083568716) {
  h_31(state, unused, out_1591707390083568716);
}
void car_H_31(double *state, double *unused, double *out_6001945733540916219) {
  H_31(state, unused, out_6001945733540916219);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
