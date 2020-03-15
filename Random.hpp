#pragma once
#include <random>
#include <functional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

// https://codereview.stackexchange.com/questions/109260/seed-stdmt19937-from-stdrandom-device
class Random {
private:
    static std::seed_seq randomSeeds() { //Get a sequence of Otterrò una sequenza di 624 semi, che darò al mersenne_twister_engine per generare numeri
        unsigned random_data[std::mt19937::state_size]; //Da essere riempito da dati casuali
        std::random_device source;      //Risorsa quasi affidabile per la generazioni di numeri casuali. Lento
        std::generate(std::begin(random_data), std::end(random_data), std::ref(source));    //Riempio l'array
        return std::seed_seq(std::begin(random_data), std::end(random_data));   //Uso l'array per creare il seed
    }

public:
    template <typename type>
    static type getInt(type low, type high) {
        std::seed_seq semi = randomSeeds();
        std::mt19937 randomGenerator(semi);
        std::uniform_int_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }

    template <typename type>
    static type getReal(type low, type high) {
        std::seed_seq semi = randomSeeds();
        std::mt19937 randomGenerator(semi);
        std::uniform_real_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }
};