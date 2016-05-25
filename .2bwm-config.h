///---User configurable stuff---///
///---Modifiers---///
#define MOD             XCB_MOD_MASK_4
/* Super/Windows key  or check xmodmap(1) with -pm*/
///--Speed---///
/* Move this many pixels when moving or resizing with keyboard unless the
 window has hints saying otherwise.
 *0)move step slow   1)move step fast
 *2)mouse slow       3)mouse fast     */
static const uint16_t movements[] = {20,40,15,400};
/* resize by line like in mcwm -- jmbi */
static const bool     resize_by_line          = true;
/* the ratio used when resizing and keeping the aspect */
static const float    resize_keep_aspect_ratio= 1.03;
///---Offsets---///
/*0)offsetx          1)offsety
 *2)maxwidth         3)maxheight */
static const uint8_t offsets[] = {40,40,80,80};
///---Colors---///
/*0)focuscol         1)unfocuscol
 *2)fixedcol         3)unkilcol
 *4)fixedunkilcol    5)outerbordercol
 *6)emptycol         */
static const char *colors[] = {"#ECEFF1","#607D8B","#FFF176","#64B5F6","#81C784","#263238","#212121"};
/* if this is set to true the inner border and outer borders colors will be
 swapped */
static const bool inverted_colors = false;
///---Cursor---///
/* default position of the cursor:
 * correct values are:
 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
 * All these are relative to the current window. */
#define CURSOR_POSITION MIDDLE
///---Borders---///
/*0) Outer border size. If you put this negative it will be a square.
 *1) Full borderwidth    2) Magnet border size
 *3) Resize border size  */
static const uint8_t borders[] = {8,10,10,10};
/* Windows that won't have a border.*/
#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};
///--Menus and Programs---///
static const char *rofirun[]   = { "rofirun", NULL };
static const char *rofiwindow[]   = { "rofiwindow", NULL };
static const char *terminal[]  = { "urxvt", NULL };
static const char *lock[]  = { "lock", NULL };
///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=2};
	maxhalf(&arg2);
	Arg arg3 = {.i=0};
	teleport(&arg3);
}
///---Shortcuts---///
/* Check /usr/include/X11/keysymdef.h for the list of all keys
 * 0x000000 is for no modkey
 * For AZERTY keyboards XK_1...0 should be replaced by :
 *      DESKTOPCHANGE(     XK_ampersand,                     0)
 *      DESKTOPCHANGE(     XK_eacute,                        1)
 *      DESKTOPCHANGE(     XK_quotedbl,                      2)
 *      DESKTOPCHANGE(     XK_apostrophe,                    3)
 *      DESKTOPCHANGE(     XK_parenleft,                     4)
 *      DESKTOPCHANGE(     XK_minus,                         5)
 *      DESKTOPCHANGE(     XK_egrave,                        6)
 *      DESKTOPCHANGE(     XK_underscore,                    7)
 *      DESKTOPCHANGE(     XK_ccedilla,                      8)
 *      DESKTOPCHANGE(     XK_agrave,                        9)*
 */
