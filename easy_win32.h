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
 * 
 *	Repo URL: https://github.com/WenchaoHuang/EasyWin32.git
 */
#pragma once

// C headers
#include <assert.h>
#include <Windows.h>

// C++ headers
#include <string>
#include <functional>

/*********************************************************************************
***************************    Forward Declarations    ***************************
*********************************************************************************/

namespace easy_win32
{
	class Window;

	enum class Style
	{
		Popup,
		Overlapped,
	};

	// Virtual-key codes used by the system.
	enum class Key
	{
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',

		Num0 = '0',
		Num1 = '1',
		Num2 = '2',
		Num3 = '3',
		Num4 = '4',
		Num5 = '5',
		Num6 = '6',
		Num7 = '7',
		Num8 = '8',
		Num9 = '9',

		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		F13 = VK_F13,
		F14 = VK_F14,
		F15 = VK_F15,
		F16 = VK_F16,
		F17 = VK_F17,
		F18 = VK_F18,
		F19 = VK_F19,
		F20 = VK_F20,
		F21 = VK_F21,
		F22 = VK_F22,
		F23 = VK_F23,
		F24 = VK_F24,

		Pause = VK_PAUSE,
		ScrollLock = VK_SCROLL,
		PrintScreen = VK_SNAPSHOT,

		End = VK_END,
		Home = VK_HOME,
		Insert = VK_INSERT,
		Delete = VK_DELETE,
		PageUp = VK_PRIOR,
		PageDown = VK_NEXT,

		Up = VK_UP,
		Down = VK_DOWN,
		Left = VK_LEFT,
		Right = VK_RIGHT,

		Tab = VK_TAB,
		Alt = VK_MENU,
		Space = VK_SPACE,
		Clear = VK_CLEAR,
		Shift = VK_SHIFT,
		Enter = VK_RETURN,
		Escape = VK_ESCAPE,
		Control = VK_CONTROL,
		CapLock = VK_CAPITAL,
		BackSpace = VK_BACK,

		NumLock = VK_NUMLOCK,
		NumPad0 = VK_NUMPAD0,
		NumPad1 = VK_NUMPAD1,
		NumPad2 = VK_NUMPAD2,
		NumPad3 = VK_NUMPAD3,
		NumPad4 = VK_NUMPAD4,
		NumPad5 = VK_NUMPAD5,
		NumPad6 = VK_NUMPAD6,
		NumPad7 = VK_NUMPAD7,
		NumPad8 = VK_NUMPAD8,
		NumPad9 = VK_NUMPAD9,

		Add = VK_ADD,
		Divide = VK_DIVIDE,
		Decimal = VK_DECIMAL,
		Subtract = VK_SUBTRACT,
		Multiply = VK_MULTIPLY,

		VolumeUp = VK_VOLUME_UP,
		VolumeMute = VK_VOLUME_MUTE,
		VolumeDown = VK_VOLUME_DOWN,

		MediaStop = VK_MEDIA_STOP,
		MediaPlayPause = VK_MEDIA_PLAY_PAUSE,
		MediaNextTrack = VK_MEDIA_NEXT_TRACK,
		MediaPrevTrack = VK_MEDIA_PREV_TRACK,

		LaunchMail = VK_LAUNCH_MAIL,
		LaunchApp1 = VK_LAUNCH_APP1,
		LaunchApp2 = VK_LAUNCH_APP2,
		LaunchMediaSelect = VK_LAUNCH_MEDIA_SELECT,

		BrowserHome = VK_BROWSER_HOME,
		BrowserStop = VK_BROWSER_STOP,
		BrowserBack = VK_BROWSER_BACK,
		BrowserSearch = VK_BROWSER_SEARCH,
		BrowserForward = VK_BROWSER_FORWARD,
		BrowserRefresh = VK_BROWSER_REFRESH,
		BrowserFavorites = VK_BROWSER_FAVORITES,
	};


