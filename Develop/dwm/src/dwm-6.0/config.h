/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[] ="-*-codec terminal-*-*-*-*-15-*-*-*-*-*-*-*";

#define NUMCOLORS 5
static const char colors[NUMCOLORS][ColLast][9] = {
  // border foreground background
  { "#4e4e4e", "#4e4e4e", "#1c1c1c" }, // 0 = normal
  { "#7c7cA6", "#ffffff", "#7c7cA6" }, // 1 = selected
  { "#212121", "#ffffff", "#1c1c1c" }, // 2 = red
  { "#000000", "#ffffff", "#1c1c1c" }, // <| Color
  { "#000000", "#7c7cA6", "#1c1c1c" }, // [ DATE ] color
};

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "scratch", "chat", "web", "video" };

static const Rule rules[] = {
  /* class      instance    title       tags mask     isfloating   monitor */
  // { NULL    , NULL        , NULL           , 0    , True  , -1 } ,
  { "NULL"     , "Dialog"    , NULL           , 0    , True  , -1 } ,
  { "XTerm"    , NULL        , "chris@arch:~" , 1<<0 , False , -1 } ,
  { "XTerm"    , NULL        , "irssi"        , 1<<1 , False , -1 } ,
  { "XTerm"    , NULL        , "ncmpcpp"      , 0    , True  , -1 } ,
  { "XTerm"    , NULL        , "mutt"         , 0    , True  , -1 } ,
  { "XTerm"    , NULL        , "pyradio"      , 1<<4 , False , -1 } ,
  { "Vlc"      , NULL        , NULL           , 1<<3 , False , -1 } ,
  { "Firefox"  , "Browser"   , NULL           , 0    , True  , -1 } ,
  { "Firefox"  , "Dialog"    , NULL           , 0    , True  , -1 } ,
  { "Firefox"  , "Downloads" , NULL           , 0    , True  , -1 } ,
  { "Firefox"  , "Places"    , NULL           , 0    , True  , -1 } ,
  { "Firefox"  , "Navigator" , NULL           , 1<<2 , False , -1 } ,
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"
#include "fibonacci.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[t]",      tile },    /* first entry is default */
  { "[f]",      NULL },    /* no layout function means floating behavior */
  { "[m]",      monocle },
  { "[b]",      bstack },
  { "[g]",      gaplessgrid },
  { "[s]",      fibonacci }
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char  *dmenucmd[]  = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]    = { "xterm", NULL };
static const char *chatcmd[]    = { "xterm", "-title,", "irssi", "-e", "dtach", "-A", "/tmp/irssi", "-z", "irssi", NULL };
static const char *musiccmd[]   = { "xterm", "-title,", "ncmpcpp", "-e", "dtach", "-A", "/tmp/ncmpcpp", "-z", "ncmpcpp", NULL };
static const char *mailcmd[]    = { "xterm", "-title,", "mutt", "-e", "dtach", "-A", "/tmp/mutt", "-z", "mutt", NULL };
static const char *volumedown[] = { "amixer", "-q", "set", "PCM", "2%-", "unmute", NULL };
static const char *volumeup[]   = { "amixer", "-q", "set", "PCM", "2%+", "unmute", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "PCM", "toggle", NULL };
static const char *vlc[]        = { "vlc-play", NULL };
static const char *rotatewall[] = { "wallpaper-rotate-new", NULL };

#include "movestack.c"
static Key keys[] = {
  /* modifier          key                       function         argument */
  { 0,                 XF86XK_AudioLowerVolume,  spawn,           { .v = volumedown } },
  { 0,                 XF86XK_AudioRaiseVolume,  spawn,           { .v = volumeup } },
  { 0,                 XF86XK_AudioMute,         spawn,           { .v = mute } },
  { MODKEY|ShiftMask,  XK_bracketright,          spawn,           {.v = rotatewall } },
  { MODKEY,            XK_v,                     spawn,           {.v = vlc } },
  { MODKEY,            XK_i,                     spawn,           {.v = chatcmd } },
  { MODKEY,            XK_r,                     spawn,           {.v = musiccmd } },
  { MODKEY,            XK_c,                     spawn,           {.v = mailcmd } },
  { MODKEY,            XK_p,                     spawn,           {.v = dmenucmd } },
  { MODKEY|ShiftMask,  XK_Return,                spawn,           {.v = termcmd } },
  { MODKEY,            XK_j,                     focusstack,      {.i = +1 } },
  { MODKEY,            XK_k,                     focusstack,      {.i = -1 } },
  // { MODKEY,         XK_i,                     incnmaster,      {.i = +1 } },
  // { MODKEY,         XK_d,                     incnmaster,      {.i = -1 } },
  { MODKEY,            XK_h,                     setmfact,        {.f = -0.05} },
  { MODKEY,            XK_l,                     setmfact,        {.f = +0.05} },
  { MODKEY|ShiftMask,  XK_j,                     movestack,       {.i = +1 } },
  { MODKEY|ShiftMask,  XK_k,                     movestack,       {.i = -1 } },
  { MODKEY,            XK_m,                     zoom,            {0} },
  { MODKEY,            XK_Tab,                   view,            {0} },
  { MODKEY|ShiftMask,  XK_q,                     killclient,      {0} },
  { MODKEY,            XK_t,                     setlayout,       {.v = &layouts[0]} },
  // { MODKEY,            XK_space,                 setlayout,       {.v = &layouts[1]} },
  { MODKEY,            XK_Return,                setlayout,       {.v = &layouts[2]} },
  { MODKEY,            XK_b,                     setlayout,       {.v = &layouts[3]} },
  { MODKEY,            XK_g,                     setlayout,       {.v = &layouts[4]} },
  { MODKEY,            XK_f,                     setlayout,       {.v = &layouts[5]} },
  { MODKEY,            XK_space,                 setlayout,       {0} },
  { MODKEY|ShiftMask,  XK_space,                 togglefloating,  {0} },
  { MODKEY,            XK_grave,                 view,            {.ui = ~0 } },
  // { MODKEY|ShiftMask,  XK_0,                     tag,             {.ui = ~0 } },
  { MODKEY,            XK_comma,                 focusmon,        {.i = -1 } },
  { MODKEY,            XK_period,                focusmon,        {.i = +1 } },
  { MODKEY|ShiftMask,  XK_comma,                 tagmon,          {.i = -1 } },
  { MODKEY|ShiftMask,  XK_period,                tagmon,          {.i = +1 } },
    TAGKEYS(                        XK_1,  0)
    TAGKEYS(                        XK_w,  1)
    TAGKEYS(                        XK_2,  2)
    TAGKEYS(                        XK_v,  3)
    // TAGKEYS(                        XK_x,  4)
    // TAGKEYS(                        XK_c,  5)
    // TAGKEYS(                        XK_7,  6)
    // TAGKEYS(                        XK_8,  7)
    // TAGKEYS(                        XK_9,  8)
    { MODKEY|ControlMask,           XK_q,      quit,           {0} },
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

