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
 *	Repo URL: https://github.com/WenchaoHuang/easywin32.git
 */
#pragma once

// C headers
#include <assert.h>
#include <Windows.h>

// C++ headers
#include <string>
#include <functional>

/*********************************************************************************
********************************    EasyWin32    *********************************
*********************************************************************************/

namespace easywin32
{
	class Window;

#ifdef UNICODE
	using string_type = std::wstring;
#else
	using string_type = std::string;
#endif

	/*****************************************************************************
	********************************    Color    *********************************
	*****************************************************************************/

	//!	@brief	Represents an RGB color with 8-bit channels.
	struct Color
	{
		uint8_t	r;	//!< Red channel component (0¨C255)
		uint8_t g;	//!< Green channel component (0¨C255)
		uint8_t b;	//!< Blue channel component (0¨C255)
	};

	/*****************************************************************************
	***************************    Flags<EnumType>    ****************************
	*****************************************************************************/

	//!	@brief		A strongly-typed bit flag wrapper for enum classes.
	template<typename EnumType> struct Flags
	{
		static_assert(std::is_enum_v<EnumType>, "Flags<T>: T must be an enum type.");

		using Type = std::underlying_type_t<EnumType>;

		Type	flags;

		// Constructors
		constexpr Flags() noexcept : flags(0) {}
		constexpr Flags(Type value) noexcept : flags(value) {}
		constexpr Flags(EnumType value) noexcept : flags(static_cast<Type>(value)) {}

		// Bitwise OR
		constexpr Flags operator|(Flags rhs) const noexcept { return Flags(flags | rhs.flags); }
		constexpr Flags operator|(EnumType rhs) const noexcept { return Flags(flags | static_cast<Type>(rhs)); }
		constexpr Flags & operator|=(EnumType rhs) noexcept { flags |= static_cast<Type>(rhs); return *this; }
		constexpr Flags & operator|=(Flags rhs) noexcept { flags |= rhs.flags; return *this; }

		// Bitwise AND
		constexpr Flags operator&(Flags rhs) const noexcept { return Flags(flags & rhs.flags); }
		constexpr Flags operator&(EnumType rhs) const noexcept { return Flags(flags & static_cast<Type>(rhs)); }
		constexpr Flags & operator&=(EnumType rhs) noexcept { flags &= static_cast<Type>(rhs); return *this; }
		constexpr Flags & operator&=(Flags rhs) noexcept { flags &= rhs.flags; return *this; }

		// Bitwise XOR
		constexpr Flags operator^(Flags rhs) const noexcept { return Flags(flags ^ rhs.flags); }
		constexpr Flags & operator^=(Flags rhs) noexcept { flags ^= rhs.flags; return *this; }

		// Bitwise NOT
		constexpr Flags operator~() const noexcept { return Flags(~flags); }

		// Comparison
		constexpr bool operator==(Flags rhs) const noexcept { return flags == rhs.flags; }
		constexpr bool operator!=(Flags rhs) const noexcept { return flags != rhs.flags; }

		// Conversion
		constexpr operator bool() const noexcept { return flags != 0; }
		constexpr operator Type() const noexcept { return flags; }

		// Test
		constexpr bool has(EnumType bit) const noexcept { return (flags & static_cast<Type>(bit)) != 0; }
		constexpr bool none() const noexcept { return flags == 0; }
		constexpr bool any() const noexcept { return flags != 0; }

		// Clear
		constexpr void clear() noexcept { flags = 0; }
	};

	/**
	 *	@brief		Enables bitwise operators (|, &, ~) for a strongly-typed enum.
	 *	@details	This macro defines overloaded operators that allow using the enum as
	 *				bit flags through the `Flags<EnumType>` wrapper.
	 */
#define EZWIN32_ENABLE_ENUM_FLAGS(EnumType)										\
																				\
	constexpr Flags<EnumType> operator|(EnumType lhs, EnumType rhs) noexcept	\
	{																			\
		return Flags<EnumType>(lhs) | Flags<EnumType>(rhs);						\
	}																			\
	constexpr Flags<EnumType> operator&(EnumType lhs, EnumType rhs) noexcept	\
	{																			\
		return Flags<EnumType>(lhs) & Flags<EnumType>(rhs);						\
	}																			\
	constexpr Flags<EnumType> operator~(EnumType v) noexcept					\
	{																			\
		return ~Flags<EnumType>(v);												\
	}

	/*****************************************************************************
	********************************    Style    *********************************
	*****************************************************************************/

