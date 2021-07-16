#pragma once

#ifdef _WIN32
	#include<Windows.h>
#endif

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define SPACE 0x20
#define KB_A 0x41
#define KB_a 0x61
#define	KB_B 0x42
#define	KB_b 0x62
#define	KB_C 0x43
#define	KB_c 0x63
#define	KB_D 0x44
#define	KB_d 0x64
#define	KB_E 0x45
#define	KB_e 0x65
#define KB_F 0x46
#define KB_f 0x66
#define KB_G 0x47
#define KB_g 0x67
#define KB_H 0x48
#define KB_h 0x68
#define KB_I 0x49
#define KB_i 0x69
#define KB_J 0x4A
#define KB_j 0x6A
#define KB_K 0x4B
#define KB_k 0x6B
#define KB_L 0x4C
#define KB_l 0x6C
#define KB_M 0x4D
#define KB_m 0x6D
#define KB_N 0x4E
#define KB_n 0x6E
#define KB_O 0x4F
#define KB_o 0x6F
#define KB_P 0x50
#define KB_p 0x70
#define KB_R 0x52
#define KB_r 0x72
#define KB_S 0x53
#define KB_s 0x73
#define KB_T 0x54
#define KB_t 0x74
#define KB_U 0x55
#define KB_u 0x75
#define KB_V 0x56
#define KB_v 0x76
#define KB_Z 0x5A
#define KB_z 0x7A
#define KB_X 0x58
#define KB_x 0x78
#define KB_Y 0x59
#define KB_y 0x79
#define KB_Q 0x51
#define KB_q 0x71

namespace kbi {
		bool isKeyHeld(GLFWwindow* wind, int key);

		bool isKeyToggled(GLFWwindow* wind, int key);

		int cursorX();

		int cursorY();
};