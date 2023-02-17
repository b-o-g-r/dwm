/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappx = 12;   /* gaps between windows */
static const unsigned int minwsz = 20; /* Minimal heigt of a client for smfact */
static const unsigned int systraypinning =    1; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5; /* systray spacing */
static const int systraypinningfailfirst = 0; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const int vertpad = 5;       /* vertical padding of bar */
static const int sidepad = 10;       /* horizontal padding of bar */
static const char *fonts[] = {"fontawesome:size=16", "Hack Nerd Font Mono:size=16", };
static const char font[] = {"fontawesome:size=16"};
static const char dmenufont[] = "fontawesome:size=16";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char col_orange[] = "#E59D45";
static const char col_black[] = "#000000";
static const char col_red[] = "#ff0000";
static const char col_yellow[] = "#ffff00";
static const char col_white[] = "#ffffff";
static const char col1[] = "#FCAB64";
static const char col2[] = "#E6DDAF";
static const char col3[] = "#FCBF82";
static const char col4[] = "#CFE7BF";
static const char col5[] = "#A1FCDF";
static const char col6[] = "#84A398";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel] = { col_white, col_orange, col_orange }, // tabs
    [SchemeWarn] = { col_black, col2, col2 }, // Lang
	[SchemeUrgent]= { col_black, col1,    col1 }, // clock
	[SchemeCol1]  = { col_black,      col3, col3 }, // vol
	[SchemeCol2]  = { col_black,      col2, col2 }, // 
	[SchemeCol3]  = { col_black,      col3, col3 },
	[SchemeCol4]  = { col_black,      col4, col4 }, // statusbar
	[SchemeCol5]  = { col_black,      col5, col5 },
	[SchemeSystray]  = { col_black,      col6, col6 }, // systray
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, OPAQUE},
    [SchemeSel] = {OPAQUE, baralpha, OPAQUE},
};

/* tagging */
static const char *tags[] = {"", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     switchtotag isfloating
       monitor */
    {"firefox", NULL, NULL, 1 << 0, 0, 0, 0},
    {"Google-chrome", NULL, NULL, 1 << 0, 0, 0, 0},
    {"Chrome-Remote-Desktop", NULL, NULL, 1 << 0, 0, 1, 1},
    {"VSCodium", NULL, NULL, 1 << 1, 0, 0, 1},
    {"figma-linux", NULL, NULL, 1 << 2, 0, 0, 1},
    {"krita", NULL, NULL, 1 << 2, 0, 0, 0},
    {"dolphin", NULL, NULL, 1 << 0, 0, 0, 1}};

/* layout(s) */
static const float mfact = 0.65;  /* factor of master area size [0.05..0.95] */
static const float smfact = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster = 1;     /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"", tile}, /* first entry is default */
    {"", monocle},
    {"", NULL},

    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY, TAG)                                                      \
  {KeyPress, MODKEY, KEY, view, {.ui = 1 << TAG}},                             \
      {KeyPress, MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},     \
      {KeyPress, MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},              \
      {KeyPress,                                                               \
       MODKEY | ControlMask | ShiftMask,                                       \
       KEY,                                                                    \
       toggletag,                                                              \
       {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/usr/local/bin/st", "-c", cmd, NULL }             \
  }

/* volume control */
static const char *upvol[] = {
    "sh", "-c", "amixer set Master 5%+ && pkill -RTMIN+2 dwmblocks", NULL};
static const char *downvol[] = {
    "sh", "-c", "amixer set Master 5%- && pkill -RTMIN+2 dwmblocks", NULL};
static const char *runrofi[] = {"sh", "-c", "rofi -show combi", NULL};
static const char *screenshot[] = {
    "sh", "-c",
    "QT_AUTO_SCREEN_SCALE_FACTOR=0 QT_SCREEN_SCALE_FACTORS='0.8;0.8' flameshot "
    "gui",
    NULL};

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,   "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray4,   "-sb", col_orange, "-sf", col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};

static const Key keys[] = {
    /* event | modifier | key | function | argument */
    {KeyPress, MODKEY, XK_grave, spawn, {.v = runrofi}},
    {KeyPress, MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {KeyPress, MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {KeyPress, MODKEY, XK_b, togglebar, {0}},
    {KeyPress, MODKEY, XK_j, focusstack, {.i = +1}},
    {KeyPress, MODKEY, XK_k, focusstack, {.i = -1}},
    {KeyPress, MODKEY, XK_i, incnmaster, {.i = +1}},
    {KeyPress, MODKEY, XK_d, incnmaster, {.i = -1}},
    {KeyPress, MODKEY, XK_h, setmfact, {.f = -0.05}},
    {KeyPress, MODKEY, XK_l, setmfact, {.f = +0.05}},
    {KeyPress, MODKEY | ShiftMask, XK_s, spawn, {.v = screenshot}},
    {KeyPress, MODKEY | ShiftMask, XK_h, setsmfact, {.f = +0.05}},
    {KeyPress, MODKEY | ShiftMask, XK_l, setsmfact, {.f = -0.05}},
    {KeyPress, MODKEY, XK_Return, zoom, {0}},
    {KeyPress, 0, XK_Pause, setlayout, {0}},
    {KeyPress, MODKEY, XK_Tab, view, {0}},
    {KeyPress, MODKEY, XK_c, killclient, {0}},
    {KeyPress, MODKEY, XK_q, killclient, {0}},
    {KeyPress, MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {KeyPress, MODKEY, XK_m, setlayout, {.v = &layouts[1]}},
    // 	{ KeyPress, MODKEY,                       XK_f,      setlayout,      {.v
    // = &layouts[2]} },
    {KeyPress, MODKEY, XK_space, setlayout, {0}},
    {KeyPress, MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {KeyPress, MODKEY, XK_0, view, {.ui = ~0}},
    {KeyPress, MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {KeyPress, MODKEY, XK_comma, focusmon, {.i = -1}},
    {KeyPress, MODKEY, XK_period, focusmon, {.i = +1}},
	{KeyPress, MODKEY | ControlMask, XK_comma, tagswapmon, {.i = +1}},
	{KeyPress, MODKEY | ControlMask, XK_period, tagswapmon, {.i = -1}},
    {KeyPress, MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {KeyPress, MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {KeyPress, MODKEY, XK_KP_Add, spawn, {.v = upvol}},
    {KeyPress, MODKEY, XK_KP_Subtract, spawn, {.v = downvol}},
    {KeyPress, MODKEY, XK_minus, setgaps, {.i = -1}},
    {KeyPress, MODKEY, XK_equal, setgaps, {.i = +1}},
    {KeyPress, MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){KeyPress, MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click | event mask | button | function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[1]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    /* placemouse options, choose which feels more natural:
     *    0 - tiled position is relative to mouse cursor
     *    1 - tiled postiion is relative to window center
     *    2 - mouse pointer warps to window center
     *
     * The moveorplace uses movemouse or placemouse depending on the floating
     * state of the selected client. Set up individual keybindings for the two
     * if you want to control these separately (i.e. to retain the feature to
     * move a tiled window into a floating position).
     */
    {ClkClientWin, MODKEY, Button1, moveorplace, {.i = 1}},
    {ClkClientWin, MODKEY, Button2, setlayout, {0}},
    {ClkClientWin, MODKEY, Button3, resizeorfacts, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button3, dragcfact, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button1, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
