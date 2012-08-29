/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS 6
static const char colors[NUMCOLORS][ColLast][8] = {
    // border foreground background
    { "#bbb", "#bbb", "#000" },  // normal
    { "#78c", "#78c", "#000" },  // selected
    { "#ca6", "#ca6", "#000" },  // warning
    { "#c55", "#c55", "#000" },  // error
    { "#000", "#78c", "#000" },  // statuscolors
    { "#000", "#444", "#000" },  // delimiters
    // add more here
};
static const char font[]            = "-*-dina-medium-r-normal-*-15-*-*-*-*-*-*-*";
static const unsigned int borderpx  = 2; 	    /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gap between windows */
static const unsigned int snap      = 0;	    /* snap pixel */
static const Bool showbar           = True;	    /* False means no bar */
static const Bool topbar            = True;	    /* False means bottom bar */
static const Bool clicktofocus      = True;     /* Change focus only on click */

/* tagging */
static const char *tags[] = { "1/def", "2/app", "3/gme", "4/foo" };

static const Rule rules[] = {
	/* class      		            instance    title                   tags mask	isfloating  iscentred   monitor */
    { "feh",                        NULL,       NULL,                        0,     True,       True,       -1 },
    { "mplayer2",                   NULL,       NULL,                        0,     True,       True,       -1 },
    { "XCalc",                      NULL,       NULL,                        0,     True,       True,       -1 }, 
	{ "Chromium",		            NULL,       NULL,                        0,		False,		False,      -1 },
    { "Easytag",		            NULL,       NULL,                   1 << 1,		False,		False,      -1 },
    { "Gimp",		                NULL,       NULL,                   1 << 1,		False,		False,      -1 },
    { "libreoffice-startcenter",    NULL,       NULL,                   1 << 1,     False,      False,      -1 },
    { "Zathura",		            NULL,       NULL,                   1 << 1,		True,		True,       -1 },
    { "Dolphin-emu",		        NULL,       NULL,                   1 << 2,		False,		False,      -1 },
    { "mupen64plus",		        NULL,       NULL,                   1 << 2,		True,		True,       -1 },
    { "scummvm",		            NULL,       NULL,                   1 << 2,		True,		True,       -1 },
    { "Snes9x-gtk",		            NULL,       NULL,                   1 << 2,		True,		True,       -1 },
    { "XMahjongg",                  NULL,       NULL,                   1 << 2,     True,       True,       -1 },
};

/* layout(s) */
static const float mfact      = 0.65; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[T]",      tile },     /* first entry is default */
    { "[F]",      NULL },     /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]           = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]  			= { "urxvtc", NULL };
static const char *voltogglecmd[]  		= { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *volupcmd[]  			= { "amixer", "-q", "sset", "Master", "3+", "unmute", NULL };
static const char *voldowncmd[]  		= { "amixer", "-q", "sset", "Master", "3-", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key        	function        argument */
	{ MODKEY,				        0xffaa,     spawn,		    {.v = voltogglecmd } },
    { MODKEY,				        0xffad,     spawn,		    {.v = voldowncmd } },
	{ MODKEY,				        0xffab,	    spawn,		    {.v = volupcmd } },
	{ MODKEY,                       XK_p,      	spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      	togglebar,      {0} },
	{ MODKEY,                       XK_j,      	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      	focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      	setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      	setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 	zoom,           {0} },
	{ MODKEY,                       XK_Tab,    	view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      	killclient,     {0} },
    { MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      	setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  	setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  	togglefloating, {0} },
	{ MODKEY,                       XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      	                0)
	TAGKEYS(                        XK_2,           	    	1)
	TAGKEYS(                        XK_3,                   	2)
	TAGKEYS(                        XK_4,                      	3)
	TAGKEYS(                        XK_5,                      	4)
	TAGKEYS(                        XK_6,                      	5)
	TAGKEYS(                        XK_7,                      	6)
	TAGKEYS(                        XK_8,                      	7)
	TAGKEYS(                        XK_9,                      	8)
	{ MODKEY|ShiftMask,             XK_q,      	quit,           {0} },
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
