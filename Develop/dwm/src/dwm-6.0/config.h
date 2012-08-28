#include <X11/XF86keysym.h> 
/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus2-medium-r-*-*-12-*-*-*-*-*-*-*";
#define NUMCOLORS 9 
static const char colors[NUMCOLORS][ColLast][9] = {
  // Dark Colors
  // border foreground background
  { "#4e4e4e", "#969191", "#4e4e4e" }, // 0 = normal
  { "#759073", "#FFFFFF", "#4e4e4e" }, // 1 = selected
  { "#212121", "#FFFFFF", "#B98585" }, // 2 = red
  { "#212121", "#FFFFFF", "#759073" }, // 3 = green
  { "#212121", "#FFFFFF", "#C0AE81" }, // 4 = yellow
  { "#212121", "#6C9E9F", "#4e4e4e" }, // 5 = blue
  { "#212121", "#FFFFFF", "#6C9E9F" }, // 5 = blue
  { "#212121", "#FFFFFF", "#D28DBB" }, // 7 = magenta
  { "#212121", "#FFFFFF", "#DAD5BC" }, // 8 = grey
};

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "\u00c7", "\u00C0", "\u00CE " };

static const Rule rules[] = {
  /* class      instance    title       tags mask     isfloating   monitor */
  // { NULL      , NULL , NULL        , 0    , True  , -1 } , 
  { "URxvt"   , NULL        , NULL , 0    , False , -1 } , 
  { "Firefox" , "Browser"   , NULL , 0    , True  , -1 } , 
  { "Firefox" , "Dialog"    , NULL , 0    , True  , -1 } , 
  { "Firefox" , "Places"    , NULL , 0    , True  , -1 } , 
  { "Firefox" , "Navigator" , NULL , 1<<1 , False , -1 } , 
  { "slgui"   , NULL        , NULL , 1<<2 , False , -1 } , 
  { "Qjackctl", NULL        , NULL , 1<<3 , True , -1 } , 
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
// #include "grid.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "\u00C9",      tile },    /* first entry is default */
  { "\u00CA",      NULL },    /* no layout function means floating behavior */
  { "\u00CB",      monocle },
  { "\u00CC",      bstack },
	// { "\u00CD",      grid },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char  *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *firefox[]    = { "firefox", NULL };
static const char *termcmd[]    = { "urxvt", NULL };
static const char *radio[]      = { "urxvt", "-e", "pyradio", NULL };
static const char *mixer[]      = { "urxvt", "-e", "alsamixer", NULL };
static const char *chat[]      = { "urxvt", "-e", "weechat-curses", NULL };
static const char *volumedown[] = { "amixer", "-q", "set", "PCM", "2%-", "unmute", NULL };
static const char *volumeup[]   = { "amixer", "-q", "set", "PCM", "2%+", "unmute", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "PCM", "toggle", NULL };
static const char *vlc[]        = { "vlc-play", NULL };
static const char *rotatewall[] = { "wallpaper-rotate-new", NULL };

#include "movestack.c"
static Key keys[] = {
  /* modifier                     key        function        argument */
  { 0, XF86XK_AudioLowerVolume,   spawn,        { .v = volumedown } },
  { 0, XF86XK_AudioRaiseVolume,   spawn,        { .v = volumeup } }, 
  { 0, XF86XK_AudioMute,          spawn,        { .v = mute } }, 
  { MODKEY|ShiftMask,             XK_bracketright, spawn,    {.v = rotatewall } },
  { MODKEY,                       XK_v,      spawn,          {.v = vlc } },
  { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_c,      spawn,          {.v = chat } },
  { MODKEY,                       XK_r,      spawn,          {.v = radio } },
  { MODKEY,                       XK_f,      spawn,          {.v = firefox } },
  { MODKEY,                       XK_a,      spawn,          {.v = mixer } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  // { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
  { MODKEY,                       XK_m,      zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_Return, setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  { MODKEY,                       XK_grave,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};


/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

