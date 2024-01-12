/* 
 * This file is generated automatically from the default
 * twm bindings file system.twmrc by the twm Makefile.
 */

const unsigned char *defTwmrc[] = {
    (const unsigned char *) "",
    (const unsigned char *) "NoGrabServer",
    (const unsigned char *) "RestartPreviousState",
    (const unsigned char *) "DecorateTransients",
    (const unsigned char *) "TitleFont \"-adobe-helvetica-bold-r-normal--*-120-*-*-*-*-*-*\"",
    (const unsigned char *) "ResizeFont \"-adobe-helvetica-bold-r-normal--*-120-*-*-*-*-*-*\"",
    (const unsigned char *) "MenuFont \"-adobe-helvetica-bold-r-normal--*-120-*-*-*-*-*-*\"",
    (const unsigned char *) "IconFont \"-adobe-helvetica-bold-r-normal--*-100-*-*-*-*-*-*\"",
    (const unsigned char *) "IconManagerFont \"-adobe-helvetica-bold-r-normal--*-100-*-*-*\"",
    (const unsigned char *) "",
    (const unsigned char *) "Color",
    (const unsigned char *) "{",
    (const unsigned char *) "    BorderColor \"slategrey\"",
    (const unsigned char *) "    DefaultBackground \"rgb:2/a/9\"",
    (const unsigned char *) "    DefaultForeground \"gray85\"",
    (const unsigned char *) "    TitleBackground \"rgb:2/a/9\"",
    (const unsigned char *) "    TitleForeground \"gray85\"",
    (const unsigned char *) "    MenuBackground \"rgb:2/a/9\"",
    (const unsigned char *) "    MenuForeground \"gray85\"",
    (const unsigned char *) "    MenuBorderColor \"slategrey\"",
    (const unsigned char *) "    MenuTitleBackground \"gray70\"",
    (const unsigned char *) "    MenuTitleForeground \"rgb:2/a/9\"",
    (const unsigned char *) "    IconBackground \"rgb:2/a/9\"",
    (const unsigned char *) "    IconForeground \"gray85\"",
    (const unsigned char *) "    IconBorderColor \"gray85\"",
    (const unsigned char *) "    IconManagerBackground \"rgb:2/a/9\"",
    (const unsigned char *) "    IconManagerForeground \"gray85\"",
    (const unsigned char *) "}",
    (const unsigned char *) "",
    (const unsigned char *) "MoveDelta 3",
    (const unsigned char *) "Function \"move-or-lower\" { f.move f.deltastop f.lower }",
    (const unsigned char *) "Function \"move-or-raise\" { f.move f.deltastop f.raise }",
    (const unsigned char *) "Function \"move-or-iconify\" { f.move f.deltastop f.iconify }",
    (const unsigned char *) "",
    (const unsigned char *) "Button1 = : root : f.menu \"defops\"",
    (const unsigned char *) "",
    (const unsigned char *) "Button1 = m : window|icon : f.function \"move-or-lower\"",
    (const unsigned char *) "Button2 = m : window|icon : f.iconify",
    (const unsigned char *) "Button3 = m : window|icon : f.function \"move-or-raise\"",
    (const unsigned char *) "",
    (const unsigned char *) "Button1 = : title : f.function \"move-or-raise\"",
    (const unsigned char *) "Button2 = : title : f.raiselower",
    (const unsigned char *) "",
    (const unsigned char *) "Button1 = : icon : f.function \"move-or-iconify\"",
    (const unsigned char *) "Button2 = : icon : f.iconify",
    (const unsigned char *) "",
    (const unsigned char *) "Button1 = : iconmgr : f.iconify",
    (const unsigned char *) "Button2 = : iconmgr : f.iconify",
    (const unsigned char *) "",
    (const unsigned char *) "menu \"defops\"",
    (const unsigned char *) "{",
    (const unsigned char *) "\"Twm\"	f.title",
    (const unsigned char *) "\"XTerm\"         !\"xterm &\"",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"Utilities\"	f.menu \"Utilities\"",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"Window Ops\"    f.menu \"Window Ops\"",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"Kill\"		f.destroy",
    (const unsigned char *) "\"Delete\"	f.delete",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"Refresh\"	f.refresh",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"(Re)Start\"	f.menu \"Restart\"",
    (const unsigned char *) "\"Exit\"		f.menu \"Quit\"",
    (const unsigned char *) "}",
    (const unsigned char *) "",
    (const unsigned char *) "menu \"Utilities\"",
    (const unsigned char *) "{",
    (const unsigned char *) "\"Top\"		!\"xterm -T Top -n Top -e top &\"",
    (const unsigned char *) "\"Calculator\"	!\"xcalc &\"",
    (const unsigned char *) "\"Xmag\"		!\"xmag &\"",
    (const unsigned char *) "\"Editres\"	!\"editres &\"",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"XLock\"		!\"xlock -mode random &\"",
    (const unsigned char *) "\"Reset X defaults\" !\"xrdb -load $HOME/.Xdefaults\"",
    (const unsigned char *) "}",
    (const unsigned char *) "",
    (const unsigned char *) "menu \"Window Ops\"",
    (const unsigned char *) "{",
    (const unsigned char *) "\"Iconify\"	f.iconify",
    (const unsigned char *) "\"Resize\"	f.resize",
    (const unsigned char *) "\"Move\"		f.move",
    (const unsigned char *) "\"Raise\"		f.raise",
    (const unsigned char *) "\"Lower\"		f.lower",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"Focus\"		f.focus",
    (const unsigned char *) "\"Unfocus\"	f.unfocus",
    (const unsigned char *) "\"Show Iconmgr\"	f.showiconmgr",
    (const unsigned char *) "\"Hide Iconmgr\"	f.hideiconmgr",
    (const unsigned char *) "}",
    (const unsigned char *) "",
    (const unsigned char *) "menu \"Restart\"",
    (const unsigned char *) "{",
    (const unsigned char *) "\"Restart\"	f.restart",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"twm\"		f.startwm \"twm\"",
    (const unsigned char *) "\"fvwm\"		f.startwm \"fvwm\"",
    (const unsigned char *) "\"cwm\"		f.startwm \"cwm\"",
    (const unsigned char *) "\"wm2\"		f.startwm \"wm2\"",
    (const unsigned char *) "\"ctwm\"		f.startwm \"ctwm\"",
    (const unsigned char *) "\"mwm\"		f.startwm \"mwm\"",
    (const unsigned char *) "\"\"		f.nop",
    (const unsigned char *) "\"dummy\"		f.startwm \"xterm\"",
    (const unsigned char *) "}",
    (const unsigned char *) "menu \"Quit\"",
    (const unsigned char *) "{",
    (const unsigned char *) "\"Don't quit\"	f.nop",
    (const unsigned char *) " \"\"		f.nop",
    (const unsigned char *) "\"Really Quit\"	f.quit",
    (const unsigned char *) "}",
    (const unsigned char *) 0 };