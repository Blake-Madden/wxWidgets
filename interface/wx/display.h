/////////////////////////////////////////////////////////////////////////////
// Name:        display.h
// Purpose:     interface of wxDisplay
// Author:      wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxDisplay

    Determines the sizes and locations of displays connected to the system.

    @library{wxcore}
    @category{cfg}
*/
class wxDisplay
{
public:
    /**
        Default constructor creating wxDisplay object representing the primary
        display.
     */
    wxDisplay();

    /**
        Constructor, setting up a wxDisplay instance with the specified
        display.

        @param index
            The index of the display to use. This must be non-negative and
            lower than the value returned by GetCount().
    */
    explicit wxDisplay(unsigned int index);

    /**
        Constructor creating the display object associated with the given
        window.

        This is the most convenient way of finding the display on which the
        given window is shown while falling back to the default display if it
        is not shown at all or positioned outside of any display.

        @param window
            A valid, i.e. non-null, window.

        @see GetFromWindow()

        @since 3.1.2
     */
    explicit wxDisplay(const wxWindow* window);

    /**
        Destructor.
    */
    ~wxDisplay();

    /**
        Changes the video mode of this display to the mode specified in the
        mode parameter.

        If wxDefaultVideoMode is passed in as the mode parameter, the defined
        behaviour is that wxDisplay will reset the video mode to the default
        mode used by the display. On Windows, the behaviour is normal. However,
        there are differences on other platforms. On Unix variations using X11
        extensions it should behave as defined, but some irregularities may
        occur.
    */
    bool ChangeMode(const wxVideoMode& mode = wxDefaultVideoMode);

    /**
        Returns the client area of the display. The client area is the part of
        the display available for the normal (non full screen) windows, usually
        it is the same as GetGeometry() but it could be less if there is a
        taskbar (or equivalent) on this display.
    */
    wxRect GetClientArea() const;

    /**
        Returns the number of connected displays.
    */
    static unsigned int GetCount();

    /**
        Returns the current video mode that this display is in.
    */
    wxVideoMode GetCurrentMode() const;

    /**
        Returns the index of the display on which the given point lies, or
        @c wxNOT_FOUND if the point is not on any connected display.

        @param pt
            The point to locate.
    */
    static int GetFromPoint(const wxPoint& pt);

    /**
        Returns the index of the display with biggest intersection with the
        given rectangle or @c wxNOT_FOUND if the rectangle doesn't intersect
        any display.

        Note that usually the returned display will be the same display which
        contains the center of the rectangle, but this is not always the case,
        as rectangle might be partly visible even if its center is off screen,
        and in this case GetFromPoint() would returns @c wxNOT_FOUND, but this
        function would return a valid display.

        @param rect
            The rectangle to check.

        @since 3.3.0
    */
    static int GetFromRect(const wxRect& rect);

    /**
        Returns the index of the display on which the given window lies.

        If the window is on more than one display it gets the display that
        overlaps the window the most.

        Returns @c wxNOT_FOUND if the window is not on any connected display.

        @param win
            The window to locate.
    */
    static int GetFromWindow(const wxWindow* win);

    /**
        Returns the bounding rectangle of the display whose index was passed to
        the constructor.

        @see GetClientArea(), wxDisplaySize()
    */
    wxRect GetGeometry() const;

    /**
        Fills and returns an array with all the video modes that are supported
        by this display, or video modes that are supported by this display and
        match the mode parameter (if mode is not wxDefaultVideoMode).
    */
    wxArrayVideoModes GetModes(const wxVideoMode& mode = wxDefaultVideoMode) const;

    /**
        Returns the display's name.

        The returned value is currently an empty string under all platforms
        except MSW.
    */
    wxString GetName() const;

    /**
        Returns display depth, i.e. number of bits per pixel (0 if unknown)

        @since 3.1.2
    */
    int GetDepth() const;

    /**
        Returns display resolution in pixels per inch.

        Horizontal and vertical resolution are returned in @c x and @c y
        components of the wxSize object respectively.

        If the resolution information is not available, returns `wxSize(0, 0)`.

        @since 3.1.2
     */
    wxSize GetPPI() const;

    /**
        Returns scaling factor used by this display.

        The scaling factor is the ratio between GetPPI() and GetStdPPI()
        (it is implicitly assumed that this ratio is the same for both
        horizontal and vertical components).

        @see wxWindow::GetContentScaleFactor(), wxWindow::GetDPIScaleFactor()

        @since 3.1.5
     */
    double GetScaleFactor() const;

    /**
        Returns default display resolution for the current platform in pixels
        per inch.

        This function mostly used internally, use GetPPI() to get the actual
        display resolution.

        Currently the standard PPI is the same in both horizontal and vertical
        directions on all platforms and its value is 96 everywhere except under
        Apple devices (those running macOS, iOS, watchOS etc), where it is 72.

        @see GetStdPPI()

        @since 3.1.5
     */
    static int GetStdPPIValue();

    /**
        Returns default display resolution for the current platform as wxSize.

        This function is equivalent to constructing wxSize object with both
        components set to GetStdPPIValue().

        @since 3.1.5
     */
    static wxSize GetStdPPI();

    /**
        Returns @true if the display has not been unplugged yet.

        This function can return @false if the display configuration has
        changed since this wxDisplay object has been created and either this
        display is known not to be connected to the system any more (support
        for detecting this is currently only implemented in wxMSW) or the
        display status is now unknown (which happens in all the other ports
        detecting the display configuration changes, e.g. wxOSX).

        A disconnected object is still usable, but all accessor functions
        return invalid fallback values (e.g. 0 for the width and height) and so
        such objects are not really useful any more. It is recommended to
        recreate them when the display configuration changes, which can be done
        in wxEVT_DISPLAY_CHANGED handler of any top-level window.

        @since 3.3.0
    */
    bool IsConnected() const;

    /**
        Returns @true if the display is the primary display. The primary
        display is the one whose index is 0.
    */
    bool IsPrimary() const;
};

