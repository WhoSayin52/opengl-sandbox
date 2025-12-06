#include "input.hpp"

#include "camera.hpp"
#include "core.hpp"

#include <GLFW/glfw3.h>

#include<iostream>//delete

static void cursor_position_callback([[maybe_unused]] GLFWwindow* window, double x, double y);
static void scroll_callback([[maybe_unused]] GLFWwindow* window, double x_offset, double y_offset);

void init_input() {

	GLFWwindow* window{ game_state.window };
	Vector2 window_center{ game_state.window_width / 2, game_state.window_height / 2 };

	input_state = InputState{
		.mouse = MouseData{
			.lock_position = Vector2{window_center.x, window_center.y},
			.current_position = Vector2{window_center.x, window_center.y},
			.scroll_offset = Vector2{0.0}
		}
	};

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void input() {
	// checks and calls events
	glfwPollEvents();

	GLFWwindow* window = game_state.window;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	camera_process_movement(window);

	glfwSetCursorPos(window, input_state.mouse.lock_position.x, input_state.mouse.lock_position.y);
	input_state.mouse.current_position = input_state.mouse.lock_position;

	// reseting scroll offset, since scroll_callback wont be called if no scrolling is occurring 
	input_state.mouse.scroll_offset.x = 0.0;
	input_state.mouse.scroll_offset.y = 0.0;
}

static void cursor_position_callback([[maybe_unused]] GLFWwindow* window, double x, double y) {
	input_state.mouse.current_position.x = x;
	input_state.mouse.current_position.y = y;
}

static void scroll_callback([[maybe_unused]] GLFWwindow* window, double x_offset, double y_offset) {
	input_state.mouse.scroll_offset.x = x_offset;
	input_state.mouse.scroll_offset.y = y_offset;
}

