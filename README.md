# Лабораторная работа № 6

Выполнил Ходин Иван, 427 группа

## Вариант № 9

Задание: Найти точку минимума функции <img src="https://bit.ly/3eQMkmJ" align="center" border="0" alt="f( x_{1} , x_{2} , x_{3} ) =  x^{2}_{1}  + 8x_{1} + 5x^{2}_{2}  + 7x^{2}_{3}  + 119x_{3} + 531.75,    [ x_{1} = 8,  x_{2} = -2,  x_{3}  = 6]" width="660" height="26" /> методом наискорейшего спуска. Для одномерной минимизации использовать метод квадратичной интерполяции. Для поиска интервала унимолдальности использовать алгоритм скользящего окна.
В окрестности точки минимума построить линии уровня и траекторию поиска на одном графике.  

## Теоретическая часть:

Для успешного выполнения работы необходима теоретическая база и понимание работы перечисленных в задании методов:

1) Метод наискорейшего спуска:

В этом методе αk выбирается из условия минимума функции f(x) вдоль направления <img src="https://bit.ly/2KGLN98" align="center" border="0" alt=" p^{k} " width="24" height="24" />, т.е. <img src="https://bit.ly/2VGPBgC" align="center" border="0" alt="f( x^{k}  +  \alpha_{k}p^{k}) =  \min_{ \alpha > 0}  f( x^{k}  +  \alpha_{k}p^{k})    " width="264" height="24" />. Таким образом, в методе наискорейшего спуска на каждом шаге
необходимо решать задачу минимизации функции одной переменной.

2) Алгоритм скользящего окна:

нахождение интервалов a и b,где находиться минимум для <img src="https://bit.ly/2W1pBfa" align="center" border="0" alt=" \alpha_{k} " width="24" height="15" />.
Выбираем <img src="https://bit.ly/2VHD1hd" align="center" border="0" alt=" x_{0} " width="22" height="15" /> и задаем шаг h>0
<img src="https://bit.ly/3f2Cnmn" align="center" border="0" alt="1) f(x_{0} - h) > f(x_{0}) < f(x_{0} + h)  \Longrightarrow a = x_{0} - h, b = x_{0} + h" width="467" height="19" />
<img src="https://bit.ly/3bJb7qP" align="center" border="0" alt="2) f(x_{0} - h) >  f(x_{0} + h)  \Longrightarrow   x_{0} = x_{0} + h/2" width="336" height="19" />
<img src="https://bit.ly/2zBuiEQ" align="center" border="0" alt="3) f(x_{0} - h) <  f(x_{0} + h)  \Longrightarrow   x_{0} = x_{0} - h/2" width="336" height="19" />

3) Метод квадратичной интерполяции:

Здесь задаются пробные три пробные точки x1 = (a + b)/2, x2 и x3. Для нахождения точки x2 задается шаг h > 0 в положительном направлении от точки x1, т.е. x2 = x1 + h и если f(x1) > f(x2), то x3 = x1 + 2h, иначе x3 = x1 − h. Вычисляются значения функции в этих точках f(x1), f(x2), f(x3), строится квадратичный интерполяционый многочлен по трем точкам и находится его точка минимума по формуле x∗ = ((x2)^2 − (x3)^2)f(x1) + ((x3)^2 − (x1)^2)f(x2) +((x1)^2 − (x2)^2)f(x3)(x2 − x3)f(x1) + (x3 − x1)f(x2) + (x1 − x2)f(x3))/2. Находится также точка xmin = arg min(f(x1), f(x2, f(x3)).
Если знаменатель в формуле для нахождения минимума квадратичного интерполяционного многочлена равен нулю, т.е. все три
точки лежат на одной прямой рекомендуется выбрать за x
1 = xmin и повторить нахождение точки x∗. Критерием окончания в этого процесса является выполнение условий для заданного ϵ:
|f(xmin) − f(x∗)| < ϵ, |xmin − x∗| < ϵ
Если условия окончания не выполняются и x∗ ∈ [x1, x3] точка x1 заменяется на точку arg min(f(xmin), f(x∗)), в противном случае точка x1 заменяется на x∗.

## Практическая часть:

Программа содержит функции, реализующие заданные методы 

Функция f(double *x) возвращает значение исходной функции в точке x, p1(double *x), p2(double *x), p2(double *x) - производные по первой, второй и третьей переменной соответственно, fun(double *x, double a, double p) - значение в точке x+ap. 
Метод скользящего окна wind(double *x, double a, double *p) возвращает середину отрезка унимодальности, метод квадратичной интерполяции interpol(double *x, double a, double *p) возвращает точку максимума функции, метод наискорейшего спуска fastspusk(double *x0) выводит точку минимума функции и значение функции в этой точке, а также записывает в текстовый файл точки траектории поиска. 
Последовательность запуска: компиляция части программы на с++, ее запуск, затем запуск части на python, в которой находится нарисованная траектория поиска и линии уровня.

### Результаты:

У функции <img src="https://bit.ly/3eQMkmJ" align="center" border="0" alt="f( x_{1} , x_{2} , x_{3} ) =  x^{2}_{1}  + 8x_{1} + 5x^{2}_{2}  + 7x^{2}_{3}  + 119x_{3} + 531.75,    [ x_{1} = 8,  x_{2} = -2,  x_{3}  = 6]" width="660" height="26" /> была найдена точка минимума [-4, 0, -8.5] и значение в ней, равное 10 за семь итерациий с точностью 1е-4 при начальной точке [8, -2, 6].

![https://github.com/IvanKhodin/lab6/blob/master/5AD48CCF-FC09-4640-9189-71FAE8829A91](https://github.com/IvanKhodin/lab6/blob/master/5AD48CCF-FC09-4640-9189-71FAE8829A91.jpeg)
![https://github.com/IvanKhodin/lab6/blob/master/5E3095B8-A8BB-40C3-BF84-BCA3686BD8E7](https://github.com/IvanKhodin/lab6/blob/master/5E3095B8-A8BB-40C3-BF84-BCA3686BD8E7.jpeg)
