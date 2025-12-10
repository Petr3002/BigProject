#include "longdouble.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cctype>

LongDouble::LongDouble() : positive(true), decimalPoint(0) {
    digits.push_back(0);
}

LongDouble::LongDouble(double value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(15) << value;
    fromString(ss.str(), nullptr);
}

LongDouble::LongDouble(const QString& str) {
    fromString(str.toStdString(), nullptr);
}

LongDouble::LongDouble(const std::string& str, bool* check) {
    fromString(str, check);
}

void LongDouble::fromString(const std::string& str, bool* check) {
    digits.clear();
    positive = true;
    decimalPoint = 0;

    if (check) *check = true;

    if (str.empty()) {
        digits.push_back(0);
        if (check) *check = false;
        return;
    }

    size_t start = 0;

    // Обработка знака
    if (str[0] == '-') {
        positive = false;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }

    // Проверка на пустую строку после знака
    if (start >= str.length()) {
        digits.push_back(0);
        if (check) *check = false;
        return;
    }

    bool hasDecimalPoint = false;
    int decimalDigits = 0;
    bool readingDecimal = false;

    // Чтение цифр
    for (size_t i = start; i < str.length(); ++i) {
        char c = str[i];

        if (c == '.' || c == ',') {
            if (hasDecimalPoint) {
                if (check) *check = false;
                digits.push_back(0);
                return;
            }
            hasDecimalPoint = true;
            readingDecimal = true;
            continue;
        }

        if (!std::isdigit(c)) {
            if (check) *check = false;
            digits.push_back(0);
            return;
        }

        digits.push_back(c - '0');

        if (readingDecimal) {
            decimalDigits++;
        }
    }

    // Удаляем ведущие нули в целой части
    size_t nonZeroIndex = 0;
    while (nonZeroIndex < digits.size() - decimalDigits && digits[nonZeroIndex] == 0) {
        nonZeroIndex++;
    }

    if (nonZeroIndex > 0) {
        digits.erase(digits.begin(), digits.begin() + nonZeroIndex);
    }

    // Если все цифры нули
    if (digits.empty()) {
        digits.push_back(0);
        positive = true;
        decimalPoint = 0;
        return;
    }

    // Удаляем хвостовые нули в дробной части
    while (decimalDigits > 0 && digits.back() == 0) {
        digits.pop_back();
        decimalDigits--;
    }

    decimalPoint = decimalDigits;

    // Если число равно нулю, делаем его положительным
    if (digits.size() == 1 && digits[0] == 0) {
        positive = true;
    }
}

void LongDouble::removeLeadingZeros() {
    size_t leadingZeros = 0;
    int wholeDigits = digits.size() - decimalPoint;

    // Удаляем нули только из целой части
    while (leadingZeros < wholeDigits && digits[leadingZeros] == 0) {
        leadingZeros++;
    }

    if (leadingZeros > 0) {
        digits.erase(digits.begin(), digits.begin() + leadingZeros);
    }

    if (digits.empty()) {
        digits.push_back(0);
        positive = true;
        decimalPoint = 0;
    }
}

void LongDouble::removeTrailingZeros() {
    while (decimalPoint > 0 && !digits.empty() && digits.back() == 0) {
        digits.pop_back();
        decimalPoint--;
    }

    if (digits.empty()) {
        digits.push_back(0);
        positive = true;
        decimalPoint = 0;
    }
}

void LongDouble::normalize() {
    removeLeadingZeros();
    removeTrailingZeros();
}

QString LongDouble::toQString() const {
    return QString::fromStdString(toString());
}

std::string LongDouble::toString() const {
    if (digits.empty()) {
        return "0";
    }

    std::string result;

    if (!positive) {
        result += '-';
    }

    int wholeDigits = digits.size() - decimalPoint;

    // Если целая часть пуста
    if (wholeDigits <= 0) {
        result += '0';
    } else {
        for (int i = 0; i < wholeDigits; ++i) {
            result += static_cast<char>('0' + digits[i]);
        }
    }

    // Добавляем дробную часть, если есть
    if (decimalPoint > 0) {
        result += '.';
        for (int i = wholeDigits; i < digits.size(); ++i) {
            result += static_cast<char>('0' + digits[i]);
        }
    }

    return result;
}

double LongDouble::toDouble() const {
    std::string str = toString();
    try {
        return std::stod(str);
    } catch (...) {
        return 0.0;
    }
}

bool LongDouble::isZero() const {
    return digits.size() == 1 && digits[0] == 0;
}

bool LongDouble::isPositive() const {
    return positive;
}

