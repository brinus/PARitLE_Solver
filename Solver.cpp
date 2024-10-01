#include "Solver.hpp"

Solver::Solver() {
    Solver::LoadDict();
    lenRes_ = 10;
    return;
}

Solver::Solver(const std::string & path) {
    Solver::LoadDict(path);
    lenRes_ = 10;
    return;
}

Solver::~Solver() {
}

void Solver::Run(const int & nAttempts) {
    std::string guess;
    std::string values;
    for (int i = 0; i < nAttempts; ++i) {
        std::cout << " --- TENTATIVO " << i+1 << " ---" << std::endl;
        do {
            std::cout << "Inserire la parola: ";
            std::cin >> guess;
        } while (!Solver::CheckWord(guess));
        do {
            std::cout << "                    "; 
            std::cin >> values;
        } while (!Solver::CheckValues(values));

        Solver::UpdateGuess(guess, values);
        
        if (!Solver::Results(lenRes_)) {
            std::cout << "FINE!!!" << std::endl;
            break;
        }
    }
}

Solver & Solver::SetLenghtRes(const int & l) {
    if (l < 0) {
        std::cerr << "ERRORE: Lunghezza della lista di risposte invalida!" << std::endl;
        return *this;
    }
    lenRes_ = l;
    return *this;
}

void Solver::LoadDict(const std::string & path) {
    std::ifstream dict;
    dict.open(path, std::ifstream::in);
    std::string word;

    if (!dict.is_open()) {
        std::cerr << "ERRORE: Impossibile aprire il file!" << std::endl
                  << "Percorso del file: " << path << std::endl;
        return;
    }

    while (std::getline(dict, word))
        good_.push_back(word);
    
    std::cout << "Dizionario caricato con successo" << std::endl
              << "Percorso del file: " << path << std::endl;
    dict.close();
    return;
}

bool Solver::CheckWord(const std::string & word) {
    if (word.size() != 5) {
        std::cerr << "ERRORE: Lunghezza della parola errata!" << std::endl;
        std::cerr << "Parola inserita: " << word << std::endl;
        std::cerr << "Lunghezza consentita: 5" << std::endl;
        return 0;
    }

    auto it = std::find(good_.begin(), good_.end(), word);
    if (it == good_.end()) {
        std::cerr << "ERRORE: Parola non trovata nella lista di parole valide!" << std::endl;
        std::cerr << "Parola inserita: " << word << std::endl;
        return 0;
    }    
    return 1;
}

bool Solver::CheckValues(const std::string & values) {
    if (values.length() != 5) {
        return 0;
    }

    for (char c : values) {
        if (c != '0' && c != '1' && c != '2') {
            return 0;
        }
    }
    return 1;
}

void Solver::UpdateGuess(const std::string & guess, const std::string & values) {
    auto remove_from = std::remove_if(good_.begin(), good_.end(), 
            [this, guess, values](std::string word) {
                return !Solver::CheckGuess(word, guess, values);
            });
    good_.erase(remove_from, good_.end());
    return;
}

bool Solver::CheckGuess(const std::string & word, const std::string & guess, const std::string &values) {
    std::unordered_map<char, int> letter_count;

    for (int i = 0; i < 5; ++i) {
        if (values[i] == '2') {
            if (guess[i] != word[i]) {
                return 0;
            } else {
                ++letter_count[guess[i]];
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (values[i] == '1') {
            if (word[i] == guess[i] || word.find(guess[i]) == std::string::npos) {
                return 0;
            }
            ++letter_count[guess[i]];
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (values[i] == '0') {
            auto count = std::count(word.begin(), word.end(), guess[i]);
            if (letter_count[guess[i]] < count) {
                return 0;
            }
        }
    }
    return 1;
}

bool Solver::Results(const int & len) {
    auto goodSize = good_.size();
    std::cout << "Numero di parole rimaste: " << goodSize << std::endl;
    for (int i = 0; i < ((goodSize > len) ? len : goodSize); ++i) {
        std::cout << good_[i];
        if (goodSize > 1) {
            std::cout << ", ";
        }
    }   
    std::cout << std::endl << std::endl;
    return goodSize > 1;
}