	/**
	 *	@brief	Standard window styles
	 *	@see	https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
	 */
	enum class Style : DWORD
	{
		Overlapped			= WS_OVERLAPPED,			//!< Standard top-level overlapped window
		Popup				= WS_POPUP,					//!< Popup window (mutually exclusive with Overlapped/Child)
		Child				= WS_CHILD,					//!< Child window (cannot have menu bar)
		Minimize			= WS_MINIMIZE,				//!< Initially minimized
		Visible				= WS_VISIBLE,				//!< Initially visible
		Disabled			= WS_DISABLED,				//!< Initially disabled
		ClipSiblings		= WS_CLIPSIBLINGS,			//!< Clips child windows relative to each other
		ClipChildren		= WS_CLIPCHILDREN,			//!< Excludes child areas when drawing parent
		Maximize			= WS_MAXIMIZE,				//!< Initially maximized
		Border				= WS_BORDER,				//!< Thin border
		DialogFrame			= WS_DLGFRAME,				//!< Dialog-style border (cannot have title bar)
		VScroll				= WS_VSCROLL,				//!< Vertical scroll bar
		HScroll				= WS_HSCROLL,				//!< Horizontal scroll bar
		SysMenu				= WS_SYSMENU,				//!< System menu (requires Caption)
		ThickFrame			= WS_THICKFRAME,			//!< Resizable border (size box)
		Group				= WS_GROUP,					//!< First control in a group (dialog navigation)
		TabStop				= WS_TABSTOP,				//!< Control can be focused using Tab key
		MinimizeBox			= WS_MINIMIZEBOX,			//!< Minimize button (requires SysMenu)
		MaximizeBox			= WS_MAXIMIZEBOX,			//!< Maximize button (requires SysMenu)
		Caption				= WS_CAPTION,				//!< Title bar (includes WS_BORDER)
		OverlappedWindow	= WS_OVERLAPPEDWINDOW,		//!< Common top-level window (Overlapped + Caption + SysMenu + ThickFrame + Min/Max boxes)
		PopupWindow			= WS_POPUPWINDOW,			//!< Popup + Border + SysMenu
		SizeBox				= WS_SIZEBOX,				//!< Same as WS_THICKFRAME
		Tiled				= WS_TILED,					//!< Same as WS_OVERLAPPED
		TiledWindow			= WS_TILEDWINDOW			//!< Same as WS_OVERLAPPEDWINDOW
	};

	//!	@brief	Enables bitwise operators (|, &, ~).
	EZWIN32_ENABLE_ENUM_FLAGS(Style);

	/*****************************************************************************
	*******************************    ExStyle    ********************************
	*****************************************************************************/

	/**
	 *	@brief	Extended window styles.
	 *	@see	https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
	 */
	enum class ExStyle : DWORD
	{
		AcceptFiles				= WS_EX_ACCEPTFILES,			//!< Accepts drag-drop files.
		AppWindow				= WS_EX_APPWINDOW,				//!< Forces top-level window onto taskbar when visible.
		ClientEdge				= WS_EX_CLIENTEDGE,				//!< Border with sunken edge.
		Composited				= WS_EX_COMPOSITED,				//!< Paints descendants bottom-to-top with double-buffering.
		ContextHelp				= WS_EX_CONTEXTHELP,			//!< Title bar question mark for help.
		ControlParent			= WS_EX_CONTROLPARENT,			//!< Enables dialog navigation for child windows.
		DlgModalFrame			= WS_EX_DLGMODALFRAME,			//!< Double border, optional title bar with WS_CAPTION.
		Layered					= WS_EX_LAYERED,				//!< Layered window, supports top-level and child windows (Windows 8+).
		LayoutRtl				= WS_EX_LAYOUTRTL,				//!< Right-edge origin for right-to-left languages.
		Left					= WS_EX_LEFT,					//!< Generic left-aligned properties (default).
		LeftScrollBar			= WS_EX_LEFTSCROLLBAR,			//!< Left-side scroll bar for right-to-left languages.
		LtrReading				= WS_EX_LTRREADING,				//!< Left-to-right text reading order (default).
		MdiChild				= WS_EX_MDICHILD,				//!< MDI child window.
		NoActivate				= WS_EX_NOACTIVATE,				//!< Non-foreground window, not on taskbar by default.
		NoInheritLayout			= WS_EX_NOINHERITLAYOUT,		//!< Does not pass layout to child windows.
		NoParentNotify			= WS_EX_NOPARENTNOTIFY,			//!< No WM_PARENTNOTIFY for child creation/destruction.
		NoRedirectionBitmap		= WS_EX_NOREDIRECTIONBITMAP,	//!< No redirection surface rendering.
		OverlappedWindow		= WS_EX_OVERLAPPEDWINDOW,		//!< Overlapped window (WINDOWEDGE | CLIENTEDGE).
		PaletteWindow			= WS_EX_PALETTEWINDOW,			//!< Palette window (WINDOWEDGE | TOOLWINDOW | TOPMOST).
		Right					= WS_EX_RIGHT,					//!< Right-aligned properties for right-to-left languages.
		RightScrollBar			= WS_EX_RIGHTSCROLLBAR,			//!< Right-side scroll bar (default).
		RtlReading				= WS_EX_RTLREADING,				//!< Right-to-left text reading order for supported languages.
		StaticEdge				= WS_EX_STATICEDGE,				//!< 3D border for non-interactive items.
		ToolWindow				= WS_EX_TOOLWINDOW,				//!< Floating toolbar, no taskbar/ALT+TAB.
		TopMost					= WS_EX_TOPMOST,				//!< Stays above non-topmost windows.
		Transparent				= WS_EX_TRANSPARENT,			//!< Delays painting until siblings are painted.
		WindowEdge				= WS_EX_WINDOWEDGE,				//!< Border with raised edge.
	};

	//!	@brief	Enables bitwise operators (|, &, ~).
	EZWIN32_ENABLE_ENUM_FLAGS(ExStyle);

	/*****************************************************************************
	*********************************    Key    **********************************
	*****************************************************************************/

	//!	@brief	Virtual-key codes used by the system.
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
		Apps = VK_APPS,
		Space = VK_SPACE,
		Clear = VK_CLEAR,
		Shift = VK_SHIFT,
		Enter = VK_RETURN,
		LeftWin = VK_LWIN,
		RightWin = VK_RWIN,
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

