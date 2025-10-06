/**
 *	Copyright (c) 2025 Wenchao Huang <physhuangwenchao@gmail.com>
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include <easywin32.h>

/*********************************************************************************
******************************    mouseEventTest    ******************************
*********************************************************************************/

/**
 *	@brief		Simple mouse event testing routine.
 *	@details	This function listens for mouse movement and click events.
 *	@note		Pressing the `Escape` key will end the test.
 */
void mouseEventTest(EzWindow & window)
{
	bool testFinished = false;

	// Mouse move callback: prints current position
	window.onMouseMove = [](int x, int y, EzMouseStateFlags stateFlags)
	{
		printf("Mouse pos: { %d, %d }, %s ¡ª press 'Esc' to finish.\n", x, y, easywin32::to_string(stateFlags).c_str());

		return 0;
	};

	// Mouse click callback: prints button and action info
	window.onMouseClick = [](EzMouseButton button, EzMouseAction action, EzMouseStateFlags stateFlags)
	{
		printf("%s, %s, %s.\n", easywin32::to_string(button), easywin32::to_string(action), easywin32::to_string(stateFlags).c_str());

		return 0;
	};

	// Mouse wheel scroll callback ¡ª prints scroll delta
	window.onWheelScroll = [](int dx, int dy, EzMouseStateFlags stateFlags)
	{
		if (dx != 0)
			printf("Mouse wheel scrolled horizontally: %d, %s.\n", dx, to_string(stateFlags).c_str());
		if (dy != 0)
			printf("Mouse wheel scrolled vertically: %d, %s.\n", dy, to_string(stateFlags).c_str());
		return 0;
	};

	// Keyboard callback: waits for Escape key to end the test
	window.onKeyboardPress = [&](EzKey key, EzKeyAction action)
	{
		if (key == EzKey::Escape && action == EzKeyAction::Press)
		{
			testFinished = true;
		}
		return 0; // handled
	};

	printf("Mouse event test started.\n");

	// Main event loop
	while (window.isOpen() && !testFinished)
	{
		window.waitProcessEvent();
	}

	printf("Mouse event test finished.\n\n");

	// Cleanup callbacks
	window.onKeyboardPress = nullptr;
	window.onWheelScroll = nullptr;
	window.onMouseClick = nullptr;
	window.onMouseMove = nullptr;
}