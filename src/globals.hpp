#pragma once
#include <unordered_map>

class Globals {
public:
    bool active = true;
    char user_name[255] = "user";
    char pass_word[255] = "pass";
};

inline Globals globals;