	//! @brief	Convert `Key` enum to string for debugging or logging.
	static inline const char * to_string(Key key)
	{
		switch (key)
		{
			// Letters
			case Key::A: return "Key::A"; case Key::B: return "Key::B"; case Key::C: return "Key::C"; case Key::D: return "Key::D";
			case Key::E: return "Key::E"; case Key::F: return "Key::F"; case Key::G: return "Key::G"; case Key::H: return "Key::H";
			case Key::I: return "Key::I"; case Key::J: return "Key::J"; case Key::K: return "Key::K"; case Key::L: return "Key::L";
			case Key::M: return "Key::M"; case Key::N: return "Key::N"; case Key::O: return "Key::O"; case Key::P: return "Key::P";
			case Key::Q: return "Key::Q"; case Key::R: return "Key::R"; case Key::S: return "Key::S"; case Key::T: return "Key::T";
			case Key::U: return "Key::U"; case Key::V: return "Key::V"; case Key::W: return "Key::W"; case Key::X: return "Key::X";
			case Key::Y: return "Key::Y"; case Key::Z: return "Key::Z";

			// Numbers
			case Key::Num0: return "Key::Num0"; case Key::Num1: return "Key::Num1"; case Key::Num2: return "Key::Num2"; case Key::Num3: return "Key::Num3";
			case Key::Num4: return "Key::Num4"; case Key::Num5: return "Key::Num5"; case Key::Num6: return "Key::Num6"; case Key::Num7: return "Key::Num7";
			case Key::Num8: return "Key::Num8"; case Key::Num9: return "Key::Num9";

			// Function keys
			case Key::F1: return "Key::F1"; case Key::F2: return "Key::F2"; case Key::F3: return "Key::F3"; case Key::F4: return "Key::F4";
			case Key::F5: return "Key::F5"; case Key::F6: return "Key::F6"; case Key::F7: return "Key::F7"; case Key::F8: return "Key::F8";
			case Key::F9: return "Key::F9"; case Key::F10: return "Key::F10"; case Key::F11: return "Key::F11"; case Key::F12: return "Key::F12";
			case Key::F13: return "Key::F13"; case Key::F14: return "Key::F14"; case Key::F15: return "Key::F15"; case Key::F16: return "Key::F16";
			case Key::F17: return "Key::F17"; case Key::F18: return "Key::F18"; case Key::F19: return "Key::F19"; case Key::F20: return "Key::F20";
			case Key::F21: return "Key::F21"; case Key::F22: return "Key::F22"; case Key::F23: return "Key::F23"; case Key::F24: return "Key::F24";

			// Navigation and control
			case Key::Up: return "Key::Up"; case Key::Down: return "Key::Down"; case Key::Left: return "Key::Left"; case Key::Right: return "Key::Right";
			case Key::Home: return "Key::Home"; case Key::End: return "Key::End"; case Key::PageUp: return "Key::PageUp"; case Key::PageDown: return "Key::PageDown";
			case Key::Insert: return "Key::Insert"; case Key::Delete: return "Key::Delete";

			// System keys
			case Key::Escape: return "Key::Escape"; case Key::Enter: return "Key::Enter"; case Key::Space: return "Key::Space";
			case Key::Tab: return "Key::Tab"; case Key::BackSpace: return "Key::BackSpace"; case Key::Shift: return "Key::Shift";
			case Key::Control: return "Key::Control"; case Key::Alt: return "Key::Alt"; case Key::CapLock: return "Key::CapLock";
			case Key::Pause: return "Key::Pause"; case Key::ScrollLock: return "Key::ScrollLock"; case Key::PrintScreen: return "Key::PrintScreen";
			case Key::LeftWin: return "Key::LeftWin"; case Key::RightWin: return "Key::RightWin"; case Key::Apps: return "Key::Apps";

			// Numpad
			case Key::NumLock: return "Key::NumLock";
			case Key::NumPad0: return "Key::NumPad0"; case Key::NumPad1: return "Key::NumPad1"; case Key::NumPad2: return "Key::NumPad2";
			case Key::NumPad3: return "Key::NumPad3"; case Key::NumPad4: return "Key::NumPad4"; case Key::NumPad5: return "Key::NumPad5";
			case Key::NumPad6: return "Key::NumPad6"; case Key::NumPad7: return "Key::NumPad7"; case Key::NumPad8: return "Key::NumPad8";
			case Key::NumPad9: return "Key::NumPad9";
			case Key::Add: return "Key::Add"; case Key::Subtract: return "Key::Subtract";
			case Key::Multiply: return "Key::Multiply"; case Key::Divide: return "Key::Divide"; case Key::Decimal: return "Key::Decimal";

			// Media & browser keys
			case Key::VolumeUp: return "Key::VolumeUp"; case Key::VolumeDown: return "Key::VolumeDown"; case Key::VolumeMute: return "Key::VolumeMute";
			case Key::MediaPlayPause: return "Key::MediaPlayPause"; case Key::MediaStop: return "Key::MediaStop";
			case Key::MediaNextTrack: return "Key::MediaNextTrack"; case Key::MediaPrevTrack: return "Key::MediaPrevTrack";
			case Key::BrowserBack: return "Key::BrowserBack"; case Key::BrowserForward: return "Key::BrowserForward";
			case Key::BrowserRefresh: return "Key::BrowserRefresh"; case Key::BrowserStop: return "Key::BrowserStop";
			case Key::BrowserSearch: return "Key::BrowserSearch"; case Key::BrowserFavorites: return "Key::BrowserFavorites";
			case Key::BrowserHome: return "Key::BrowserHome";
			case Key::LaunchMail: return "Key::LaunchMail"; case Key::LaunchApp1: return "Key::LaunchApp1";
			case Key::LaunchApp2: return "Key::LaunchApp2"; case Key::LaunchMediaSelect: return "Key::LaunchMediaSelect";

			default: return "Key::Unknown";
		}
	}

