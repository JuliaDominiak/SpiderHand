#pragma once

template <typename T>
class ExpFiltered {
    private:
    T previous;
    bool initialized = false;
    float exp;
    public:
    ExpFiltered(float exp, T initial) {
        this->exp = exp;
        this->previous = initial;
        this->initialized = true;
    }
    ExpFiltered(float exp) {
        this->exp = exp;
    }
    ExpFiltered() {
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
    operator T() const {
        return this->previous;
    }
};

template <typename T>
class FastFiltered {
    private:
    T previous;
    bool initialized = false;
    float eps;
    int direction = 0;
    public:
    FastFiltered(float eps, T initial) {
        this->eps = eps;
        this->previous = initial;
        this->initialized = true;
    }
    FastFiltered(float eps) {
        this->eps = eps;
    }
    FastFiltered() {
        this->eps = 5;
    }
    T operator= (T value) {
        if (!initialized) {
            this->previous = value;
            this->initialized = true;
            return this->previous;
        }
        if (value < this->previous + this->eps && value > this->previous - this->eps) {
            this->direction = 0;
            return this->previous;
        }
        if (this->direction == 0){
            this->direction = value > this->previous ? 1 : -1;
            return this->previous;
        }
        if ((value > this->previous ? 1 : -1) == this->direction) {
            this->previous = value;
            return this->previous;
        }
        this->direction = 0;
        return this->previous;
    }
    T get() {
        return this->previous;
    }
    operator T() const {
        return this->previous;
    }
};