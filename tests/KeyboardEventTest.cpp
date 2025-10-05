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

#include <easy_win32.h>

/*********************************************************************************
****************************    KeyboardEventTest    *****************************
*********************************************************************************/

/**
 *	@brief		Simple keyboard event testing routine.
 *	@details	Listens for all key press, repeat, and release actions.
 *	@note		Pressing the `Escape` key will terminate the test.
 */
void KeyboardEventTest(EzWindow & window)
{
	bool testFinished = false;

	// Keyboard event callback
	window.onKeyboardPress = [&](EzKey key, EzKeyAction action)
	{
		printf("Key: %s, Action: %s\n", ToString(key), ToString(action));

		if (key == EzKey::Escape && action == EzKeyAction::Press)
		{
			testFinished = true;
		}
		return 0;	// message handled
	};

	printf("Keyboard event test started.\n");

	// Main event loop
	while (window.IsOpen() && !testFinished)
	{
		window.WaitProcessEvent();
	}

	printf("Keyboard event test finished.\n\n");

	// Cleanup
	window.onKeyboardPress = nullptr;
}