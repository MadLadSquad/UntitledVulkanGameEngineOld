// Keys.hpp
// Last update 3/6/2021 by Madman10K
#pragma once
#include <glfw3.h>

/**
 * @brief A namespace of keys to be used for input. Also includes mouse keys
 */
namespace Keys
{
    [[maybe_unused]] constexpr int UnknownKey = 349;
    [[maybe_unused]] constexpr int Space = 32;
    [[maybe_unused]] constexpr int Apostrophe = 39;
    [[maybe_unused]] constexpr int Comma = 44;
    [[maybe_unused]] constexpr int Minus = 45;
    [[maybe_unused]] constexpr int Period = 46;
    [[maybe_unused]] constexpr int Slash = 47;
    [[maybe_unused]] constexpr int Zero = 48;
    [[maybe_unused]] constexpr int One = 49;
    [[maybe_unused]] constexpr int Two = 50;
    [[maybe_unused]] constexpr int Three= 51;
    [[maybe_unused]] constexpr int Four = 52;
    [[maybe_unused]] constexpr int Five = 53;
    [[maybe_unused]] constexpr int Six = 54;
    [[maybe_unused]] constexpr int Seven = 55;
    [[maybe_unused]] constexpr int Eight = 56;
    [[maybe_unused]] constexpr int Nine = 57;
    [[maybe_unused]] constexpr int Semicolon = 59;
    [[maybe_unused]] constexpr int Equal = 61;
    [[maybe_unused]] constexpr int A = 65;
    [[maybe_unused]] constexpr int B = 66;
    [[maybe_unused]] constexpr int C = 67;
    [[maybe_unused]] constexpr int D = 68;
    [[maybe_unused]] constexpr int E = 69;
    [[maybe_unused]] constexpr int F = 70;
    [[maybe_unused]] constexpr int G = 71;
    [[maybe_unused]] constexpr int H = 72;
    [[maybe_unused]] constexpr int I = 73;
    [[maybe_unused]] constexpr int J = 74;
    [[maybe_unused]] constexpr int K = 75;
    [[maybe_unused]] constexpr int L = 76;
    [[maybe_unused]] constexpr int M = 77;
    [[maybe_unused]] constexpr int N = 78;
    [[maybe_unused]] constexpr int O = 79;
    [[maybe_unused]] constexpr int P = 80;
    [[maybe_unused]] constexpr int Q = 81;
    [[maybe_unused]] constexpr int R = 82;
    [[maybe_unused]] constexpr int S = 83;
    [[maybe_unused]] constexpr int T = 84;
    [[maybe_unused]] constexpr int U = 85;
    [[maybe_unused]] constexpr int V = 86;
    [[maybe_unused]] constexpr int W = 87;
    [[maybe_unused]] constexpr int X = 88;
    [[maybe_unused]] constexpr int Y = 89;
    [[maybe_unused]] constexpr int Z = 90;
    [[maybe_unused]] constexpr int LeftBracket = 91;
    [[maybe_unused]] constexpr int Backslash = 92;
    [[maybe_unused]] constexpr int RightBracket = 93;
    [[maybe_unused]] constexpr int GraveAccent = 96;
    [[maybe_unused]] constexpr int WorldOne = 161;
    [[maybe_unused]] constexpr int WorldTwo = 162;
    [[maybe_unused]] constexpr int Escape = 256;
    [[maybe_unused]] constexpr int Enter = 257;
    [[maybe_unused]] constexpr int Tab = 258;
    [[maybe_unused]] constexpr int Backspace = 259;
    [[maybe_unused]] constexpr int Insert = 260;
    [[maybe_unused]] constexpr int Delete = 261;
    [[maybe_unused]] constexpr int RightArrow = 262;
    [[maybe_unused]] constexpr int LeftArrow = 263;
    [[maybe_unused]] constexpr int DownArror = 264;
    [[maybe_unused]] constexpr int UpArrow = 265;
    [[maybe_unused]] constexpr int PageUp = 266;
    [[maybe_unused]] constexpr int PageDown = 267;
    [[maybe_unused]] constexpr int Home = 268;
    [[maybe_unused]] constexpr int End = 269;
    [[maybe_unused]] constexpr int CapsLock = 280;
    [[maybe_unused]] constexpr int ScrollLock = 281;
    [[maybe_unused]] constexpr int NumLock = 282;
    [[maybe_unused]] constexpr int PrintSceen = 283;
    [[maybe_unused]] constexpr int Pause = 284;
    [[maybe_unused]] constexpr int F1 = 290;
    [[maybe_unused]] constexpr int F2 = 291;
    [[maybe_unused]] constexpr int F3 = 292;
    [[maybe_unused]] constexpr int F4 = 293;
    [[maybe_unused]] constexpr int F5 = 294;
    [[maybe_unused]] constexpr int F6 = 295;
    [[maybe_unused]] constexpr int F7 = 296;
    [[maybe_unused]] constexpr int F8 = 297;
    [[maybe_unused]] constexpr int F9 = 298;
    [[maybe_unused]] constexpr int F10 = 299;
    [[maybe_unused]] constexpr int F11 = 300;
    [[maybe_unused]] constexpr int F12 = 301;
    [[maybe_unused]] constexpr int F13 = 302;
    [[maybe_unused]] constexpr int F14 = 303;
    [[maybe_unused]] constexpr int F15 = 304;
    [[maybe_unused]] constexpr int F16 = 305;
    [[maybe_unused]] constexpr int F17 = 306;
    [[maybe_unused]] constexpr int F18 = 307;
    [[maybe_unused]] constexpr int F19 = 308;
    [[maybe_unused]] constexpr int F20 = 309;
    [[maybe_unused]] constexpr int F21 = 310;
    [[maybe_unused]] constexpr int F22 = 311;
    [[maybe_unused]] constexpr int F23 = 312;
    [[maybe_unused]] constexpr int F24 = 313;
    [[maybe_unused]] constexpr int F25 = 314;
    [[maybe_unused]] constexpr int NumPadZero = 320;
    [[maybe_unused]] constexpr int NumPadOne = 321;
    [[maybe_unused]] constexpr int NumPadTwo = 322;
    [[maybe_unused]] constexpr int NumPadThree = 323;
    [[maybe_unused]] constexpr int NumPadFour = 324;
    [[maybe_unused]] constexpr int NumPadFive = 325;
    [[maybe_unused]] constexpr int NumPadSix = 326;
    [[maybe_unused]] constexpr int NumPadSeven = 327;
    [[maybe_unused]] constexpr int NumPadEight = 328;
    [[maybe_unused]] constexpr int NumPadNine = 329;
    [[maybe_unused]] constexpr int NumPadDecimal = 330;
    [[maybe_unused]] constexpr int NumPadDivide = 331;
    [[maybe_unused]] constexpr int NumPadMultiply = 332;
    [[maybe_unused]] constexpr int NumPadSubstract = 333;
    [[maybe_unused]] constexpr int NumPadAdd = 334;
    [[maybe_unused]] constexpr int NumPadEnter = 335;
    [[maybe_unused]] constexpr int NumPadEqual = 336;
    [[maybe_unused]] constexpr int LeftShift= 340;
    [[maybe_unused]] constexpr int LeftControl = 341;
    [[maybe_unused]] constexpr int LeftAlt= 342;
    [[maybe_unused]] constexpr int LeftSuper = 343;
    [[maybe_unused]] constexpr int RightShift = 344;
    [[maybe_unused]] constexpr int RightControl = 345;
    [[maybe_unused]] constexpr int RightAlt = 346;
    [[maybe_unused]] constexpr int RightSuper = 347;
    [[maybe_unused]] constexpr int Menu = 348;

