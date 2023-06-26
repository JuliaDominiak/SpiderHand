#pragma once

template <typename T>
class Filtered {
    private:
    T previous;
    bool initialized = false;
    float exp;
    public:
    Filtered(float exp, T initial) {
        this->exp = exp;
        this->previous = initial;
        this->initialized = true;
    }
    Filtered(float exp) {
        this->exp = exp;
    }
    Filtered() {
        this->exp = 0.8;
    }
    T operator= (T value) {
        if (!initialized) {
            this->previous = value;
            this->initialized = true;
            return this->previous;
        }
        this->previous = this->exp * value + (1 - this->exp) * this->previous;
        return this->previous;
    }
    T get() {
        return this->previous;
    }
};