LongDouble LongDouble::operator-() const {
    LongDouble result = *this;
    if (!isZero()) {
        result.positive = !result.positive;
    }
    return result;
}

bool LongDouble::operator==(const LongDouble& other) const {
    if (positive != other.positive) return false;
    if (isZero() && other.isZero()) return true;

    LongDouble a = *this;
    LongDouble b = other;
    alignDecimalPoints(a, b);

    return a.digits == b.digits;
}

bool LongDouble::operator!=(const LongDouble& other) const {
    return !(*this == other);
}

bool LongDouble::absoluteLess(const LongDouble& a, const LongDouble& b) {
    LongDouble tempA = a;
    LongDouble tempB = b;
    alignDecimalPoints(tempA, tempB);

    if (tempA.digits.size() != tempB.digits.size()) {
        return tempA.digits.size() < tempB.digits.size();
    }

    for (size_t i = 0; i < tempA.digits.size(); ++i) {
        if (tempA.digits[i] != tempB.digits[i]) {
            return tempA.digits[i] < tempB.digits[i];
        }
    }

    return false;
}

bool LongDouble::absoluteEqual(const LongDouble& a, const LongDouble& b) {
    LongDouble tempA = a;
    LongDouble tempB = b;
    alignDecimalPoints(tempA, tempB);

    return tempA.digits == tempB.digits;
}

bool LongDouble::operator<(const LongDouble& other) const {
    if (positive != other.positive) {
        return !positive;
    }

    if (positive) {
        return absoluteLess(*this, other);
    } else {
        return absoluteLess(other, *this);
    }
}

bool LongDouble::operator>(const LongDouble& other) const {
    return other < *this;
}

bool LongDouble::operator<=(const LongDouble& other) const {
    return !(other < *this);
}

bool LongDouble::operator>=(const LongDouble& other) const {
    return !(*this < other);
}

void LongDouble::alignDecimalPoints(LongDouble& a, LongDouble& b) {
    int maxDecimal = std::max(a.decimalPoint, b.decimalPoint);

    // Добавляем нули в дробную часть
    while (a.decimalPoint < maxDecimal) {
        a.digits.push_back(0);
        a.decimalPoint++;
    }

    while (b.decimalPoint < maxDecimal) {
        b.digits.push_back(0);
        b.decimalPoint++;
    }

    // Выравниваем целую часть
    int aWhole = a.digits.size() - a.decimalPoint;
    int bWhole = b.digits.size() - b.decimalPoint;
    int maxWhole = std::max(aWhole, bWhole);

    // Добавляем нули в начало целой части
    std::vector<int> newA, newB;
    newA.resize(maxWhole - aWhole, 0);
    newA.insert(newA.end(), a.digits.begin(), a.digits.end());

    newB.resize(maxWhole - bWhole, 0);
    newB.insert(newB.end(), b.digits.begin(), b.digits.end());

    a.digits = newA;
    b.digits = newB;
}

LongDouble LongDouble::addAbsoluteValues(const LongDouble& a, const LongDouble& b) {
    LongDouble result;
    LongDouble tempA = a;
    LongDouble tempB = b;

    alignDecimalPoints(tempA, tempB);

    result.digits.clear();
    result.decimalPoint = tempA.decimalPoint;

    int carry = 0;
    size_t maxSize = std::max(tempA.digits.size(), tempB.digits.size());

    for (size_t i = 0; i < maxSize || carry; ++i) {
        int digitA = (i < tempA.digits.size()) ? tempA.digits[tempA.digits.size() - 1 - i] : 0;
        int digitB = (i < tempB.digits.size()) ? tempB.digits[tempB.digits.size() - 1 - i] : 0;

        int sum = digitA + digitB + carry;
        result.digits.insert(result.digits.begin(), sum % 10);
        carry = sum / 10;
    }

    result.normalize();
    return result;
}