#define DESKTOPCHANGE(K,N) \
{  MOD ,             K,              changeworkspace, {.i=N}}, \
{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=0}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=1}},
    // Kill a window
    {  MOD ,              XK_x,          deletewin,         {.i=0}},
    // Resize a window
    {  MOD |SHIFT,        XK_e,          resizestep,        {.i=2}},
    {  MOD |SHIFT,        XK_n,          resizestep,        {.i=1}},
    {  MOD |SHIFT,        XK_i,          resizestep,        {.i=3}},
    {  MOD |SHIFT,        XK_h,          resizestep,        {.i=0}},
    // Resize a window slower
    {  MOD |SHIFT|CONTROL,XK_e,          resizestep,        {.i=6}},
    {  MOD |SHIFT|CONTROL,XK_n,          resizestep,        {.i=5}},
    {  MOD |SHIFT|CONTROL,XK_i,          resizestep,        {.i=7}},
    {  MOD |SHIFT|CONTROL,XK_h,          resizestep,        {.i=4}},
    // Move a window
    {  MOD ,              XK_e,          movestep,          {.i=2}},
    {  MOD ,              XK_n,          movestep,          {.i=1}},
    {  MOD ,              XK_i,          movestep,          {.i=3}},
    {  MOD ,              XK_h,          movestep,          {.i=0}},
    // Move a window slower
    {  MOD |CONTROL,      XK_e,          movestep,          {.i=6}},
    {  MOD |CONTROL,      XK_n,          movestep,          {.i=5}},
    {  MOD |CONTROL,      XK_i,          movestep,          {.i=7}},
    {  MOD |CONTROL,      XK_h,          movestep,          {.i=4}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_c,          teleport,          {.i=0}},
    // Center y:
    {  MOD |SHIFT,        XK_c,          teleport,          {.i=3}},
    // Center x:
    {  MOD |CONTROL,      XK_c,          teleport,          {.i=-3}},
    // Top left:
    {  MOD ,              XK_Up,         teleport,          {.i=2}},
    // Top right:
    {  MOD ,              XK_Right,      teleport,          {.i=-2}},
    // Bottom left:
    {  MOD ,              XK_Left,       teleport,          {.i=1}},
    // Bottom right:
    {  MOD ,              XK_Down,       teleport,          {.i=-1}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Page_Down,  resizestep_aspect, {.i=0}},
    {  MOD ,              XK_Page_Up,    resizestep_aspect, {.i=1}},
    // Full screen window without borders
    {  MOD ,              XK_m,          maximize,          {.i=0}},
    // Full screen window without borders overiding offsets
    {  MOD |SHIFT ,       XK_m,          maximize,          {.i=1}},
    // Maximize vertically
    {  MOD ,              XK_v,          maxvert_hor,       {.i=1}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_v,          maxvert_hor,       {.i=0}},
    // Maximize and move
    // vertically left
    {  MOD ,              XK_Home,       maxhalf,           {.i=2}},
    // vertically right
    {  MOD ,              XK_End,        maxhalf,           {.i=1}},
    // Next/Previous screen
    {  MOD ,              XK_comma,      changescreen,      {.i=1}},
    {  MOD ,              XK_period,     changescreen,      {.i=0}},
    // Raise or lower a window
    {  MOD ,              XK_r,          raiseorlower,      {.i=0}},
    // Next/Previous workspace
    {  MOD ,              XK_t,          nextworkspace,     {.i=0}},
    {  MOD ,              XK_s,          prevworkspace,     {.i=0}},
    // Move to Next/Previous workspace
    {  MOD |SHIFT ,       XK_t,          sendtonextworkspace,{.i=0}},
    {  MOD |SHIFT ,       XK_s,          sendtoprevworkspace,{.i=0}},
    // Make the window unkillable
    {  MOD ,              XK_a,          unkillable,        {.i=0}},
    // Make the window appear always on top
    {  MOD |SHIFT,        XK_z,          always_on_top,     {.i=0}},
    // Make the window stay on all workspaces
    {  MOD ,              XK_z,          fix,               {.i=0}},
    // Iconify the window
    {  MOD ,              XK_Escape,     hide,              {}},
    // Fold half vertically
    {  MOD ,              XK_k,          maxhalf,           {.i=4}},
    // Fold half horizontally
    {  MOD |SHIFT,        XK_k,          maxhalf,           {.i=-4}},
    // Unfold vertically
    {  MOD ,              XK_b,          maxhalf,           {.i=3}},
    // Unfold horizontally
    {  MOD |SHIFT,        XK_b,          maxhalf,           {.i=-3}},
    // Start programs
    {  MOD ,              XK_Return,     start,             {.com=terminal}},
    {  MOD ,              XK_o,          start,             {.com=rofirun}},
    {  MOD ,              XK_slash,      start,             {.com=rofiwindow}},
    {  MOD ,              XK_minus,      start,             {.com=lock}},
    // Exit or restart 2bwm
    {  MOD |CONTROL,      XK_x,          twobwm_exit,       {.i=0}},
    {  MOD |CONTROL,      XK_r,          twobwm_restart,    {.i=0}},
    // Change current workspace
       DESKTOPCHANGE(     XK_q,                             0)
       DESKTOPCHANGE(     XK_w,                             1)
       DESKTOPCHANGE(     XK_f,                             2)
       DESKTOPCHANGE(     XK_p,                             3)
       DESKTOPCHANGE(     XK_g,                             4)
       DESKTOPCHANGE(     XK_j,                             5)
       DESKTOPCHANGE(     XK_l,                             6)
       DESKTOPCHANGE(     XK_u,                             7)
	   DESKTOPCHANGE(     XK_semicolon,                     9)
       DESKTOPCHANGE(     XK_y,                             8)
};
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}},
    {  MOD|CONTROL,XCB_BUTTON_INDEX_3,     start,         {.com=rofirun}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}}
};