	/*****************************************************************************
	*****************************    MouseButton    ******************************
	*****************************************************************************/

	//!	@brief	Mouse button types.
	enum class MouseButton
	{
		Left,			//!< Left mouse button.
		Right,			//!< Right mouse button.
		Middle,			//!< Middle mouse button (usually the wheel).
		XButton1,		//!< Extra mouse button 1.
		XButton2,		//!< Extra mouse button 2.
	};

	//!	@brief	Converts a `MouseButton` enum value to a string representation.
	static inline const char * to_string(MouseButton button)
	{
		switch (button)
		{
			case MouseButton::Left:			return "MouseButton::Left";
			case MouseButton::Right:		return "MouseButton::Right";
			case MouseButton::Middle:		return "MouseButton::Middle";
			case MouseButton::XButton1:		return "MouseButton::XButton1";
			case MouseButton::XButton2:		return "MouseButton::XButton2";
			default:						return "MouseButton::Unknown";
		}
	}

	/*****************************************************************************
	******************************    MouseState    ******************************
	*****************************************************************************/

	//! @brief	Mouse state bit flags representing the current button and key states.
	enum class MouseState
	{
		Left		= MK_LBUTTON,		//!< Left mouse button is pressed.
		Right		= MK_RBUTTON,		//!< Right mouse button is pressed.
		Middle		= MK_MBUTTON,		//!< Middle mouse button is pressed.
		XButton1	= MK_XBUTTON1,		//!< Extra mouse button 1 is pressed.
		XButton2	= MK_XBUTTON2,		//!< Extra mouse button 2 is pressed.
		Shift		= MK_SHIFT,			//!< SHIFT key is held down.
		Ctrl		= MK_CONTROL,		//!< CTRL key is held down.
	};

	//!	@brief	Enables bitwise operators (|, &, ~).
	EZWIN32_ENABLE_ENUM_FLAGS(MouseState);

	//!	@brief	Converts a `Flags<MouseState>` to a readable string.
	static inline std::string to_string(Flags<MouseState> stateFlags)
	{
		std::string result;

		auto append = [&](const char * name)
		{
			if (!result.empty())
				result += " | ";

			result += name;
		};

		if (stateFlags.has(MouseState::Left))		append("MouseState::Left");
		if (stateFlags.has(MouseState::Right))		append("MouseState::Right");
		if (stateFlags.has(MouseState::Middle))		append("MouseState::Middle");
		if (stateFlags.has(MouseState::XButton1))	append("MouseState::XButton1");
		if (stateFlags.has(MouseState::XButton2))	append("MouseState::XButton2");
		if (stateFlags.has(MouseState::Shift))		append("MouseState::Shift");
		if (stateFlags.has(MouseState::Ctrl))		append("MouseState::Ctrl");
		if (result.empty())							append("MouseState::None");

		return result;
	}

	/*****************************************************************************
	*****************************    MouseAction    ******************************
	*****************************************************************************/

	//! @brief	Type of mouse action.
	enum class MouseAction
	{
		Up,				//!< Mouse button released.
		Down,			//!< Mouse button pressed.
		DoubleClick,	//!< Mouse button double-clicked.
	};

	//! @brief	Converts a `MouseAction` enum value to a string representation.
	static inline const char * to_string(MouseAction action)
	{
		switch (action)
		{
			case MouseAction::Up:				return "MouseAction::Up";
			case MouseAction::Down:				return "MouseAction::Down";
			case MouseAction::DoubleClick:		return "MouseAction::DoubleClick";
			default:							return "MouseAction::Unknown";
		}
	}

	/*****************************************************************************
	******************************    KeyAction    *******************************
	*****************************************************************************/

	//!	@brief	Type of keyboard action.
	enum class KeyAction
	{
		Press,		//!< The key has been pressed down for the first time.
		Repeat,		//!< The key is being held down and generating repeat messages.
		Release,	//!< The key has been released.
	};

	//!	@brief	Convert `KeyAction` enum to string for debugging or logging.
	static inline const char * to_string(KeyAction action)
	{
		switch (action)
		{
			case KeyAction::Press:			return "KeyAction::Press";
			case KeyAction::Repeat:			return "KeyAction::Repeat";
			case KeyAction::Release:		return "KeyAction::Release";
			default:						return "KeyAction::Unknown";
		}
	}

	/*****************************************************************************
	********************************    Cursor    ********************************
	*****************************************************************************/

	//!	@brief	Predefined cursors of Windows OS.
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

