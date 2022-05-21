/* See LICENSE file for copyright and license details. */

/* Appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1; /* 0 means bottom bar */
static const char *fonts[] = { "monospace:pixelsize=18" };
static const char dmenufont[] = "monospace:pixelsize=18";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/* could also use ichi, ni, san, yon, go, roku, nana, etc kanji */
/* static const char *tags[] = { "cute", "neko", "robot", "maid", "hana", }; */
static const char *tags[] = { "一", "二", "三", "四", "五", };

/* For some windows, such as preferences dialogs, it does not make sense for these windows to be tiled - they should be free-floating instead */
/* From: https://dwm.suckless.org/customisation/rules */
static const Rule rules[] = {
    /* To check the properties of a client, run the xprop script, xproperties.sh, and click on the GUI of a running client. */
	/* The double carats in the rules below, such as 1 << 2, means that a 1 (000000001) is moved 2 spaces to the left (000000100), which means tag 3. */

	/*   class          instance        title  tags mask  isfloating  monitor */
	{ "Brave-browser", "brave-browser", NULL,   1 << 1,       0,          -1 },
	{ "discord",       "discord",       NULL,   1 << 3,       0,          -1 },
	{ "qBittorrent",   "qbittorrent",   NULL,   1 << 4,       0,          -1 },

};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints = 2;/* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
/* https://dwm.suckless.org/customisation/windows_key */
#define MODKEY Mod4Mask
#define MODMASK (MODKEY|ShiftMask)
// #define ALTKEY Mod1Mask create a definition for Mod1Mask (the alt key)
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODMASK,                      KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODMASK|ControlMask,          KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[] = { "/usr/bin/web", NULL };
static const char *killwb[] = { "/usr/bin/killall", "-I", "-q", "brave", NULL };
static const char *passmenu[] = { "/usr/bin/passmenu", NULL };
static const char *flameshot[] = { "/usr/bin/flameshot", "gui", NULL };
static const char *upvol[]   = { "/home/suke/.local/bin/vol", "+2%",     NULL };
static const char *downvol[] = { "/home/suke/.local/bin/vol", "-2%",     NULL };
static const char *mutevol[] = { "/home/suke/.local/bin/vol", "toggle",  NULL };

static Key keys[] = {
	/* modifier                     key                      function        argument */
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = upvol } },
	{ MODKEY,                       XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_m,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,                    spawn,          {.v = web } },
	{ MODMASK,                      XK_w,                    spawn,          {.v = killwb } },
	{ MODKEY,                       XK_p,                    spawn,          {.v = passmenu } },
	{ MODKEY,                       XK_s,                    spawn,          {.v = flameshot } },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = 0 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05 } },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05 } },
	{ MODMASK,                      XK_Return,               zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODMASK,                      XK_c,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} }, /* monocle */
	{ MODMASK,                      XK_f,                    setlayout,      {.v = &layouts[2]} }, /* no layout/floating */
	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODMASK,                      XK_space,                togglefloating, {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODMASK,                      XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODMASK,                      XK_comma,                tagmon,         {.i = -1 } },
	{ MODMASK,                      XK_period,               tagmon,         {.i = +1 } },
	{ MODMASK|ControlMask,          XK_q,                    quit,           {0} },
	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
};

/* mouse button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