	// Mouse button tags.
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		XButton1,
		XButton2,
	};


	// Mouse state bits.
	enum MouseStateBits
	{
		Left		= MK_LBUTTON,
		Right		= MK_RBUTTON,
		Middle		= MK_MBUTTON,
		XButton1	= MK_XBUTTON1,
		XButton2	= MK_XBUTTON2,
		Shift		= MK_SHIFT,
		Ctrl		= MK_CONTROL,
	};


	// Type of mouse action.
	enum class MouseAction
	{
		Up				= 0,
		Down			= 1,
		DoubleClick		= 2,
	};


	// Type of keyboard action.
	enum class KeyAction
	{
		Press,
		Repeat,
		Release,
	};


	//	Predefined cursors of Windows OS.
	enum class Cursor : uint64_t
	{
		None			= (uint64_t)IDC_NO,
		Wait			= (uint64_t)IDC_WAIT,
		Hand			= (uint64_t)IDC_HAND,
		Help			= (uint64_t)IDC_HELP,
		Arrow			= (uint64_t)IDC_ARROW,
		Cross			= (uint64_t)IDC_CROSS,
		IBeam			= (uint64_t)IDC_IBEAM,
		SizeWE			= (uint64_t)IDC_SIZEWE,
		SizeNS			= (uint64_t)IDC_SIZENS,
		SizeAll			= (uint64_t)IDC_SIZEALL,
		UpArrow			= (uint64_t)IDC_UPARROW,
		SizeNWSE		= (uint64_t)IDC_SIZENWSE,
		SizeNESW		= (uint64_t)IDC_SIZENESW,
		AppStarting		= (uint64_t)IDC_APPSTARTING,
	};

#ifdef UNICODE
	using string_type = std::wstring;
#else
	using string_type = std::string;
#endif
}

using EzKey = easy_win32::Key;
using EzStyle = easy_win32::Style;
using EzWindow = easy_win32::Window;
using EzCursor = easy_win32::Cursor;
using EzKeyAction = easy_win32::KeyAction;
using EzMouseAction = easy_win32::MouseAction;
using EzMouseButton = easy_win32::MouseButton;

/*********************************************************************************
**********************************    Window    **********************************
*********************************************************************************/

/**
 *	@brief		
 */
class easy_win32::Window
{

public:

	Window() = default;

	Window(const Window&) = delete;

	void operator=(const Window&) = delete;

	~Window() { this->Close(); }

public:

	/**
	 *	@brief			
	 */
	void Open();


	/**
	 *	@brief		
	 */
	void Close()
	{
		if (m_hWnd != nullptr)
		{
			::DestroyWindow(m_hWnd);

			m_hWnd = nullptr;
		}
	}

public:

	//!	@brief	Returns the native handle of the win32 window.
	HWND NativeHandle() { return m_hWnd; }

	//!	@brief	Whether the specified window handle identifies an existing window (opened).	
	bool IsOpen() const { return ::IsWindow(m_hWnd); }

	//!	@brief	Whether the window is minimized.
	bool IsMinimized() const { return ::IsIconic(m_hWnd); }

	//!	@brief	Whether the window is maximized.
	bool IsMaximized() const { return ::IsZoomed(m_hWnd); }

	//!	@brief	Whether the windows is focused.
	bool IsFocused() const { return ::GetFocus() == m_hWnd; }

	//!	@brief	Checks if the window is currently marked as visible.
	bool IsVisible() const { return ::IsWindowVisible(m_hWnd) != FALSE; }

	//!	@brief	Whether the windows is the foreground (active) window.
	bool IsForeground() const { return ::GetForegroundWindow() == m_hWnd; }

public:

	//!	@brief	Bring the window to front and set input focus.
	void SetFocus() { ::SetFocus(m_hWnd); }

	//!	@brief	Hide the window.
	void Hide() { ::ShowWindow(m_hWnd, SW_HIDE); }

	//!	@brief	Bring the window to the top of the Z order.
	void BringToTop() { ::BringWindowToTop(m_hWnd); }

