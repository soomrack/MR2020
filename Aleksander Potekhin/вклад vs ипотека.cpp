//a-зарплату//
//b-первоначальный взнос//
//c-срок//
//d-стоимость квартиры//
//e-вклад в %, ежемесячная капитализация//
//f-рост стоимости квартиры в год в %//
//g-дополнительный доход (ипотека)//
//h-ипотечный кредит в %//

#include <iostream>

using namespace std;

int main()
{
    double a, b, c, d, e, f, g, h, ip, ip1, t, S1, S, Q1, Q;
    cout << "vvedite zarplatu" << endl;
    cin >> a;
    cout << "vvedite pervonachalniy vznos" << endl;
    cin >> b;
    cout << "vvedite srok" << endl;
    cin >> c;
    cout << "vvedite stoimost kvartiri" << endl;
    cin >> d;
    cout << "vvedite vklad v %" << endl;
    cin >> e;
    cout << "vvedite rost stoimosti kvartiri v %" << endl;
    cin >> f;
    cout << "vvedite dop dohod (ipoteka)" << endl;
    cin >> g;
    cout << "vvedite ipotechniy kredit v %" << endl;
    cin >> h;

    //Сначала рассмортрим вариант с ипотекой//

    ip1 = d-b; //сумма ипотечного кредита//
    ip = h/1200; //ежемесячная процентная ставка по кредиту//
    t = pow(1 + ip,c);//общая ставка//
    S1 = ip1 * ip * t / (t - 1);//ежемесячный платёж//
    S = S1 * t + b-(a+g-S1)*t;//общая сумма в варианте с ипотекой//
   
    //теперь рассмотрим вариант со вкладом//

    Q1 = b * (1 + e / 1200) * c + (a * (1 + e / 1200) * c) / (e / 1200);
    Q = d * (1 + f / 100) * c / 12;

    //сравним где уходит по итогу больше денег//

    if (Q1 > (Q + (a + g - S1) * t))
    {
        cout << "vklad vigodnee";
    }
    else 
    {
        cout << "ipoteka vigodnee";
    }
}
