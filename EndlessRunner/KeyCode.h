#pragma once
#include "SDL.h"

//The keycode class and function have been taken from Jerry's code

enum class KeyCode
{
	ESCAPE, SPACE, ENTER,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW,
	INVALID
};

KeyCode TranslateKeyCode(SDL_Keycode key);