	//!	@brief	Show the window.
	void Show() { ::ShowWindow(m_hWnd, SW_SHOWNORMAL); }

	//!	@brief	Displays or hides the cursor.
	void ShowCursor(bool bShow) { ::ShowCursor(bShow); }

	//!	@brief	Foreground the window.
	void SetForeground() { ::SetForegroundWindow(m_hWnd); }

	//!	@brief	Maximized the window.
	void Maximize() { ::ShowWindow(m_hWnd, SW_SHOWMAXIMIZED); }

	//!	@brief	Minimized the window.
	void Minimize() { ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED); }

	//!	@brief	Enables or disables mouse and keyboard input to the specified window.
	void EnableInput(bool bEnable) { ::EnableWindow(m_hWnd, bEnable); }

	//!	@brief	Creates a timer with the specified time-out value.
	void SetTimer(unsigned int millisecond) { ::SetTimer(m_hWnd, 1, millisecond, NULL); }

	//!	@brief	Specify the cursor shape, must be called from the main thread.
	void SetCursor(Cursor cursor)
	{
	#ifdef UNICODE
		::SetCursor(::LoadCursor(NULL, (LPCWSTR)cursor));
	#else
		::SetCursor(::LoadCursor(NULL, (LPCSTR)cursor));
	#endif
	}

public:

	/**
	 *	@brief		Sets the window title text.
	 *	@details	Updates the internal title string and, if the window has already been
	 *				created, also updates the actual Win32 window title using SetWindowText().
	 *	@note		If the window has not been created yet (m_hWnd == nullptr), only
	 *				the internal title string is updated. The title will be applied
	 *				once the window is created.
	 */
	void SetTitle(string_type title)
	{
		if (m_title != title)
		{
			::SetWindowText(m_hWnd, title.c_str());

			m_title = title;
		}
	}


	/**
	 *	@brief		Returns the window title text.
	 */
	const string_type & GetTitle() const { return m_title; }

public:

	void SetStyle(Style style);

	void SetPos(int left, int top, int right, int bottom);

public:

	/**
	 *	@brief		Waits for and processes the next window message.
	 *	@details	This call will block until a new message is available in the queue for this window.
	 *				It retrieves the message with `GetMessage`, translates it (e.g. converts virtual-key
	 *				messages into character messages), and dispatches it to the window procedure.
	 */
	void WaitProcessEvent()
	{
		if (m_hWnd != nullptr)	
		{
			MSG uMsg = {};

			if (::GetMessage(&uMsg, m_hWnd, 0, 0))
			{
				::TranslateMessage(&uMsg);

				::DispatchMessage(&uMsg);
			};
		}
	}


	/**
	 *	@brief		Waits for and processes the next message for all windows belonging to the current thread.
	 *	@details	This function blocks until a message is available in the message queue of the
	 *				current thread (regardless of which window it belongs to).
	 *	@note		Unlike per-window message processing, passing `nullptr` as `hWnd` allows
	 *				messages for any window in this thread to be retrieved.
	 */
	static void WaitProcessThreadWindows()
	{
		MSG uMsg = {};

		if (::GetMessage(&uMsg, nullptr, 0, 0))
		{
			::TranslateMessage(&uMsg);

			::DispatchMessage(&uMsg);
		};
	}


	/**
	 *	@brief		Processes a single pending window message, if available.
	 *	@details	Uses `PeekMessage` to check for a message in the queue for this window.
	 *				If a message exists, it is translated and dispatched to the window procedure.
	 *	@return		`true` if a message was processed, `false` if no messages were pending.
	 */
	bool ProcessEvent()
	{
		if (m_hWnd != nullptr)
		{
			MSG uMsg = {};

			if (::PeekMessage(&uMsg, m_hWnd, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&uMsg);

				::DispatchMessage(&uMsg);

				return true;
			};
		}

		return false;
	}


	/**
	 *	@brief		Processes a single pending message for all windows belonging to the current thread, if any.
	 *	@details	Uses `PeekMessage` with hWnd set to `nullptr` to check for messages in the message queue
	 *				of the current thread. If a message exists, it is translated and dispatched
	 *				to the appropriate window procedure.
	 *	@return		`true` if a message was processed, `false` if no messages were pending.
	 *	@note		Unlike per-window processing, passing `nullptr` as `hWnd` retrieves messages
	 *				for any window in this thread.
	 */
	static bool ProcessThreadWindows()
	{
		MSG uMsg = {};

		if (::PeekMessage(&uMsg, nullptr, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&uMsg);

			::DispatchMessage(&uMsg);

			return true;
		};

		return false;
	}