	//!	@brief	Convert `Cursor` enum to string for debugging or logging.
	static inline const char* to_string(Cursor cursor)
	{
		switch (cursor)
		{
			case Cursor::None:				return "Cursor::None";
			case Cursor::Wait:				return "Cursor::Wait";
			case Cursor::Hand:				return "Cursor::Hand";
			case Cursor::Help:				return "Cursor::Help";
			case Cursor::Arrow:				return "Cursor::Arrow";
			case Cursor::Cross:				return "Cursor::Cross";
			case Cursor::IBeam:				return "Cursor::IBeam";
			case Cursor::SizeWE:			return "Cursor::SizeWE";
			case Cursor::SizeNS:			return "Cursor::SizeNS";
			case Cursor::SizeAll:			return "Cursor::SizeAll";
			case Cursor::UpArrow:			return "Cursor::UpArrow";
			case Cursor::SizeNWSE:			return "Cursor::SizeNWSE";
			case Cursor::SizeNESW:			return "Cursor::SizeNESW";
			case Cursor::AppStarting:		return "Cursor::AppStarting";
			default:						return "Cursor::Unknown";
		}
	}

	/*****************************************************************************
	****************************    HitTestResult    *****************************
	*****************************************************************************/

	//!	@brief	HitTest result type, returned by WM_NCHITTEST.
	enum class HitTestResult : LRESULT
	{
		Nowhere			= HTNOWHERE,		//!< No part of the window
		Client			= HTCLIENT,			//!< Client area
		Caption			= HTCAPTION,		//!< Title bar (caption)
		SystemMenu		= HTSYSMENU,		//!< System menu (icon)
		GrowBox			= HTSIZE,			//!< Size box (legacy)
		Menu			= HTMENU,			//!< Menu area
		HScroll			= HTHSCROLL,		//!< Horizontal scroll bar
		VScroll			= HTVSCROLL,		//!< Vertical scroll bar
		MinButton		= HTMINBUTTON,		//!< Minimize button
		MaxButton		= HTMAXBUTTON,		//!< Maximize button
		Left			= HTLEFT,			//!< Left border
		Right			= HTRIGHT,			//!< Right border
		Top				= HTTOP,			//!< Top border
		TopLeft			= HTTOPLEFT,		//!< Top-left corner
		TopRight		= HTTOPRIGHT,		//!< Top-right corner
		Bottom			= HTBOTTOM,			//!< Bottom border
		BottomLeft		= HTBOTTOMLEFT,		//!< Bottom-left corner
		BottomRight		= HTBOTTOMRIGHT,	//!< Bottom-right corner
		Border			= HTBORDER,			//!< Non-sizing border
		CloseButton		= HTCLOSE,			//!< Close button
		HelpButton		= HTHELP,			//!< Help button
		Default			= -1,				//!< Use default hit test (DefWindowProc)
	};


	//!	@brief	Convert `HitTestResult` enum to string for debugging or logging.
	static inline const char* to_string(HitTestResult result)
	{
		switch (result)
		{
			case HitTestResult::Nowhere:		return "HitTestResult::Nowhere";
			case HitTestResult::Client:			return "HitTestResult::Client";
			case HitTestResult::Caption:		return "HitTestResult::Caption";
			case HitTestResult::SystemMenu:		return "HitTestResult::SystemMenu";
			case HitTestResult::GrowBox:		return "HitTestResult::GrowBox";
			case HitTestResult::Menu:			return "HitTestResult::Menu";
			case HitTestResult::HScroll:		return "HitTestResult::HScroll";
			case HitTestResult::VScroll:		return "HitTestResult::VScroll";
			case HitTestResult::MinButton:		return "HitTestResult::MinButton";
			case HitTestResult::MaxButton:		return "HitTestResult::MaxButton";
			case HitTestResult::Left:			return "HitTestResult::Left";
			case HitTestResult::Right:			return "HitTestResult::Right";
			case HitTestResult::Top:			return "HitTestResult::Top";
			case HitTestResult::TopLeft:		return "HitTestResult::TopLeft";
			case HitTestResult::TopRight:		return "HitTestResult::TopRight";
			case HitTestResult::Bottom:			return "HitTestResult::Bottom";
			case HitTestResult::BottomLeft:		return "HitTestResult::BottomLeft";
			case HitTestResult::BottomRight:	return "HitTestResult::BottomRight";
			case HitTestResult::Border:			return "HitTestResult::Border";
			case HitTestResult::CloseButton:	return "HitTestResult::CloseButton";
			case HitTestResult::HelpButton:		return "HitTestResult::HelpButton";
			case HitTestResult::Default:		return "HitTestResult::Default";
			default:							return "HitTestResult::Unknown";
		}
	}
}

/*********************************************************************************
********************************    Type alias    ********************************
*********************************************************************************/

using EzKey = easywin32::Key;
using EzColor = easywin32::Color;
using EzStyle = easywin32::Style;
using EzWindow = easywin32::Window;
using EzCursor = easywin32::Cursor;
using EzExStyle = easywin32::ExStyle;
using EzKeyAction = easywin32::KeyAction;
using EzMouseState = easywin32::MouseState;
using EzMouseAction = easywin32::MouseAction;
using EzMouseButton = easywin32::MouseButton;
using EzHitTestResult = easywin32::HitTestResult;
using EzMouseStateFlags = easywin32::Flags<easywin32::MouseState>;
template<typename EnumType> using EzFlags = easywin32::Flags<EnumType>;

/*********************************************************************************
**********************************    Window    **********************************
*********************************************************************************/

/**
 *	@brief		
 */
class easywin32::Window
{

public:

	Window() = default;

	Window(const Window&) = delete;

	void operator=(const Window&) = delete;

	Window(string_type title) { this->setTitle(title); }

	~Window() { this->close(); }

public:

