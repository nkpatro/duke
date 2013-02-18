/*
 * Window.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: Guillaume Chatelet
 */

#include "DukeWindow.h"

#include <duke/gl/GL.h>

using namespace std;

namespace duke {

static void glViewport(const Viewport &viewport) {
	::glViewport(viewport.offset.x, viewport.offset.y, viewport.dimension.x, viewport.dimension.y);
}

DukeWindow::DukeWindow(GLFWwindow *pWindow) :
		DukeGLFWWindow(pWindow), m_LeftButton(false) {
	mouseButtonCallback = bind(&DukeWindow::onMouseClick, this, placeholders::_1, placeholders::_2);
	mousePosCallback = bind(&DukeWindow::onMouseMove, this, placeholders::_1, placeholders::_2);
	scrollCallback = bind(&DukeWindow::onScroll, this, placeholders::_1, placeholders::_2);
	windowResizeCallback = bind(&DukeWindow::onWindowResize, this, placeholders::_1, placeholders::_2);
	charCallback = bind(&DukeWindow::onChar, this, placeholders::_1);
	keyCallback = bind(&DukeWindow::onKey, this, placeholders::_1, placeholders::_2);
}

void DukeWindow::onWindowResize(int width, int height) {
	::glViewport(0, 0, width, height);
	m_Dimension.x = width;
	m_Dimension.y = height;
}

void DukeWindow::onMouseMove(int x, int y) {
	auto previousPos = m_MousePos;
	m_MousePos.x = x;
	m_MousePos.y = m_Dimension.y - y;
	if (m_LeftButton)
		m_Pan += m_MousePos - previousPos;
}

void DukeWindow::onScroll(double x, double y) {
	m_Scroll.x += x;
	m_Scroll.y += y;
}

void DukeWindow::setScroll(glm::vec2 scroll) {
	m_Scroll = scroll;
}

void DukeWindow::setPan(glm::ivec2 pan) {
	m_Pan = pan;
}

void DukeWindow::onMouseClick(int buttonId, int buttonState) {
	if (buttonId == GLFW_MOUSE_BUTTON_LEFT)
		switch (buttonState) {
		case GLFW_PRESS:
			m_LeftButton = true;
			m_MouseDragStartPos = m_MousePos;
			break;
		case GLFW_RELEASE:
			m_LeftButton = false;
			m_MouseDragStartPos.x = m_MouseDragStartPos.y = 0;
			break;
		}
}

void DukeWindow::onChar(int unicodeCodePoint) {
	m_CharStrokes.push_back(unicodeCodePoint);
}

void DukeWindow::onKey(int key, int action) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		m_KeyStrokes.push_back(key);
}

const Viewport DukeWindow::useViewport(bool north, bool south, bool east, bool west) const {
	using namespace glm;
	assert(!(north && south));
	assert(!(east && west));
	const ivec2 halfDim(m_Dimension.x / 2, m_Dimension.y / 2);
	const ivec2 offset(east ? halfDim.x : 0, south ? halfDim.y : 0);
	const ivec2 dimension(east || west ? halfDim.x : m_Dimension.x, north || south ? halfDim.y : m_Dimension.y);
	const Viewport viewport(offset, dimension);
	glViewport(viewport);
	return viewport;
}

vector<int>& DukeWindow::getPendingChars() {
	return m_CharStrokes;
}
vector<int>& DukeWindow::getPendingKeys() {
	return m_KeyStrokes;
}

glm::ivec2 DukeWindow::getRelativeMousePos() const {
	return m_MousePos;
}

glm::ivec2 DukeWindow::getViewportMousePos(const Viewport& viewport) const {
	return m_MousePos - viewport.offset;
}

glm::ivec2 DukeWindow::getPanPos() const {
	return m_Pan;
}

glm::vec2 DukeWindow::getScrollPos() const {
	return m_Scroll;
}

int DukeWindow::glfwGetKey(int key) {
	return ::glfwGetKey(m_pWindow, key);
}

int DukeWindow::glfwGetWindowParam(int param) {
	return ::glfwGetWindowParam(m_pWindow, param);
}

void DukeWindow::glfwSwapBuffers() {
	::glfwSwapBuffers(m_pWindow);
}

void DukeWindow::makeContextCurrent() {
	::glfwMakeContextCurrent(m_pWindow);
	registerCallbacks();
}
}  // namespace duke
