/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 4;
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad						= 10;
static const int sidepad						= 1;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12" };
static const char dmenufont[]       = { "monospace:size=10" };
static const char col_gray1[]       = "#24273a";
static const char col_gray2[]       = "#8aadf4";
static const char col_gray3[]       = "#f5c2e7";
static const char col_gray4[]       = "#eed49f";
static const char col_cyan[]        = "#181926";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_cyan },
    [SchemeSel]  = { col_gray4, col_cyan,  col_gray2  },
};
/*autostart*/
static const char *autostart[] = {
	"kitty",NULL,
	NULL/*terminate*/
};
/* tagging */
static const char *tags[] = { "", "", "", "", "󱄅", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
  { "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *screenshot[] = {"scrot","/home/somya/Pictures/screenshots_%Y-%m-%d_%H-%M-%S.png",NULL};
static const char *flameshot[] = {"flameshot","gui",NULL};
static const char *light_up[] = { "brightnessctl", "set", "+5%", NULL };
static const char *light_down[] = { "brightnessctl", "set", "5%-", NULL };

static const Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          SHCMD("clipmenu")},
				{ MODKEY,												XK_Escape, spawn,					 SHCMD("rofi -show power-menu -modi power-menu:~/.local/bin/rofi-power-menu") },
        { MODKEY,                       XK_x,      spawn,          {.v = roficmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { 0,                            XK_Print,  spawn,          {.v = screenshot} },
	      { MODKEY,			                  XK_Print,  spawn,          {.v = flameshot}  },
        { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("/run/wrappers/bin/slock") },
	      { MODKEY,                       XK_Up,     spawn,          SHCMD("~/.local/bin/volume up") },
	      { MODKEY,			                  XK_Down,   spawn,	         SHCMD("~/.local/bin/volume down") },
	      { MODKEY,                       XK_Right,  spawn,          SHCMD("~/.local/bin/backlight up") },
	      { MODKEY,                       XK_Left,   spawn,          SHCMD("~/.local/bin/backlight down") },
				{ MODKEY,												XK_e,			 spawn,					 SHCMD("rofi -modi emoji -show emoji") },
				{ MODKEY,												XK_c,			 spawn,					 SHCMD("rofi -show calc -modi calc") },
				{ MODKEY,												XK_w,			 spawn,					 SHCMD("zsh ~/.local/bin/rofi-wallpaper.sh") },
				{ MODKEY|ShiftMask,							XK_w,			 spawn,					 SHCMD("zsh ~/.local/bin/rofi-image-viewer.sh") },
				{ MODKEY,												XK_m,			 spawn,					 SHCMD("zsh ~/.local/bin/rofi-music-selection.sh") },
				{ MODKEY,												XK_v,      spawn,					 SHCMD("zsh ~/.local/bin/rofi-video.sh") },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	      { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	      { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	      { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	      { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[7]} },
				{ MODKEY,												XK_g,			 setlayout,			 {.v = &layouts[8]} },
				{ MODKEY|ShiftMask,							XK_g,			 setlayout,			 {.v = &layouts[6]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

