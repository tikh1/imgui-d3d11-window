#pragma once
#include <unordered_map>

class Globals {
public:
    bool active = true;
    char user_name[255] = "user";
    char pass_word[255] = "pass";
    int width = 400;
    int height = 300;
    float window_pos_x = 0.f;
    float window_pos_y = 0.f;
	POINTS position = { 0, 0 };
	ImVec2 screen_res = { 0, 0 };
};

inline Globals globals;
