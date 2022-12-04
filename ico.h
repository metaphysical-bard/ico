#pragma once

#include <math.h>

//�ϐ�
double ICO_MR;//���a
int ICO_MS;//�ċA��
double* ICO_P = NULL;//�z��i�[�p�̃|�C���^
int ICO_COUNT = 0;//�J�E���g�p

//�֐�
double ICO_sn(double x, double y, double z);
void ICO_se(double* k);
void ICO_sl(double* w, double* e, double* d);
void ICO_sd(double a[3], double b[3], double c[3]);
void ICO_sa(double a[3], double b[3], double c[3], int Scount);
void ICO_MAIN(double MR, int MS);

//���������Ƃ߂�֐�
double ICO_sn(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

//������MR�ɂ���֐�
void ICO_se(double* k) {
    double q = sqrt(*(k + 0) * *(k + 0) + *(k + 1) * *(k + 1) + *(k + 2) * *(k + 2));
    *(k + 0) = *(k + 0) * ICO_MR / q;
    *(k + 1) = *(k + 1) * ICO_MR / q;
    *(k + 2) = *(k + 2) * ICO_MR / q;
}

//��n�_�̒��_�����߂�֐�
void ICO_sl(double* w, double* e, double* d) {
    *(d + 0) = (*(w + 0) + *(e + 0)) * 0.5;
    *(d + 1) = (*(w + 1) + *(e + 1)) * 0.5;
    *(d + 2) = (*(w + 2) + *(e + 2)) * 0.5;
}

//�z��ɒl���i�[����֐�
void ICO_sd(double a[3], double b[3], double c[3]) {
    ICO_se(a); ICO_se(b); ICO_se(c);
    int i = ICO_COUNT * 3;

    *(ICO_P + i + 0) = a[0];
    *(ICO_P + i + 1) = a[1];
    *(ICO_P + i + 2) = a[2];

    *(ICO_P + i + 3) = b[0];
    *(ICO_P + i + 4) = b[1];
    *(ICO_P + i + 5) = b[2];

    *(ICO_P + i + 6) = c[0];
    *(ICO_P + i + 7) = c[1];
    *(ICO_P + i + 8) = c[2];

    ICO_COUNT += 3;
}

//���_�����Ƃɕ`��
void ICO_sa(double a[3], double b[3], double c[3], int Scount) {
    if (Scount >= ICO_MS) {
        ICO_sd(a, b, c);
    }
    else {
        double ab[3];
        double ac[3];
        double bc[3];
        Scount++;
        ICO_sl(a, b, ab);
        ICO_sl(a, c, ac);
        ICO_sl(b, c, bc);
        ICO_sa(a, ab, ac, Scount);
        ICO_sa(b, bc, ab, Scount);
        ICO_sa(c, ac, bc, Scount);
        ICO_sa(ab, bc, ac, Scount);
    }
}

void ICO_MAIN(double MR, int MS) {
    ICO_MR = MR;// ���a
    ICO_MS = MS; //�ċA��(0~5���炢���ڈ��B�傫������ƃt���[�Y)

    double r, yr;
    r = ICO_MR / 2;
    yr = (1 + sqrt(5)) / 2 * r;

    //��\�ʑ̂̒��_�����߂�
    double p[12][3] = {
        { r,yr,0 },
        { r,-yr,0 },
        { -r,yr,0 },
        { -r,-yr,0 },

        { yr,0,r },
        { yr,0,-r },
        { -yr,0,r },
        { -yr,0,-r },

        { 0,r,yr },
        { 0,r,-yr },
        { 0,-r,yr },
        { 0,-r,-yr } };

    //���_�����Ƃɉ��Z
    ICO_sa(p[1], p[3], p[10], 0);
    ICO_sa(p[1], p[11], p[3], 0);

    ICO_sa(p[1], p[5], p[11], 0);
    ICO_sa(p[1], p[10], p[4], 0);
    ICO_sa(p[3], p[11], p[7], 0);
    ICO_sa(p[3], p[6], p[10], 0);

    ICO_sa(p[1], p[4], p[5], 0);
    ICO_sa(p[3], p[7], p[6], 0);
    ICO_sa(p[0], p[5], p[4], 0);
    ICO_sa(p[2], p[6], p[7], 0);

    ICO_sa(p[5], p[9], p[11], 0);
    ICO_sa(p[7], p[11], p[9], 0);
    ICO_sa(p[4], p[10], p[8], 0);
    ICO_sa(p[6], p[8], p[10], 0);

    ICO_sa(p[0], p[9], p[5], 0);
    ICO_sa(p[0], p[4], p[8], 0);
    ICO_sa(p[2], p[7], p[9], 0);
    ICO_sa(p[2], p[8], p[6], 0);

    ICO_sa(p[0], p[8], p[2], 0);
    ICO_sa(p[0], p[2], p[9], 0);
}