private:

	RECT AdjustWindowRect() const;

	static LRESULT Procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

public:

	/**
	 *	@brief		User-defined callback functions, called when triggled and if defined.
	 *	@retval		0 - If the event is fully handled by the user callback.
	 *	@retval		1 - If the event should continue to be dispatched (e.g., to DefWindowProc).
	 */
	std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>					forwardMessage;		// Custom forwarder for any window message before default handling.
	std::function<LRESULT(wchar_t)>										onInputCharacter;	// Called when a character input (WM_CHAR, WM_SYSCHAR, WM_UNICHAR) is received.
	std::function<LRESULT()>											onKillFocus;		// Called when the window loses focus (WM_KILLFOCUS).
	std::function<LRESULT()>											onSetFocus;			// Called when the window gains focus (WM_SETFOCUS).
	std::function<LRESULT()>											onEnterMove;		// Called when the user starts moving or resizing the window(WM_ENTERSIZEMOVE).
	std::function<LRESULT()>											onExitMove;			// Called when the user finishes moving or resizing the window (WM_EXITSIZEMOVE).
	std::function<LRESULT()>											onTimer;			// Called when a timer event occurs (WM_TIMER).
	std::function<LRESULT()>											onClose;			// Called when the window is about to close (WM_CLOSE).
	std::function<LRESULT(int w, int h)>								onResize;			// Called when the window is resized (WM_SIZE).
	std::function<LRESULT(int x, int y)>								onMove;				// Called when the window is moved (WM_MOVE).
	std::function<LRESULT(int x, int y, MouseStateBits)>				onMouseMove;		// Called when the mouse is moved (WM_MOUSEMOVE).
	std::function<LRESULT(int dx, int dy, MouseStateBits)>				onWheelScroll;		// Called when the mouse wheel is scrolled (WM_MOUSEWHEEL / WM_MOUSEHWHEEL).
	std::function<LRESULT(MouseButton, MouseAction, MouseStateBits)>	onMouseClick;		// Called when a mouse button event occurs (down, up, or double click).
	std::function<LRESULT(Key, KeyAction)>								onKeyboardPress;	// Called when a key is pressed, released, or repeated (WM_KEYDOWN/WM_KEYUP).

private:

	HWND				m_hWnd = nullptr;
	Style				m_style = Style::Overlapped;
	RECT				m_bounds = { 100, 100, 800, 600 };
#ifdef UNICODE
	string_type			m_title = L"EasyWin32";
#else
	string_type			m_title = "EasyWin32";
#endif
};

/*********************************************************************************
******************************    Implementation    ******************************
*********************************************************************************/

#ifdef EZWIN32_IMPLEMENTATION

#include <windowsx.h>
#undef IsMinimized
#undef IsMaximized

