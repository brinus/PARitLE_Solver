#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#ifndef SOLVER_H_
#define SOLVER_H_

#define ATTEMPTS 6

class Solver {
    public:
        Solver();
        Solver(const std::string &);
        ~Solver();

        void Run(const int & nAttempts = ATTEMPTS);
        Solver & SetLenghtRes(const int &);

    private:
        void LoadDict(const std::string & path = "possible_word.txt");
        bool CheckWord(const std::string &);
        bool CheckValues(const std::string &);
        void UpdateGuess(const std::string &, const std::string &);
        bool Results(const int & len = 10);
        bool CheckGuess(const std::string &, const std::string &, const std::string &);

        std::vector<std::string> good_;
        int lenRes_;
};

#endif
