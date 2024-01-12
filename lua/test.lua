local ffi = require("ffi")
local bit = require("bit")

ffi.cdef[[
typedef unsigned long XID;

typedef struct _Display Display;

typedef struct _XExtData XExtData;
typedef XID GContext;
typedef struct _GC {
    XExtData *ext_data;
    GContext gid;
} GC;

typedef union _XEvent {
        int type;
	long pad[24];
} XEvent;

typedef XID Window;
typedef XID Drawable;

Display *XOpenDisplay(const char*);
int XDefaultScreen(Display*);
unsigned long XBlackPixel(Display*, int);
unsigned long XWhitePixel(Display*, int);
Window XDefaultRootWindow(Display*);
Window XCreateSimpleWindow(Display*, Window, int, int, unsigned int, unsigned int, unsigned int, unsigned long, unsigned long);
int XSelectInput(Display*, Window, long);
int XMapWindow(Display*, Window);
GC XDefaultGC(Display*, int);
int XNextEvent(Display*, XEvent*);
int XFillRectangle(Display*, Drawable, GC, int, int, unsigned int, unsigned int);
]]

local X11 = ffi.load("X11")

local display = X11.XOpenDisplay(ffi.NULL)

local screen = X11.XDefaultScreen(display)

local blackColor = X11.XBlackPixel(display, screen)
local whiteColor = X11.XWhitePixel(display, screen)

local window = X11.XCreateSimpleWindow(display, X11.XDefaultRootWindow(display), 0, 0, 200, 200, 0, blackColor, whiteColor)

local ExposureMask = ffi.new("long", 1)
local mask = bit.lshift(ExposureMask, 15)
X11.XSelectInput(display, window, mask)

X11.XMapWindow(display, window)

local Expose = 12

local gc = X11.XDefaultGC(display, screen)

local event = ffi.new("XEvent")
while true do
	X11.XNextEvent(display, event)
	if event.type == Expose then
		X11.XFillRectangle(display, window, gc, 5, 50, 5, 5)
	end
end