/**
 *	@brief		Static window procedure for message dispatching.
 *	@details	This function is registered with the Win32 API as the window procedure
 *				for the Window class. It handles core messages (e.g., `WM_CREATE`, `WM_DESTROY`),
 *				associates HWND handles with Window instances, and forwards other messages to user-defined callbacks stored in the Window object.
 *	@param[in]	hWnd - Handle to the window receiving the message.
 *	@param[in]	uMsg - The message identifier (e.g., `WM_CREATE`, `WM_SIZE`, `WM_KEYDOWN`).
 *	@param[in]	wParam - Additional message-specific information.
 *	@param[in]	lParam - Additional message-specific information.
 *	@return		The result of message processing. If the message is not handled, the result of `DefWindowProc()` is returned.
 *	@note
 *		- On `WM_CREATE`, the Window pointer passed via lpCreateParams is stored in the window's user data slot for later retrieval.
 *		- On `WM_DESTROY`, a quit message is posted to end the application loop.
 *		- For other messages, the stored Window pointer is used to dispatch events to registered callbacks (e.g., onClose, onResize, onMouseClick).
 */
LRESULT easy_win32::Window::Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)		//	Retrieve the use pointer
	{
		CREATESTRUCT * createStrcut = reinterpret_cast<CREATESTRUCT*>(lParam);

		auto window = reinterpret_cast<Window*>(createStrcut->lpCreateParams);

		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
	}
	else if (uMsg == WM_NCCALCSIZE)
	{
	//	NCCALCSIZE_PARAMS * sizeParams = (NCCALCSIZE_PARAMS*)lParam;

	}
	else if (uMsg == WM_DESTROY)	//	Handle window destruction
	{
		::PostQuitMessage(0);		//	Post a quit message to end the application message loop
		
		return 0;	//	Message handled
	}

	//	Retrieve the stored Window* from the window's user data
	LONG_PTR ptr = ::GetWindowLongPtr(hWnd, GWLP_USERDATA);

	auto window = reinterpret_cast<Window*>(ptr);

	if (window != nullptr)
	{
		LRESULT result = 1;

		//	Forward message to custom handler if defined
		if (window->forwardMessage)
		{
			result = window->forwardMessage(hWnd, uMsg, wParam, lParam);

			if (result == 0)
				return result;
		}

		//	Dispatch standard messages to callbacks
		switch (uMsg)
		{
			case WM_CLOSE:			if (window->onClose)			result = window->onClose();			break;
			case WM_TIMER:			if (window->onTimer)			result = window->onTimer();			break;
			case WM_SETFOCUS:		if (window->onSetFocus)			result = window->onSetFocus();		break;
			case WM_KILLFOCUS:		if (window->onKillFocus)		result = window->onKillFocus();		break;
			case WM_EXITSIZEMOVE:	if (window->onExitMove)			result = window->onExitMove();		break;
			case WM_ENTERSIZEMOVE:	if (window->onEnterMove)		result = window->onEnterMove();		break;

			case WM_CHAR:			if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;
			case WM_SYSCHAR:		if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;
			case WM_UNICHAR:		if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;

			case WM_MOVE:			if (window->onMove)				result = window->onMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));		break;
			case WM_SIZE:			if (window->onResize)			result = window->onResize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));		break;

			case WM_KEYUP:			if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), KeyAction::Release);		break;
			case WM_SYSKEYUP:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), KeyAction::Release);		break;

			case WM_KEYDOWN:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), (lParam & (1 << 30)) ? KeyAction::Repeat : KeyAction::Press);		break;
			case WM_SYSKEYDOWN:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), (lParam & (1 << 30)) ? KeyAction::Repeat : KeyAction::Press);		break;

			case WM_MOUSEMOVE:		if (window->onMouseMove)		result = window->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<MouseStateBits>(wParam & 127));				break;
			case WM_MOUSEWHEEL:		if (window->onWheelScroll)		result = window->onWheelScroll(0, static_cast<SHORT>(HIWORD(wParam)) / WHEEL_DELTA, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_MOUSEHWHEEL:	if (window->onWheelScroll)		result = window->onWheelScroll(static_cast<SHORT>(HIWORD(wParam)) / WHEEL_DELTA, 0, static_cast<MouseStateBits>(wParam & 127));		break;

			case WM_LBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::Up, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_RBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::Up, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_MBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::Up, static_cast<MouseStateBits>(wParam & 127));		break;

			case WM_LBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::Down, static_cast<MouseStateBits>(wParam & 127));			break;
			case WM_RBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::Down, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_MBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::Down, static_cast<MouseStateBits>(wParam & 127));		break;

			case WM_LBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::DoubleClick, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_RBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::DoubleClick, static_cast<MouseStateBits>(wParam & 127));		break;
			case WM_MBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::DoubleClick, static_cast<MouseStateBits>(wParam & 127));	break;

			case WM_XBUTTONUP:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONDBLCLK:
			{
				if (window->onMouseClick)
				{
					auto button = GET_XBUTTON_WPARAM(wParam);

					auto action = (uMsg == WM_XBUTTONUP) ? MouseAction::Up : (uMsg == WM_XBUTTONDOWN) ? MouseAction::Down : MouseAction::DoubleClick;

					if (button == XBUTTON1)
					{
						result = window->onMouseClick(MouseButton::XButton1, action, static_cast<MouseStateBits>(wParam & 127));
					}
					else if (button == XBUTTON2)
					{
						result = window->onMouseClick(MouseButton::XButton2, action, static_cast<MouseStateBits>(wParam & 127));
					}
				}

				break;
			}
		}

		if (result == 0)
			return result;
	}

	//	Default handling for unprocessed messages
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void easy_win32::Window::Open()
{
	if (::IsWindow(m_hWnd) != 0)		return;

	/**
	 *	@brief	Static window class wrapper for Win32 window registration.
	 * 
	 *	This struct inherits from `WNDCLASSEX` and is used to register a single
	 *	window class with the Win32 API. The class is automatically registered
	 *	upon construction and unregistered upon destruction. This ensures that
	 *	the registration occurs only once during the application's lifetime.
	 */
	static struct WindowClass : public WNDCLASSEX
	{
		bool isRegistered;

		WindowClass() : isRegistered(false)
		{
			cbSize			= sizeof(WNDCLASSEXW);
			style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			lpfnWndProc		= Window::Procedure;
			cbClsExtra		= 0;
			cbWndExtra		= 0;
			hInstance		= ::GetModuleHandle(NULL);
			hIcon			= ::LoadIcon(NULL, IDI_APPLICATION);
			hCursor			= NULL;
			hbrBackground	= (HBRUSH)::GetStockObject(NULL_BRUSH);
			lpszMenuName	= NULL;
		#ifdef UNICODE
			lpszClassName	= L"EasyWin32";
		#else
			lpszClassName	= "EasyWin32";
		#endif
			hIconSm			= ::LoadIcon(NULL, IDI_WINLOGO);
			isRegistered	= ::RegisterClassEx(this);
		}

		~WindowClass()
		{
			if (isRegistered)
			{
				::UnregisterClass(lpszClassName, hInstance);
			}
		}
	} s_win32Class;

	assert(s_win32Class.isRegistered);

	if (s_win32Class.isRegistered)
	{
		auto rect = this->AdjustWindowRect();

		DWORD dwStyle = (m_style == Style::Popup) ? WS_POPUPWINDOW : WS_OVERLAPPEDWINDOW;

		m_hWnd = ::CreateWindowEx(WS_EX_APPWINDOW, s_win32Class.lpszClassName, m_title.c_str(), dwStyle,
								  rect.left, rect.top, rect.right, rect.bottom, NULL, NULL, s_win32Class.hInstance,
								  this /* Additional application data */);
	}
}


RECT easy_win32::Window::AdjustWindowRect() const
{
	auto rect = m_bounds;

	DWORD dwStyle = (m_style == Style::Popup) ? WS_POPUPWINDOW : WS_OVERLAPPEDWINDOW;

	::AdjustWindowRectEx(&rect, dwStyle, FALSE, WS_EX_APPWINDOW);

	return rect;
}


void easy_win32::Window::SetStyle(Style style)
{
	if (m_style != style)
	{
		m_style = style;
	}
}

#endif