#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1607973439159951126);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2168352623537558810);
void car_H_mod_fun(double *state, double *out_2583274475517743554);
void car_f_fun(double *state, double dt, double *out_5962891950542322522);
void car_F_fun(double *state, double dt, double *out_2636529809798275009);
void car_h_25(double *state, double *unused, double *out_1279931555827013363);
void car_H_25(double *state, double *unused, double *out_6609913750394493683);
void car_h_24(double *state, double *unused, double *out_1314306168655061671);
void car_H_24(double *state, double *unused, double *out_8782563349399993249);
void car_h_30(double *state, double *unused, double *out_1716461369006897797);
void car_H_30(double *state, double *unused, double *out_306776591097123072);
void car_h_26(double *state, double *unused, double *out_5998025210250558305);
void car_H_26(double *state, double *unused, double *out_8095327004441001709);
void car_h_27(double *state, double *unused, double *out_3721741711833832282);
void car_H_27(double *state, double *unused, double *out_8914016009338158664);
void car_h_29(double *state, double *unused, double *out_4041523544986840159);
void car_H_29(double *state, double *unused, double *out_3581349447572852872);
void car_h_28(double *state, double *unused, double *out_8147102627132063815);
void car_H_28(double *state, double *unused, double *out_8663748464642383446);
void car_h_31(double *state, double *unused, double *out_5490903670523337573);
void car_H_31(double *state, double *unused, double *out_6579267788517533255);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}