	/**
	 *	@brief			
	 */
	void open(Flags<Style> styleFlags = Style::OverlappedWindow, Flags<ExStyle> exStyleFlags = 0);


	/**
	 *	@brief		
	 */
	void close() { ::DestroyWindow(m_hWnd);		m_hWnd = nullptr; }

public:

	//!	@brief	Returns the native handle of the win32 window.
	HWND nativeHandle() { return m_hWnd; }

	//!	@brief	Whether the specified window handle identifies an existing window (opened).	
	bool isOpen() const { return ::IsWindow(m_hWnd); }

	//!	@brief	Whether the window is minimized.
	bool isMinimized() const { return ::IsIconic(m_hWnd); }

	//!	@brief	Whether the window is maximized.
	bool isMaximized() const { return ::IsZoomed(m_hWnd); }

	//!	@brief	Whether the windows is focused.
	bool IsFocused() const { return ::GetFocus() == m_hWnd; }

	//!	@brief	Checks if the window is currently marked as visible.
	bool isVisible() const { return ::IsWindowVisible(m_hWnd) != FALSE; }

	//!	@brief	Whether the windows is the foreground (active) window.
	bool isForeground() const { return ::GetForegroundWindow() == m_hWnd; }

public:

	//!	@brief	Bring the window to front and set input focus.
	void setFocus() { ::SetFocus(m_hWnd); }

	//!	@brief	Hide the window.
	void hide() { ::ShowWindow(m_hWnd, SW_HIDE); }

	//!	@brief	Bring the window to the top of the Z order.
	void bringToTop() { ::BringWindowToTop(m_hWnd); }

	//!	@brief	Show the window.
	void show() { ::ShowWindow(m_hWnd, SW_SHOWNORMAL); }

	//!	@brief	Displays or hides the cursor.
	void showCursor(bool bShow) { ::ShowCursor(bShow); }

	//!	@brief	Foreground the window.
	void setForeground() { ::SetForegroundWindow(m_hWnd); }

	//!	@brief	Maximized the window.
	void maximize() { ::ShowWindow(m_hWnd, SW_SHOWMAXIMIZED); }

	//!	@brief	Minimized the window.
	void minimize() { ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED); }

	//!	@brief	Enables or disables mouse and keyboard input to the specified window.
	void enableInput(bool bEnable) { ::EnableWindow(m_hWnd, bEnable); }

	//!	@brief	Creates a timer with the specified time-out value.
	void setTimer(unsigned int millisecond) { ::SetTimer(m_hWnd, 1, millisecond, NULL); }

	//!	@brief	Draws a raw RGB bitmap onto the window at the specified position.
	void drawBitmap(const Color * pixels, int width, int height, int dstX = 0, int dstY = 0);

	//!	@brief	Requests the window to be redrawn.
	void requestRedraw(const RECT * rect = nullptr, bool eraseBackground = false)
	{
		::InvalidateRect(m_hWnd, rect, eraseBackground);
		::UpdateWindow(m_hWnd);
	}

	//!	@brief	Specify the cursor shape, must be called from the main thread.
	void setCursor(Cursor cursor)
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
	void setTitle(string_type title)
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
	const string_type & getTitle() const { return m_title; }

public:

	void setPos(int left, int top, int right, int bottom);

public:

	/**
	 *	@brief		Waits for and processes the next window message.
	 *	@details	This call will block until a new message is available in the queue for this window.
	 *				It retrieves the message with `GetMessage`, translates it (e.g. converts virtual-key
	 *				messages into character messages), and dispatches it to the window procedure.
	 */
	void waitProcessEvent()
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
	static void waitProcessThreadWindows()
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
	bool processEvent()
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
	static bool processThreadWindows()
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

	template<bool EraseTitleBar> struct NativeClass;

	//!	@brief	Window procedure for message dispatching.
	template<bool EraseTitleBar> static LRESULT procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