    [[maybe_unused]] constexpr int MouseButton1 = 0;
    [[maybe_unused]] constexpr int MouseButton2 = 1;
    [[maybe_unused]] constexpr int MouseButton3 = 2;
    [[maybe_unused]] constexpr int MouseButton4 = 3;
    [[maybe_unused]] constexpr int MouseButton5 = 4;
    [[maybe_unused]] constexpr int MouseButton6 = 5;
    [[maybe_unused]] constexpr int MouseButton7 = 6;
    [[maybe_unused]] constexpr int MouseButton8 = 7;
    [[maybe_unused]] constexpr int MouseButtonLast = 7;
    [[maybe_unused]] constexpr int MouseButtonLeft = 0;
    [[maybe_unused]] constexpr int MouseButtonRight = 1;
    [[maybe_unused]] constexpr int MouseButtonMiddle = 2;

    [[maybe_unused]] constexpr int MouseScrollUp = 0;
    [[maybe_unused]] constexpr int MouseScrollDown = 1;
    [[maybe_unused]] constexpr int MouseScrollRight = 2;
    [[maybe_unused]] constexpr int MouseScrollLeft = 3;

    [[maybe_unused]] constexpr int KeyPressedEvent = 1;
    [[maybe_unused]] constexpr int KeyReleasedEvent = 0;
    [[maybe_unused]] constexpr int KeyRepeatEvent = 2;
}

