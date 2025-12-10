#ifndef LONGDOUBLE_H
#define LONGDOUBLE_H

#include <vector>
#include <string>
#include <QString>

class LongDouble
{
public:
    // Конструкторы
    LongDouble();
    explicit LongDouble(double value);
    explicit LongDouble(const QString& str);
    LongDouble(const std::string& str, bool* check = nullptr);

    // Базовые арифметические операции
    LongDouble operator+(const LongDouble& other) const;
    LongDouble operator-(const LongDouble& other) const;
    LongDouble operator*(const LongDouble& other) const;
    LongDouble operator/(const LongDouble& other) const;

    // Унарные операторы
    LongDouble operator-() const;

    // Операторы сравнения
    bool operator==(const LongDouble& other) const;
    bool operator!=(const LongDouble& other) const;
    bool operator<(const LongDouble& other) const;
    bool operator>(const LongDouble& other) const;
    bool operator<=(const LongDouble& other) const;
    bool operator>=(const LongDouble& other) const;

    // Преобразования
    QString toQString() const;
    std::string toString() const;
    double toDouble() const;

    // Вспомогательные методы
    bool isZero() const;
    bool isPositive() const;

private:
    std::vector<int> digits;  // цифры числа (от старших к младшим)
    bool positive;            // true = положительное, false = отрицательное
    int decimalPoint;         // положение запятой (количество цифр после запятой)

    // Вспомогательные методы
    void removeLeadingZeros();
    void removeTrailingZeros();
    void normalize();
    void fromString(const std::string& str, bool* check);

    // Арифметические вспомогательные методы
    static LongDouble addAbsoluteValues(const LongDouble& a, const LongDouble& b);
    static LongDouble subtractAbsoluteValues(const LongDouble& a, const LongDouble& b);
    static bool absoluteLess(const LongDouble& a, const LongDouble& b);
    static bool absoluteEqual(const LongDouble& a, const LongDouble& b);

    // Выравнивание запятых
    static void alignDecimalPoints(LongDouble& a, LongDouble& b);

    // Умножение и деление
    LongDouble multiplyByDigit(int digit) const;
    LongDouble shiftRight(int positions) const;
};

#endif // LONGDOUBLE_H