public:

	/**
	 *	@brief		User-defined callback functions, called when triggered and defined by the user.
	 *	@note		Each callback can optionally handle the event and determine whether it should be passed to the 
	 *				system's default handler (`DefWindowProc`).
	 *	@details	If the callback returns any value other than `-1`, that value will be returned directly as the 
	 *				window procedure¡¯s result ¡ª meaning the event is considered handled and `DefWindowProc` will **not** be called.
	 *	@details	If the callback returns `-1`, the message will be forwarded to `DefWindowProc` for default processing.
	 */
	std::function<LRESULT(wchar_t)>											onInputCharacter;	// Called when a character input (WM_CHAR, WM_SYSCHAR, WM_UNICHAR) is received.
	std::function<LRESULT()>												onKillFocus;		// Called when the window loses focus (WM_KILLFOCUS).
	std::function<LRESULT()>												onSetFocus;			// Called when the window gains focus (WM_SETFOCUS).
	std::function<LRESULT()>												onEnterMove;		// Called when the user starts moving or resizing the window(WM_ENTERSIZEMOVE).
	std::function<LRESULT()>												onExitMove;			// Called when the user finishes moving or resizing the window (WM_EXITSIZEMOVE).
	std::function<LRESULT()>												onPaint;			// Called when the window needs to be repainted (WM_PAINT).
	std::function<LRESULT()>												onTimer;			// Called when a timer event occurs (WM_TIMER).
	std::function<LRESULT()>												onClose;			// Called when the window is about to close (WM_CLOSE).
	std::function<LRESULT(int w, int h)>									onResize;			// Called when the window is resized (WM_SIZE).
	std::function<LRESULT(int x, int y)>									onMove;				// Called when the window is moved (WM_MOVE).
	std::function<LRESULT(int x, int y, Flags<MouseState>)>					onMouseMove;		// Called when the mouse is moved (WM_MOUSEMOVE).
	std::function<LRESULT(int dx, int dy, Flags<MouseState>)>				onWheelScroll;		// Called when the mouse wheel is scrolled (WM_MOUSEWHEEL / WM_MOUSEHWHEEL).
	std::function<LRESULT(MouseButton, MouseAction, Flags<MouseState>)>		onMouseClick;		// Called when a mouse button event occurs (down, up, or double click).
	std::function<LRESULT(Key, KeyAction)>									onKeyboardPress;	// Called when a key is pressed, released, or repeated (WM_KEYDOWN/WM_KEYUP).
	std::function<HitTestResult(int x, int y)>								onHitTest;			// Called when WM_NCHITTEST is received, should return the hit-test result based on cursor position.

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
template<bool EraseTitleBar> LRESULT easywin32::Window::procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)		//	Retrieve the use pointer
	{
		CREATESTRUCT * createStrcut = reinterpret_cast<CREATESTRUCT*>(lParam);

		auto window = reinterpret_cast<Window*>(createStrcut->lpCreateParams);

		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
	}
	else if (uMsg == WM_NCCALCSIZE)
	{
		if constexpr (EraseTitleBar)
		{
			constexpr int frameSize = 8;	//	win32 default size for drag

			NCCALCSIZE_PARAMS * pParams = (NCCALCSIZE_PARAMS*)lParam;

			if (::IsZoomed(hWnd))
			{
				pParams->rgrc[0].top += frameSize;
				pParams->rgrc[0].left += frameSize;
				pParams->rgrc[0].right -= frameSize;
				pParams->rgrc[0].bottom -= frameSize;
			}
			else
			{
				pParams->rgrc[0].top += 0;				//	skip title bar
				pParams->rgrc[0].left += frameSize;
				pParams->rgrc[0].right -= frameSize;
				pParams->rgrc[0].bottom -= frameSize;
			}

			return 0;
		}
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
		LRESULT result = -1;

		//	Dispatch standard messages to callbacks
		switch (uMsg)
		{
			case WM_CLOSE:			if (window->onClose)			result = window->onClose();			break;
			case WM_TIMER:			if (window->onTimer)			result = window->onTimer();			break;
			case WM_PAINT:			if (window->onPaint)			result = window->onPaint();			break;
			case WM_SETFOCUS:		if (window->onSetFocus)			result = window->onSetFocus();		break;
			case WM_KILLFOCUS:		if (window->onKillFocus)		result = window->onKillFocus();		break;
			case WM_EXITSIZEMOVE:	if (window->onExitMove)			result = window->onExitMove();		break;
			case WM_ENTERSIZEMOVE:	if (window->onEnterMove)		result = window->onEnterMove();		break;

			case WM_CHAR:			if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;
			case WM_SYSCHAR:		if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;
			case WM_UNICHAR:		if (window->onInputCharacter)	result = window->onInputCharacter(static_cast<wchar_t>(wParam));	break;

			case WM_MOVE:			if (window->onMove)				result = window->onMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));				break;
			case WM_SIZE:			if (window->onResize)			result = window->onResize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));				break;
			case WM_NCHITTEST:		if (window->onHitTest)			result = (LRESULT)window->onHitTest(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));	break;

			case WM_KEYUP:			if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), KeyAction::Release);		break;
			case WM_SYSKEYUP:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), KeyAction::Release);		break;

			case WM_KEYDOWN:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), (lParam & (1 << 30)) ? KeyAction::Repeat : KeyAction::Press);		break;
			case WM_SYSKEYDOWN:		if (window->onKeyboardPress)	result = window->onKeyboardPress(static_cast<Key>(wParam), (lParam & (1 << 30)) ? KeyAction::Repeat : KeyAction::Press);		break;

			case WM_MOUSEMOVE:		if (window->onMouseMove)		result = window->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), static_cast<MouseState>(wParam & 127));				break;
			case WM_MOUSEWHEEL:		if (window->onWheelScroll)		result = window->onWheelScroll(0, static_cast<SHORT>(HIWORD(wParam)) / WHEEL_DELTA, static_cast<MouseState>(wParam & 127));		break;
			case WM_MOUSEHWHEEL:	if (window->onWheelScroll)		result = window->onWheelScroll(static_cast<SHORT>(HIWORD(wParam)) / WHEEL_DELTA, 0, static_cast<MouseState>(wParam & 127));		break;

			case WM_LBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::Up, static_cast<MouseState>(wParam & 127));		break;
			case WM_RBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::Up, static_cast<MouseState>(wParam & 127));		break;
			case WM_MBUTTONUP:		if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::Up, static_cast<MouseState>(wParam & 127));		break;

			case WM_LBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::Down, static_cast<MouseState>(wParam & 127));			break;
			case WM_RBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::Down, static_cast<MouseState>(wParam & 127));		break;
			case WM_MBUTTONDOWN:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::Down, static_cast<MouseState>(wParam & 127));		break;

			case WM_LBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Left, MouseAction::DoubleClick, static_cast<MouseState>(wParam & 127));		break;
			case WM_RBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Right, MouseAction::DoubleClick, static_cast<MouseState>(wParam & 127));		break;
			case WM_MBUTTONDBLCLK:	if (window->onMouseClick)		result = window->onMouseClick(MouseButton::Middle, MouseAction::DoubleClick, static_cast<MouseState>(wParam & 127));	break;

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
						result = window->onMouseClick(MouseButton::XButton1, action, static_cast<MouseState>(wParam & 127));
					}
					else if (button == XBUTTON2)
					{
						result = window->onMouseClick(MouseButton::XButton2, action, static_cast<MouseState>(wParam & 127));
					}
				}

				break;
			}
		}

		if (result != -1)
			return result;
	}

	//	Default handling for unprocessed messages
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/**
 *	@brief	Window class wrapper for Win32 window registration.
 *
 *	This struct inherits from `WNDCLASSEX` and is used to register a single
 *	window class with the Win32 API. The class is automatically registered
 *	upon construction and unregistered upon destruction. This ensures that
 *	the registration occurs only once during the application's lifetime.
 */
