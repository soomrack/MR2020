#include <stdio.h>
#include <math.h>
int main(void){
    int MunthBezBabok1 = 5;   // ����� ������ � ������� �� ������� ����� ��� �������/�������
    int MunthBezBabok2 = 45;   // ����� �� ����� ���
    int SrokProsrochki1 = 20;  // ������� ���� �������� �� �� ��� �� ������� ����� ��������� ��� ��������� ���������� ���� �������
    int SrokProsrochki2 = 6;
    float kap = 1000000.0, doh = 20000.0; // �������, �����
    int i, n = 9;
    int Pereplata1 = doh*powf(1.007, SrokProsrochki1)-doh; // ��������� ����� ��������� ����� ��� �������/��������
    int Pereplata2 = doh*powf(1.007, SrokProsrochki2)-doh;
    for (i = 1; i <= 12*n; i++){
        if (i==MunthBezBabok1) kap += Pereplata1;
        if (i==MunthBezBabok2) kap += Pereplata2;

        kap = (kap + doh)*1.0055; // ��� ������� ������� 6,6 (�������� 0,55)

        //if (i%12 == 0)2
        //    kap *=0.96; // ��������� �������� 4% (�������� ����� ����� � ������ = ������ �� ������ �������)
    }
    printf("Itogovaya summa na vklade: %.2f\n", kap);

    int vpl; // ������� �� ��������
    float kr = 1510500.0, stkv = 2500000.0; // ������ � ������ ��������� ��������� �� ������ ������, ��������� ��������
    i = 1;
    while (kr > 0){ // ���� �� ������� ������
        if (i==MunthBezBabok1) doh += Pereplata1; // ���� ���������� ��������� ����������
        if (i==MunthBezBabok2) doh += Pereplata2;
        kr = (kr - doh)*1.007; // ������ �� ������� 8,4%
        i++
                ;
    }
    vpl = doh*i + kr + 1000000; // �������� ����������� �� ��������(+kr - ����� ��������� ��� ��������� �������)
    stkv *= powf(1.05, 8.0);    // ��������� �������� � ��������� ������ � ������ ���������� �� 5% � ���
    //stkv *= 1.3;

    printf("Summ viplat za kv: %d\nKolichestvo let %.2f\nStoimist' kv na prodazhu:%.2f\n", vpl, (float)i/12, stkv);

    float sdach = 0.0;
    for (i = 1; i <= 12*7; i++){ // ���� �������� 2 ���� ���������, � � �� ����� �� �������� ������� � ������� ������
        sdach += 15000; // �� �������� � �������� � ������� 2,5 ���, �� � ������ 15�
    //    if (i%12 == 0)
    //        sdach *=0.96; // ������ ������� �������� � �������� ������ ������
    }
    printf("Den'gi so sdachi kvartiri: %.2f\nItogo plan s kvartiroi: %.2f\n", sdach, sdach+stkv);
    return 0;
}