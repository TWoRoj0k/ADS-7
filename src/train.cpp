// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (first == nullptr) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;
    countOp = 0;

    if (first->light) {
        first->light = false;
        int length = 1;
        Car* current = first;

        while (true) {
            for (int i = 0; i < length; i++) {
                current = current->next;
                countOp++;
            }
            bool found = !current->light;
            if (!found) {
                current->light = false;
            }
            for (int i = 0; i < length; i++) {
                current = current->prev;
                countOp++;
            }
            if (found) {
                return length;
            }
            length++;
        }
    } else {
        const Car* temp = first;
        int length = 0;
        do {
            temp = temp->next;
            countOp++;
            length++;
        } while (temp != first);
        // cppcheck-suppress constVariablePointer
        Car* current = first;
        do {
            current = current->prev;
            countOp++;
        } while (current != first);
        return length;
    }
}

int Train::getOpCount() {
    return countOp;
}