template<bool EraseTitleBar> struct easywin32::Window::NativeClass : public WNDCLASSEX
{
	bool isRegistered;

	NativeClass() : isRegistered(false)
	{
		cbSize			= sizeof(WNDCLASSEXW);
		style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		lpfnWndProc		= Window::procedure<EraseTitleBar>;
		cbClsExtra		= 0;
		cbWndExtra		= 0;
		hInstance		= ::GetModuleHandle(NULL);
		hIcon			= ::LoadIcon(NULL, IDI_APPLICATION);
		hCursor			= NULL;
		hbrBackground	= (HBRUSH)::GetStockObject(NULL_BRUSH);
		lpszMenuName	= NULL;
		hIconSm			= ::LoadIcon(NULL, IDI_WINLOGO);
	#ifdef UNICODE
		lpszClassName	= L"EasyWin32";
	#else
		lpszClassName	= "EasyWin32";
	#endif
		isRegistered = ::RegisterClassEx(this);
	}

	~NativeClass()
	{
		if (isRegistered)
		{
			::UnregisterClass(lpszClassName, hInstance);
		}
	}
};


void easywin32::Window::open(Flags<Style> styleFlags, Flags<ExStyle> exStyleFlags)
{
	if (::IsWindow(m_hWnd) != 0)		return;

	if (styleFlags.has(Style::ThickFrame) && !styleFlags.has(Style::Caption))
	{
		static NativeClass<true>	s_win32Class;

		assert(s_win32Class.isRegistered);

		if (s_win32Class.isRegistered)
		{
			auto rect = m_bounds;

			constexpr int frameSize = 8;
			rect.bottom += frameSize;
			rect.right += frameSize;
			rect.left -= frameSize;

			m_hWnd = ::CreateWindowEx(exStyleFlags, s_win32Class.lpszClassName, m_title.c_str(), styleFlags,
									  rect.left, rect.top, rect.right, rect.bottom, NULL, NULL, s_win32Class.hInstance,
									  this /* Additional application data */);
		}
	}
	else
	{
		static NativeClass<false>	s_win32Class;

		assert(s_win32Class.isRegistered);

		if (s_win32Class.isRegistered)
		{
			auto rect = m_bounds;

			::AdjustWindowRectEx(&rect, styleFlags, FALSE, exStyleFlags);

			m_hWnd = ::CreateWindowEx(exStyleFlags, s_win32Class.lpszClassName, m_title.c_str(), styleFlags,
									  rect.left, rect.top, rect.right, rect.bottom, NULL, NULL, s_win32Class.hInstance,
									  this /* Additional application data */);
		}
	}
}


/**
 *	@brief		Draws a raw RGB bitmap onto the window at the specified position.
 *	@details	This function copies pixel data directly to the window's client area
 *				using GDI without relying on any GPU or graphics API.
 *	@param[in]	pixels - Pointer to the RGB pixel data in row-major order.
 *	@param[in]	width - Width of the bitmap in pixels.
 *	@param[in]	height - Height of the bitmap in pixels.
 *	@param[in]	dstX - Destination X coordinate in the client area.
 *	@param[in]	dstY - Destination Y coordinate in the client area.
 *	@note		The pixel format must match the expected 24-bit RGB format defined by `Color`.
 *				The function performs an immediate blit to the window using `SetDIBitsToDevice`.
 *	@warning	This function must be called only inside `onPaint`, because it uses BeginPaint/EndPaint.
 *				Calling it outside `onPaint` causes undefined behavior in Win32.
 */
void easywin32::Window::drawBitmap(const Color * pixels, int width, int height, int dstX, int dstY)
{
	PAINTSTRUCT ps = {};
	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth			= width;
	bmi.bmiHeader.biHeight			= -height;				// Negative = top-down bitmap
	bmi.bmiHeader.biPlanes			= 1;
	bmi.bmiHeader.biBitCount		= sizeof(Color) * 8;	// 24-bit (RGB)
	bmi.bmiHeader.biCompression		= BI_RGB;				// No compression

	// Begin painting
	HDC hdc = BeginPaint(m_hWnd, &ps);

	// Draw image directly to window
	SetDIBitsToDevice(
		hdc,
		dstX, dstY,			// Destination X, Y
		width, height,		// Width, Height
		0, 0,				// Source X, Y
		0, height,			// Start scan line, number of scan lines
		pixels,				// Pointer to pixel data
		&bmi,
		DIB_RGB_COLORS		// RGB mode
	);

	// End painting
	EndPaint(m_hWnd, &ps);
}

#endif