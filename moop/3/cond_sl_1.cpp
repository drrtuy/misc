#include <clocale>
#include <iostream>

using  std::cout;
using  std::cin;
using  std::endl;

typedef struct {
    float min;
    float max;
} min_max_t;

min_max_t *GetMinMax(float a, float b);
bool isEmbedded(min_max_t *rectang1, min_max_t *rectang2);

int main() 
{
    float a = 0.0, b = 0.0, c = 0.0, d = 0.0;

    setlocale(LC_ALL, ""); 
    cout << "Введите 2 float-а для задания размеров сторон 1ой фигуры" << endl;
    cin >> a;
    cin >> b;
    cout << "Введите 2 float-а для задания размеров сторон 2ой фигуры" << endl;
    cin >> c;
    cin >> d;
    cout << a << " " << d << endl;       

    cout << "Прямоугольник со сторонами: " << a << " и " << b;
    if (isEmbedded(GetMinMax(a, b), GetMinMax(c, d))) {
        cout << " можно ";
    } else {
        cout << " нельзя ";
    }
    cout << "поместить в прямоугольник со сторонами: " << c << " и " << d << endl;
    return 0;

}

min_max_t *GetMinMax(float a, float b)
{
    min_max_t *result;
    result = new min_max_t;
    if (a > b) {
        result->min = b;
        result->max = a;
    } else {
        result->max = b;
        result->min = a;
    } 
    return result;
}

bool isEmbedded(min_max_t *rectang1, min_max_t *rectang2)
{
    bool result = false;
    if (rectang1->max <= rectang2->min) {
        result = true;
    } 

    return result;
}
