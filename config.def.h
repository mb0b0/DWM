/* See LICENSE file for copyright and license details.background */
/* #include <X11/XF86keysym.h> */
#include "fibonacci.c"
/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const int startwithgaps = 0;     /* 1 means gaps are used by default */
static const unsigned int gappx = 5; /* default gap between windows in pixels */
static const unsigned int snap = 12; /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const int vertpad = 10;    /* vetical padding of bar */
static const int sidepad = 10;      /*horizontal padding of bar */
/* static const char *fonts[] = {"JetBrainsMono NF:Regular:size=12"}; */

static const char *fonts[] = {"UbuntuMono Nerd Font:Light:size=12"};
static const char dmenufont[] = {"firacode Nerd Font:Medium:size=34"};
static const char background2[] = "#282a36";
static const char border1[] = "#ff74cE";
static const char foreground1[] = "#05fa7b";
static const char foreground2[] = "#ffb86c";
static const char background[] = "#282a36";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {foreground1, background2, background},
    [SchemeSel] = {foreground2, background2, border1},
};

/* tagging */
static const char *tags[] = {"󰈹", "󰆍", "", "󰙯", "󰓓",
                             "",  "󱉟", "", "󰋌"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 0, 0, -1},
    {"steam", NULL, NULL, 1 << 4, 0, -1},
    {"Discord", NULL, NULL, 1 << 3, 0, -1},
    {"Spotube", NULL, "spotube", 1 << 8, 0, -1},
    {"emulationstation", NULL, "RPie", 5, 0, -1},
    {"blender", NULL, NULL, 0, 1, -1},
    /* {"Blender Render", NULL, "Blender Render", 0, 1, -1}, */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[@]", spiral},  {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"[\\]", dwindle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_j, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD, XK_k, ACTION##stack, {.i = INC(-1)}},                              \
      {MOD, XK_grave, ACTION##stack, {.i = PREVSEL}},                          \
      {MOD, XK_q, ACTION##stack, {.i = 0}},                                    \
      {MOD, XK_a, ACTION##stack, {.i = 1}},                                    \
      {MOD, XK_z, ACTION##stack, {.i = 2}},                                    \
      {MOD, XK_x, ACTION##stack, {.i = -1}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
/*static const char *dmenucmd[] = {"dmenu_run","-b", "-fn", dmenufont,   "-nb",*/
/*                                 background1, "-nf", foreground0, "-sb",*/
/*                                 background,  "-sf", foreground2, NULL};*/
static const char *dmenucmd[] = {"dmenu_run", "-b", "-l", "3","-fn", dmenufont, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *st[] = {"st", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *explorer[] = {"thunar", NULL};
static const char *brightness_up[] = {"brightnessctl", "s", "30+", NULL};
static const char *brightness_down[] = {"brightnessctl", "s", "30-", NULL};
static const char *audio_up[] = {"audio_up", NULL};
static const char *audio_down[] = {"audio_down", NULL};
static const char *print_screen[] = {"flameshot", "gui", NULL};
static const char *roficmd[] = {"rofi", "-show", "drun", NULL};
static const char *lang_us[] = {"setxkbmap", "us", NULL};
static const char *lang_rs[] = {"setxkbmap", "rs", NULL};
static const char *discord[] = {"discord",  NULL};
/* static const char *suspend[] = {"systemctl", "suspend", NULL}; */
/* #define XF86MonBrightnessUp   b_down */
/* #define XF86MonBrightnessDown b_up */

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_o, spawn, {.v = audio_up}},
    /* {MODKEY, XK_l, spawn, {.v = suspend}}, */
    {MODKEY, XK_p, spawn, {.v = print_screen}},
    {MODKEY | ShiftMask, XK_o, spawn, {.v = audio_down}},
    /* {MODKEY, XK_p, spawn, {.v = brightness_up}}, */
    /* {MODKEY | ShiftMask, XK_p, spawn, {.v = brightness_down}}, */
    {MODKEY, XK_m, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = roficmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = st}},
    {MODKEY, XK_b, spawn, {.v = browser}},
    {MODKEY, XK_e, spawn, {.v = explorer}},
    {MODKEY, XK_F9, spawn, {.v = lang_us}},
    {MODKEY, XK_F10, spawn, {.v = lang_rs}},
    {MODKEY | ShiftMask, XK_b, togglebar, {0}},
    // { MODKEY,                XK_j,      focusstack,     {.i = +1 } },
    // { MODKEY,                XK_k,      focusstack,     {.i = -1 } },
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push){
        MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, spawn, {.v = discord}},
    {MODKEY, XK_h, setmfact, {.f = -0.07}},
    {MODKEY, XK_l, setmfact, {.f = +0.07}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY | ShiftMask, XK_Tab, view, {0}},
    {MODKEY, XK_w, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    // { MODKEY,                XK_f,      setlayout,      {.v = &layouts[1]} },
    {MODKEY | ShiftMask, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY, XK_Tab, cyclelayout, {.i = +1}},
    {MODKEY, XK_r, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_r, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -5}},
    {MODKEY, XK_equal, setgaps, {.i = +5}},
    {MODKEY | ShiftMask, XK_minus, setgaps, {.i = GAP_RESET}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = GAP_TOGGLE}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    // { MODKEY|ShiftMask,      XK_q,      quit,           {0} },
    {MODKEY | ControlMask, XK_r, quit, {1}},
    {MODKEY | ShiftMask, XK_BackSpace, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
