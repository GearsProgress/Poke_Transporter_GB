#include <tonc.h>

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE *obj_aff_buffer;

extern OBJ_ATTR *testroid;
extern OBJ_ATTR *prof;
extern OBJ_ATTR *btn_t_l;
extern OBJ_ATTR *btn_t_r;
extern OBJ_ATTR *btn_p_l;
extern OBJ_ATTR *btn_p_r;
extern OBJ_ATTR *btn_c_l;
extern OBJ_ATTR *btn_c_r;
extern OBJ_ATTR *dex_l[];
extern OBJ_ATTR *dex_m[];
extern OBJ_ATTR *dex_r[];
extern OBJ_ATTR *btn_d_l;
extern OBJ_ATTR *btn_d_r;

void load_background();
void load_textbox_background();
void load_opening_background();
void load_testroid();
void load_professor();
void load_btn_t_l();
void load_btn_t_r();
void load_btn_p_l();
void load_btn_p_r();
void load_btn_c_l();
void load_btn_c_r();
void load_dex_l();
void load_dex_m();
void load_dex_r();
void load_btn_d_l();
void load_btn_d_r();