LongDouble LongDouble::subtractAbsoluteValues(const LongDouble& a, const LongDouble& b) {
    LongDouble result;

    if (absoluteEqual(a, b)) {
        result.digits = {0};
        result.positive = true;
        result.decimalPoint = 0;
        return result;
    }

    bool resultPositive = !absoluteLess(a, b);
    LongDouble larger = resultPositive ? a : b;
    LongDouble smaller = resultPositive ? b : a;

    alignDecimalPoints(larger, smaller);

    result.digits.clear();
    result.decimalPoint = larger.decimalPoint;
    result.positive = resultPositive;

    int borrow = 0;

    for (int i = larger.digits.size() - 1; i >= 0; --i) {
        int digitLarger = larger.digits[i];
        int digitSmaller = (i < smaller.digits.size()) ? smaller.digits[i] : 0;

        digitLarger -= borrow;

        if (digitLarger < digitSmaller) {
            digitLarger += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.insert(result.digits.begin(), digitLarger - digitSmaller);
    }

    result.normalize();
    return result;
}

LongDouble LongDouble::operator+(const LongDouble& other) const {
    if (positive == other.positive) {
        LongDouble result = addAbsoluteValues(*this, other);
        result.positive = positive;
        result.normalize();
        return result;
    } else {
        // Разные знаки - это вычитание
        if (positive) {
            // this + (-other) = this - |other|
            return *this - (-other);
        } else {
            // (-this) + other = other - |this|
            return other - (-*this);
        }
    }
}

LongDouble LongDouble::operator-(const LongDouble& other) const {
    if (positive != other.positive) {
        // Разные знаки - это сложение
        LongDouble result = addAbsoluteValues(*this, other);
        result.positive = positive;
        result.normalize();
        return result;
    } else {
        // Одинаковые знаки - вычитание абсолютных значений
        LongDouble result = subtractAbsoluteValues(*this, other);

        if (positive) {
            // Оба положительные
            result.positive = !absoluteLess(*this, other);
        } else {
            // Оба отрицательные
            result.positive = absoluteLess(*this, other);
        }

        result.normalize();

        // Если результат 0, делаем его положительным
        if (result.isZero()) {
            result.positive = true;
        }

        return result;
    }
}

LongDouble LongDouble::multiplyByDigit(int digit) const {
    LongDouble result;
    result.digits.clear();
    result.decimalPoint = decimalPoint;
    result.positive = true;

    int carry = 0;

    for (int i = digits.size() - 1; i >= 0; --i) {
        int product = digits[i] * digit + carry;
        result.digits.insert(result.digits.begin(), product % 10);
        carry = product / 10;
    }

    if (carry > 0) {
        result.digits.insert(result.digits.begin(), carry);
    }

    result.normalize();
    return result;
}

LongDouble LongDouble::shiftRight(int positions) const {
    LongDouble result = *this;
    result.decimalPoint += positions;

    // Добавляем нули в конец, если нужно
    while (result.decimalPoint > result.digits.size()) {
        result.digits.push_back(0);
    }

    result.normalize();
    return result;
}

LongDouble LongDouble::operator*(const LongDouble& other) const {
    LongDouble result;
    result.digits = {0};
    result.decimalPoint = 0;
    result.positive = (positive == other.positive);

    for (size_t i = 0; i < other.digits.size(); ++i) {
        int digit = other.digits[other.digits.size() - 1 - i];
        LongDouble partial = multiplyByDigit(digit);

        // Сдвигаем в зависимости от позиции цифры
        partial = partial.shiftRight(i);

        result = result + partial;
    }

    // Учитываем положение запятой
    result.decimalPoint = decimalPoint + other.decimalPoint;
    result.normalize();

    // Если результат 0, делаем положительным
    if (result.isZero()) {
        result.positive = true;
    }

    return result;
}

LongDouble LongDouble::operator/(const LongDouble& other) const {
    if (other.isZero()) {
        throw std::runtime_error("Division by zero");
    }

    // Простая реализация деления через умножение на 10 и вычитание
    // Для более точного деления нужна более сложная логика

    LongDouble dividend = *this;
    LongDouble divisor = other;
    dividend.positive = true;
    divisor.positive = true;

    // Определяем точность
    int precision = 20; // Количество знаков после запятой

    // Умножаем делимое на 10^precision
    for (int i = 0; i < precision; ++i) {
        dividend = dividend * LongDouble(10);
    }

    LongDouble result;
    result.digits.clear();
    result.decimalPoint = precision;
    result.positive = (positive == other.positive);

    // Выравниваем запятые
    alignDecimalPoints(dividend, divisor);

    // Простой алгоритм деления в столбик
    LongDouble current;
    current.digits = {0};
    current.decimalPoint = 0;

    for (size_t i = 0; i < dividend.digits.size(); ++i) {
        current.digits.push_back(dividend.digits[i]);
        current.removeLeadingZeros();

        int quotientDigit = 0;
        while (!absoluteLess(current, divisor)) {
            current = subtractAbsoluteValues(current, divisor);
            quotientDigit++;
        }

        result.digits.push_back(quotientDigit);
    }

    result.normalize();

    // Если результат 0, делаем положительным
    if (result.isZero()) {
        result.positive = true;
    }

    return result;
}
